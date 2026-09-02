param(
    [switch]$CreateArchive
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

$repositoryRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$buildScript = Join-Path $PSScriptRoot 'Build-Project.ps1'
$approvedZip = Join-Path $repositoryRoot 'references\local\BladeDash(2005).zip'
$approvedResourceRoot = Join-Path $repositoryRoot 'references\local\BladeDash(2005)'
$libraryRootsSource = Join-Path $repositoryRoot 'config\library_roots.txt'
$expectedZipHash = 'b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b'

foreach ($requiredPath in @(
    $approvedZip,
    $approvedResourceRoot,
    (Join-Path $approvedResourceRoot 'skin.xur'),
    (Join-Path $approvedResourceRoot 'main.xur'),
    (Join-Path $approvedResourceRoot 'gamelist.xur'),
    (Join-Path $approvedResourceRoot 'GameControls.xur'),
    (Join-Path $approvedResourceRoot 'Font\arial.ttf'),
    $libraryRootsSource
)) {
    if (-not (Test-Path -LiteralPath $requiredPath)) {
        throw "Required approved input is missing: $requiredPath"
    }
}

$actualZipHash = (Get-FileHash -LiteralPath $approvedZip -Algorithm SHA256).Hash.ToLowerInvariant()
if ($actualZipHash -ne $expectedZipHash) {
    throw "Approved BladeDash ZIP hash mismatch. Expected $expectedZipHash, got $actualZipHash."
}

$build = & $buildScript -Configuration ConsoleTest -Rebuild
$xexSource = Join-Path $repositoryRoot 'build\ConsoleTest\bin\default.xex'
if (-not (Test-Path -LiteralPath $xexSource -PathType Leaf)) {
    throw "Console-test XEX is missing: $xexSource"
}

$timestamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$packageName = "BladeDashboard-M000-PhaseG-R5-EnglishListBinding-$timestamp"
$packageRoot = Join-Path $repositoryRoot 'build\console-test'
$stagingDirectory = Join-Path $packageRoot $packageName
$skinDestination = Join-Path $stagingDirectory 'Skins\BladeDash(2005)'
$archivePath = Join-Path $packageRoot "$packageName.zip"

if (Test-Path -LiteralPath $stagingDirectory) {
    throw "Refusing to overwrite an existing package directory: $stagingDirectory"
}

New-Item -ItemType Directory -Path $skinDestination -Force | Out-Null
New-Item -ItemType Directory -Path (Join-Path $stagingDirectory 'Config') -Force | Out-Null
Copy-Item -LiteralPath $xexSource -Destination (Join-Path $stagingDirectory 'default.xex')
Copy-Item -Path (Join-Path $approvedResourceRoot '*') -Destination $skinDestination -Recurse -Force
Copy-Item -LiteralPath $libraryRootsSource -Destination (Join-Path $stagingDirectory 'Config\library_roots.txt')

$readme = @"
Blade Dashboard — Milestone 000 Phase G Revision 5 English List-Binding Test
Package: $packageName

PRIVATE TEST MATERIAL
  This package contains the developer-supplied BladeDash(2005) resource tree.
  Do not redistribute it unless asset redistribution is separately approved.

PURPOSE
  Prove that the standalone host can preserve the approved main shell, open the
  supplied gamelist.xur, populate it from loose installed titles, and launch a
  selected default.xex/default.xbe without Freestyle Dash, Aurora, or CCLOS at
  runtime.

  Revision 5 restores the proven Arial default so all dashboard text renders,
  registers ConsoleFont only as an alias instead of replacing the global
  default, applies English labels to the existing scene objects at runtime,
  and accepts the item_data=0 source callback observed on the standalone host.
  It also logs per-category discovery totals and launchable paths.

INSTALL
  Copy this entire folder without changing its layout to:
    Hdd1:\Apps\BladeDashboard\

RUN
  Launch default.xex on an XDK or homebrew-enabled JTAG/RGH Xbox 360.
  An unmodified retail console cannot run this XDK-built unsigned XEX.

SCAN ROOTS
  Edit Config\library_roots.txt before launch if your loose games are outside
  the supplied Hdd1:\Games / Usb*:\Games defaults. The background scan is
  bounded to four directory levels and 64 launchable entries. XBLA containers
  are not part of this checkpoint because XLaunchNewImage needs a loose image.

EXPECTED
  1. The supplied BladeDash main shell renders with visible English labels and
     its authored focus.
  2. Highlight Homebrew and press A. The R4 log proved 13 launchable entries
     were discovered across the configured roots, while Xbox 360 specifically
     had zero. Homebrew is therefore the first list-binding verification.
     If the background scan is not ready yet, the request is retained and the
     list opens automatically when scanning completes.
  3. At least one application folder name should appear. Navigate the list and
     verify the localized "N of total" counter changes.
  4. Press B once and verify the main shell returns. Enter Xbox 360 and record
     whether it remains empty; the new category/path diagnostics identify the
     exact classification and image paths without guessing.
  5. Enter a populated category again, highlight a safe test entry, and press
     A / Play.
     The Blade host should shut down cleanly and launch that title.
  6. Relaunch Blade Dashboard and use the controller Back/View button only
     from the main shell to request a clean application exit.

  Also recheck all five main Blades. This is a functional Gate-3 probe, not a
  visual-fidelity approval and not a synthetic replacement menu.

  The approved package itself lacks img-Xbox360Logo_Stacked.png and
  Images\Interface\Weather\Type\25.png. The log records these as REFERENCE_GAP;
  no replacement assets were added.

LOG
  Inspect Logs\blade_dashboard.log. Expected success markers:
    Starting Milestone 000 Phase G Revision 5 English text and list-binding checkpoint.
    Registered supplied Arial as the default and ConsoleFont compatibility alias; global text rendering preserved.
    English text compatibility applied: scene=main.xur replacements=<count> result=0x00000000.
    Storage alias: alias=Hdd1: ... available=1 ...
    Installed-game background scan completed: ... games=<count> ...
    Installed-game category total: category=<category> games=<count>.
    Discovered launchable entry: index=<index> category=<category> title=<title> image=<path>.
    XUI standalone renderer initialized; supplied-scene effects pre-render is enabled.
    XUI backbuffer <width>x<height>; approved 1280x720 canvas view scale <x>x<y>.
    Registered XDK XuiSoundXAudio class for supplied skin audio objects.
    Registered observed ScnTabPresenter compatibility class.
    Resolved 11 observed main.xur compatibility classes without invented behavior.
    Registered 3 observed gamelist/GameControls compatibility classes.
    Approved BladeDash skin.xur loaded.
    Approved BladeDash main.xur initialized under the standalone host.
    Approved main.xur tab host resolved: count=5 current=2.
    Approved main navigation state: tab=<index> focus=<id> class=<class>.
    First XUI effects frame rendered and presented.
    Controller A fallback routed focused category: id=<category-control> ...
      (This line appears when the supplied XN_PRESS does not reach its host.)
    Opening approved gamelist.xur category=<category> items=<count>.
    Approved gamelist.xur initialized through the standalone library adapter.
    English text compatibility applied: scene=gamelist.xur replacements=<count> result=0x00000000.
    GamesList title supplied: item=<index> data=0 item_data=<0-or-1> title=<title>.
    Approved game-list selection: index=<index> title=<title>.
    Approved gamelist.xur returned to the main shell.
    Queueing installed-game launch index=<index> title=<title> image=<path>.
    Installed-game launch queued; requesting clean XUI shutdown.
    Dispatching queued launch after clean shutdown.

  If the list is empty, a category press does nothing, the screen is black, or
  launch returns to the prior dashboard, return the complete log plus
  Config\library_roots.txt. The log identifies the exact resource, scan, or
  launch boundary that failed.

PERSISTENCE
  Config\blade_dashboard.settings is written on clean shutdown. A second run
  should increment the logged Milestone 000 console-test boot count.
"@
$readmePath = Join-Path $stagingDirectory 'README-CONSOLE-TEST.txt'
$readme | Set-Content -LiteralPath $readmePath -Encoding UTF8

$gitCommit = (& git -C $repositoryRoot rev-parse HEAD).Trim()
$gitStatus = @(& git -C $repositoryRoot status --porcelain --untracked-files=all)
$payloadFiles = @(Get-ChildItem -LiteralPath $stagingDirectory -Recurse -File | Sort-Object FullName)
$fileRecords = foreach ($file in $payloadFiles) {
    $relativePath = $file.FullName.Substring($stagingDirectory.Length + 1).Replace('\', '/')
    [ordered]@{
        path = $relativePath
        bytes = $file.Length
        sha256 = (Get-FileHash -LiteralPath $file.FullName -Algorithm SHA256).Hash.ToLowerInvariant()
    }
}

$manifest = [ordered]@{
    schemaVersion = 1
    packageName = $packageName
    generatedUtc = (Get-Date).ToUniversalTime().ToString('o')
    milestone = '000'
    hardwareStatus = 'NOT_TESTED'
        visualStatus = 'APPROVED_GAMELIST_FUNCTIONAL_PROBE_NOT_FIDELITY_APPROVED'
    source = [ordered]@{
        repository = 'https://github.com/CGameDev/Blade-Skin-Dashboard.git'
        commit = $gitCommit
        workingTreeDirty = $gitStatus.Count -gt 0
    }
    approvedBladeDash = [ordered]@{
        zipSha256 = $actualZipHash
        resourceRoot = 'Skins/BladeDash(2005)'
        skin = 'Skins/BladeDash(2005)/skin.xur'
        firstScene = 'Skins/BladeDash(2005)/main.xur'
        resourcesModified = $false
        redistributionStatus = 'DEVELOPER_PRIVATE_TEST_MATERIAL'
    }
    runtime = [ordered]@{
        entryPoint = 'default.xex'
        fsdRequired = $false
        auroraRequired = $false
        cclosApplicationRequired = $false
        log = 'Logs/blade_dashboard.log'
        settings = 'Config/blade_dashboard.settings'
        libraryRoots = 'Config/library_roots.txt'
        libraryLimit = 64
        scanDepthLimit = 4
        looseImagesOnly = $true
        cleanExitInput = 'Controller Back button'
    }
    manifestSelfHashExcluded = $true
    files = @($fileRecords)
}
$manifestPath = Join-Path $stagingDirectory 'manifest.json'
$manifest | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $manifestPath -Encoding UTF8

if ($CreateArchive) {
    Compress-Archive -LiteralPath $stagingDirectory -DestinationPath $archivePath -CompressionLevel Optimal
}

$xexHash = (Get-FileHash -LiteralPath (Join-Path $stagingDirectory 'default.xex') -Algorithm SHA256).Hash.ToLowerInvariant()
Write-Host 'Milestone 000 console-test package created.'
Write-Host "Folder: $stagingDirectory"
Write-Host "default.xex SHA-256: $xexHash"
if ($CreateArchive) {
    Write-Host "Archive: $archivePath"
}

[pscustomobject]@{
    Folder = $stagingDirectory
    DefaultXexSha256 = $xexHash
    Manifest = $manifestPath
    Archive = if ($CreateArchive) { $archivePath } else { $null }
}
