param(
    [ValidateSet('Debug', 'Release', 'ConsoleTest')]
    [string]$Configuration = 'Debug',

    [switch]$Rebuild
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

$repositoryRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$solutionPath = Join-Path $repositoryRoot 'BladeDashboard.sln'

function Resolve-XdkRoot {
    $candidates = @($env:XEDK)
    $registryPaths = @(
        'HKLM:\SOFTWARE\WOW6432Node\Microsoft\Xbox\2.0\SDK',
        'HKLM:\SOFTWARE\Microsoft\Xbox\2.0\SDK'
    )

    foreach ($registryPath in $registryPaths) {
        $registryValue = Get-ItemProperty $registryPath -ErrorAction SilentlyContinue
        if ($null -ne $registryValue -and $null -ne $registryValue.PSObject.Properties['InstallPath']) {
            $candidates += $registryValue.InstallPath
        }
    }

    foreach ($candidate in $candidates) {
        if ($candidate -and (Test-Path -LiteralPath $candidate -PathType Container)) {
            return (Resolve-Path -LiteralPath $candidate).Path
        }
    }

    throw 'Xbox 360 XDK not found. Install the XDK or define XEDK.'
}

$xdkRoot = Resolve-XdkRoot
$msbuildPath = Join-Path $env:WINDIR 'Microsoft.NET\Framework\v4.0.30319\MSBuild.exe'
$requiredPaths = @(
    $msbuildPath,
    (Join-Path $xdkRoot 'bin\win32\cl.exe'),
    (Join-Path $xdkRoot 'bin\win32\link.exe'),
    (Join-Path $xdkRoot 'bin\win32\imagexex.exe'),
    (Join-Path $xdkRoot 'include\xbox\xui.h'),
    (Join-Path $xdkRoot 'lib\xbox\xuirun.lib')
)

foreach ($requiredPath in $requiredPaths) {
    if (-not (Test-Path -LiteralPath $requiredPath)) {
        throw "Required build prerequisite is missing: $requiredPath"
    }
}

$env:XEDK = $xdkRoot
$logDirectory = Join-Path $repositoryRoot 'build\logs'
New-Item -ItemType Directory -Path $logDirectory -Force | Out-Null
$timestamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$logPath = Join-Path $logDirectory "BladeDashboard-$Configuration-$timestamp.log"
$target = if ($Rebuild) { 'Rebuild' } else { 'Build' }

$arguments = @(
    $solutionPath,
    "/t:$target",
    "/p:Configuration=$Configuration",
    '/p:Platform=Xbox 360',
    '/m:1',
    '/verbosity:minimal'
)

Write-Host "Building Blade Dashboard ($Configuration|Xbox 360)..."
Write-Host "XDK: $xdkRoot"
Write-Host "Log: $logPath"

Push-Location $repositoryRoot
try {
    & $msbuildPath @arguments 2>&1 | Tee-Object -FilePath $logPath
    $buildExitCode = $LASTEXITCODE
}
finally {
    Pop-Location
}

if ($buildExitCode -ne 0) {
    throw "MSBuild failed with exit code $buildExitCode. See $logPath"
}

$xexPath = Join-Path $repositoryRoot "build\$Configuration\bin\default.xex"
if (-not (Test-Path -LiteralPath $xexPath -PathType Leaf)) {
    throw "Build reported success but default.xex is missing: $xexPath"
}

$hash = (Get-FileHash -LiteralPath $xexPath -Algorithm SHA256).Hash.ToLowerInvariant()
Write-Host 'Build succeeded.'
Write-Host "XEX: $xexPath"
Write-Host "XEX SHA-256: $hash"

[pscustomobject]@{
    Configuration = $Configuration
    Xex = $xexPath
    XexSha256 = $hash
    Log = $logPath
}
