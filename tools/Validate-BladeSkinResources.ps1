param(
    [string]$ReferenceRoot = '',
    [string]$OutputDirectory = '',
    [switch]$FailOnUnresolved
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

$repositoryRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
if ([string]::IsNullOrWhiteSpace($ReferenceRoot)) {
    $ReferenceRoot = Join-Path $repositoryRoot 'references\local\BladeDash(2005)'
}
if ([string]::IsNullOrWhiteSpace($OutputDirectory)) {
    $OutputDirectory = Join-Path $repositoryRoot 'build\milestone000\resource-validation'
}

$ReferenceRoot = (Resolve-Path -LiteralPath $ReferenceRoot).Path
$skinXuiPath = Join-Path $ReferenceRoot 'skin.xui'
$skinXmlPath = Join-Path $ReferenceRoot 'skin.xml'
foreach ($requiredPath in @($skinXuiPath, $skinXmlPath)) {
    if (-not (Test-Path -LiteralPath $requiredPath -PathType Leaf)) {
        throw "Required BladeDash file is missing: $requiredPath"
    }
}

$allFiles = @(Get-ChildItem -LiteralPath $ReferenceRoot -Recurse -File)
$extensionPattern = '(?:xur|xma|png|dds|ttf|xtt|wmv|jpg|fx|x)'

function Resolve-ResourceReference {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Source,

        [Parameter(Mandatory = $true)]
        [string]$Reference
    )

    $normalizedReference = $Reference.Trim()
    $extension = [System.IO.Path]::GetExtension($normalizedReference).TrimStart('.').ToLowerInvariant()

    if ($normalizedReference -match '^[a-z]+://') {
        return [pscustomobject]@{
            Source = $Source
            Reference = $normalizedReference
            Extension = $extension
            Status = 'EXTERNAL_SCHEME'
            ResolvedPath = ''
        }
    }

    if ($normalizedReference -match '^\.\.[\\/]') {
        return [pscustomobject]@{
            Source = $Source
            Reference = $normalizedReference
            Extension = $extension
            Status = 'OUTSIDE_REFERENCE_ROOT'
            ResolvedPath = ''
        }
    }

    $candidate = Join-Path $ReferenceRoot ($normalizedReference -replace '/', '\')
    if (Test-Path -LiteralPath $candidate) {
        $item = Get-Item -LiteralPath $candidate
        return [pscustomobject]@{
            Source = $Source
            Reference = $normalizedReference
            Extension = $extension
            Status = if ($item.PSIsContainer) { 'FOUND_DIRECTORY' } else { 'FOUND_EXACT_PATH' }
            ResolvedPath = $item.FullName.Substring($ReferenceRoot.Length + 1)
        }
    }

    if ($normalizedReference -match '[\\/]') {
        return [pscustomobject]@{
            Source = $Source
            Reference = $normalizedReference
            Extension = $extension
            Status = 'MISSING_PATH'
            ResolvedPath = ''
        }
    }

    $matches = @($allFiles | Where-Object { $_.Name -ieq $normalizedReference })
    if ($matches.Count -eq 1) {
        return [pscustomobject]@{
            Source = $Source
            Reference = $normalizedReference
            Extension = $extension
            Status = 'FOUND_BY_BASENAME'
            ResolvedPath = $matches[0].FullName.Substring($ReferenceRoot.Length + 1)
        }
    }

    if ($matches.Count -gt 1) {
        return [pscustomobject]@{
            Source = $Source
            Reference = $normalizedReference
            Extension = $extension
            Status = 'AMBIGUOUS_BASENAME'
            ResolvedPath = ($matches.FullName | ForEach-Object {
                $_.Substring($ReferenceRoot.Length + 1)
            }) -join '; '
        }
    }

    return [pscustomobject]@{
        Source = $Source
        Reference = $normalizedReference
        Extension = $extension
        Status = 'MISSING_BASENAME'
        ResolvedPath = ''
    }
}

$rows = [System.Collections.Generic.List[object]]::new()

$skinXuiText = Get-Content -LiteralPath $skinXuiPath -Raw
$xuiPattern = "(?i)[^<>\r\n]+\.${extensionPattern}"
$xuiReferences = @(
    [regex]::Matches($skinXuiText, $xuiPattern) |
        ForEach-Object { $_.Value.Trim() } |
        Sort-Object -Unique
)
foreach ($reference in $xuiReferences) {
    $rows.Add((Resolve-ResourceReference -Source 'skin.xui' -Reference $reference))
}

[xml]$skinXml = Get-Content -LiteralPath $skinXmlPath -Raw
foreach ($node in $skinXml.SelectNodes('//*[not(*)]')) {
    $value = ([string]$node.InnerText).Trim()
    if ($value -match "(?i)\.${extensionPattern}$" -or $value -match '[\\/]$') {
        $rows.Add((Resolve-ResourceReference -Source "skin.xml:$($node.Name)" -Reference $value))
    }
}
foreach ($attribute in $skinXml.SelectNodes('//@*')) {
    $value = ([string]$attribute.Value).Trim()
    if ($value -match "(?i)\.${extensionPattern}$") {
        $rows.Add((Resolve-ResourceReference -Source "skin.xml:@$($attribute.Name)" -Reference $value))
    }
}

New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
$csvPath = Join-Path $OutputDirectory 'BladeDash-resource-audit.csv'
$summaryPath = Join-Path $OutputDirectory 'BladeDash-resource-audit-summary.json'
$rows | Sort-Object Source, Reference | Export-Csv -LiteralPath $csvPath -NoTypeInformation -Encoding UTF8

$statusCounts = [ordered]@{}
foreach ($group in ($rows | Group-Object Status | Sort-Object Name)) {
    $statusCounts[$group.Name] = $group.Count
}

$unresolvedStatuses = @(
    'AMBIGUOUS_BASENAME',
    'MISSING_BASENAME',
    'MISSING_PATH',
    'OUTSIDE_REFERENCE_ROOT'
)
$unresolved = @($rows | Where-Object { $_.Status -in $unresolvedStatuses })
$summary = [ordered]@{
    schemaVersion = 1
    generatedUtc = (Get-Date).ToUniversalTime().ToString('o')
    referenceRoot = $ReferenceRoot
    sourceXuiReferenceCount = $xuiReferences.Count
    totalAuditRows = $rows.Count
    statusCounts = $statusCounts
    unresolvedLocalReferenceCount = $unresolved.Count
    note = 'External sharedres:// references are host-provided contracts and are not counted as missing local files.'
}
$summary | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $summaryPath -Encoding UTF8

$rows | Group-Object Status | Sort-Object Name | Select-Object Name, Count | Format-Table -AutoSize
Write-Host "CSV: $csvPath"
Write-Host "Summary: $summaryPath"

if ($FailOnUnresolved -and $unresolved.Count -gt 0) {
    throw "BladeDash resource audit found $($unresolved.Count) unresolved local reference(s)."
}

[pscustomobject]@{
    Csv = $csvPath
    Summary = $summaryPath
    Rows = $rows.Count
    UnresolvedLocalReferences = $unresolved.Count
}
