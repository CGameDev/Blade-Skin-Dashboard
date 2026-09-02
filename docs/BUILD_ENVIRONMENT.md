# Build Environment — Milestone 000

## Checkpoint

- Recorded: 2026-09-01
- Updated: 2026-09-02 (Phase F console evidence)
- Blade Dashboard source: `main` at `d9bc65e`
- Host OS: Windows NT 10.0.19044.0, x64
- PowerShell: 7.6.5
- Primary acceptance display target: 16:9 HD / 720p

This record describes the environment actually inspected for Milestone 000. The
standalone BladeDash host passed its approved-splash console proof. The first
approved-main-shell Phase F package also passed functional hardware validation:
the scene presented and all five Blades were navigable.

## Approved BladeDash input

Developer-supplied source:

```text
F:\references\local\BladeDash(2005).zip
```

Verified SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

The 124,835,326-byte ZIP has 1,249 central-directory entries: 1,139 files and
110 directory entries. No unsafe traversal path or duplicate archive path was
found. Its only top-level entry is `BladeDash(2005)`.

The verified local golden copy is:

```text
references/local/BladeDash(2005).zip
```

It is read-only and has the same SHA-256 as the supplied source. The unflattened
extraction is at `references/local/BladeDash(2005)/`; both locations are ignored
by Git. The extraction contains 1,139 files and 109 directories below its root.

Local generated inventories:

```text
references/local/BladeDash(2005).manifest.csv
references/local/BladeDash(2005).manifest-summary.json
```

These inventories and raw resources remain developer-local and must not be
published automatically.

## Xbox 360 XDK installation

Resolved XDK/XEDK root:

```text
C:\Program Files (x86)\Microsoft Xbox 360 SDK
```

| Tool | File version | Bytes |
|---|---:|---:|
| `bin\win32\XuiTool.exe` | 2.0.21256.0 | 2,617,344 |
| `bin\win32\xuipkg.exe` | 2.0.21256.0 | 335,872 |
| `bin\win32\imagexex.exe` | 2.0.21256.0 | 196,608 |
| `bin\win32\cl.exe` | 16.00.11886.00 | 99,328 |
| `bin\win32\link.exe` | 10.00.11886.00 | 607,744 |
| `C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe` | 4.8.9037.0 | 255,920 |

The `XEDK` environment value resolves to the same SDK root.

## XuiTool validation

The installed `XuiTool.exe` was opened directly and tested with the approved
extraction.

Observed results:

- `skin.xui` opens as `Xbox UI Tool - skin.xui` with an active document,
  properties/timeline panes and Save enabled;
- the approved compiled `main.xur` opens concurrently as
  `Xbox UI Tool - main.xur` with its own active document and Save enabled;
- the approved compiled `SplashScreen.xur` opens as its own active document;
- XuiTool Save As produced an ignored XML inspection copy without changing the
  approved XUR; it exposes a 1280x720 `ScnSplashScreen` scene whose scene and
  two full-screen image layers all set `EnableEffects=true`;
- no load-error dialog appeared for either file;
- this proves that the approved source XUI and an individual compiled XUR can be
  inspected in the installed editor;
- no approved resource was saved or changed during the test.

Screen capture through Windows Graphics Capture fails for this legacy editor
with `0x80004002` (`No such interface supported`). Accessibility state and the
document window titles were used to record the result. This is a tooling capture
limitation, not evidence of an XUI load failure.

## Verified `xuipkg` interface and compile test

Only switches shown by the installed tool's own `xuipkg /?` output are treated
as supported. The observed options are `/A`, `/O`, `/U`, `/V`, `/R`, `/D`, `/E`,
`/I`, `/X`, `/XMA`, `/NOCONVERT`, `/NOLOGO` and `/C`.

From the extracted skin root, this supported command succeeds:

```powershell
& "$env:XEDK\bin\win32\xuipkg.exe" /NOLOGO /D /O <output.xzp> skin.xui
```

Result:

- archive: `build/milestone000/resource-validation/BladeDash-skin-relative-test.xzp`
- archive bytes: 869,860
- archive SHA-256: `00c2db29d83e6c4f891312c5dcb7378d2453959be35d3691ce5d86ea78fc6249`
- internal entry: `skin.xur`, 869,617 bytes

This artifact is ignored and is compile-path evidence only. It is not a
redistributable skin package and is not yet the selected deployment format.

## Resource-resolution audit

Run:

```powershell
./tools/Validate-BladeSkinResources.ps1
```

The audit checks literal resource references in approved `skin.xui` and
`skin.xml` without modifying either file. Current result:

| Status | Count |
|---|---:|
| Found exact path | 139 |
| Found by unique basename | 5 |
| Found directory | 1 |
| Host-provided `sharedres://` contract | 4 |
| Missing basename | 10 |
| Missing path | 19 |
| Outside reference root | 1 |

There are 179 audit rows and 30 unresolved local references. The resolved set
includes all configured DDS loading/missing artwork, the CoverFlow shader and
both meshes, the mesh-texture directory, file/TU list icons and other configured
images. The four `sharedres://` entries are host contracts rather than local
missing files.

Known approved-source gaps include:

- `Font/ERASBD.TTF`, declared by `skin.xml`, is absent; the supplied `Font`
  directory instead contains `arial.ttf`, `xenonclatin.ttf` and
  `xenonclatin.xtt`;
- two `Audio/!Metro_*.xma` paths are absent;
- several apparently historical image/music references embedded in `skin.xui`
  are absent;
- one source reference points outside the package to a former developer desktop
  (`volume_slider.JPG`).

The full generated CSV and JSON summary are under the ignored
`build/milestone000/resource-validation/` directory. These gaps are preserved as
baseline evidence. They must be traced to active/inactive scenes and host
fallback behavior before any change to the approved frontend.

The developer's extracted
`C:\Users\CGAmeDev\Downloads\shrdres.xzp(unpacked)` was inspected read-only.
Its observed contents are shared dashboard images, audio and localized XUS
resources rather than the XUI effects initialization contract needed by this
splash. `SplashScreen.xur` references local `fond.png` and `splash.dds`, both
already present in the approved package. No `shrdres` content was copied into
the repository or console-test package; it remains relevant to the later
`sharedres://` compatibility pass.

## External presentation strategy

Current provisional strategy:

1. keep the approved extracted resource tree external to `default.xex` during
   host bring-up;
2. load its existing XUR/resources from the standalone host without changing
   geometry or replacing scenes;
3. retain `skin.xui` as the editable source and use the verified `xuipkg`
   source-to-XUR path for generated resources;
4. evaluate a complete external XZP/repack workflow only after the host proves
   correct resource-provider semantics for images, DDS, XMA, fonts, shaders and
   meshes;
5. embed only a resource specifically proven unsafe or impossible to load
   externally.

Gate B is locally validated for XUI/XUR editability and source compilation. It
remains open for standalone-runtime resolution and console proof.

## Phase E console-test build

The selectively ported standalone host builds successfully with:

```powershell
./tools/build/Build-Project.ps1 -Configuration ConsoleTest -Rebuild
```

Current packaged build:

```text
build/console-test/BladeDashboard-M000-ApprovedSplash-20260901-192810/
```

`default.xex`:

```text
Bytes: 1548288
SHA-256: 23293e6c52850fc13347c55b7ba955f1c9e327f92f5ee89a659bda9b141810cc
```

`imagexex /DUMP` validates it as a title module with original PE name
`default.exe`, entry point `0x8214D1E8`, image size `0x190000`, hard-disk media
allowed, and approved 2.0.21256.0 XUI/runtime library imports. The XEX is an XDK
build for an XDK or homebrew-enabled JTAG/RGH console; it is not usable on an
unmodified retail console.

The private package contains 1,139 approved skin files under
`Skins/BladeDash(2005)/`. Every packaged skin-file hash matches the golden local
manifest. The host performs this sequence:

1. verify `skin.xur`, `SplashScreen.xur`, `splash.dds` and supplied
   `Font/arial.ttf` exist;
2. initialize the internally owned standalone renderer with
   `CXuiModule::Init(XuiD3DXTextureLoader)`, then enable the inherited effects
   flag so the standard helper loop performs its `PreRender` pass;
3. register the supplied Arial only as a temporary Phase E host default;
4. call `LoadSkin` for the approved `skin.xur`;
5. call `LoadFirstScene` for the approved `SplashScreen.xur`;
6. run the XUI effects pre-render/frame/render/present loop and exit cleanly on
   Back.

The temporary Arial default does not repair or conceal the absent
`Font/ERASBD.TTF` contract. It is limited to this first image-led scene proof and
must not be treated as the approved dashboard typography mapping.

Compile/package validation is complete. Revision 6 hardware capture proves the
supplied scene renders full-frame on the console. Its two-run log confirms both
resource loads, effects-frame presentation and clean Back exits; the settings
file confirms Blade-owned boot persistence. Gate E passed on 2026-09-01.

### First hardware result and compatibility revision

The first package (`20260901-182213`) was run twice. Both runs passed resource
preflight and temporary font registration, then failed at `LoadSkin` with:

```text
HRESULT 0x80300004 = XUI_ERR_CLASS_NOTREG
```

Approved `skin.xui` inspection identifies one `ClassOverride` value:
`ScnTabPresenter`, used 38 times on supplied `XuiScene` visuals. The revised host
registers a minimal `CXuiSceneImpl` compatibility class with that exact observed
name before `LoadSkin`. It adds no presenter data or behavior. The package and
hash above are the revised build awaiting retest.

The second package (`20260901-183426`) confirmed `ScnTabPresenter` registration
but returned the same class-not-registered error. The next exact optional class
is visible in the approved source: `skin.xui` contains 181 `XuiSoundXAudio`
objects. XDK sample applications explicitly call `XuiSoundXAudioRegister()`
before loading skins containing those objects. The current package/hash above
adds that XDK registration before `ScnTabPresenter`; no audio behavior or asset
was replaced.

Revision 3 (`20260901-185021`) then loaded both approved XURs and stayed in its
run loop, but produced a black screen. The log contained no failing HRESULT.
Inspection of the supplied `SplashScreen.xur` exposed the missing presentation
contract: the scene, `fond.png` image and `splash.dds` image all enable XUI
effects, while the basic module initializer never enables the pre-render pass.
The same scene declares `ClassOverride=ScnSplashScreen`.

Revision 4 attempted the XDK `InitEx` shader-compiler path, but both hardware
runs failed during XUI initialization with `E_INVALIDARG` because that API
requires a caller-supplied D3D/XUI device. No skin resource was reached.

Revision 5 restored the already proven internally owned standalone
renderer, opts its standard run loop into effects pre-render, registers the
exact observed splash scene class when absent, and retains scene-tree plus
pre-render/render/present diagnostics.

Revision 5 subsequently produced the first visible approved splash. The scene
occupied the upper-left 1280x720 region of an inferred 1920x1080 backbuffer,
leaving the right and bottom black. Revision 6 follows the installed XDK
Aquatica sample: it queries the actual backbuffer and applies the corresponding
1280x720 view transform for both pre-render and render. The supplied scene
geometry remains unchanged. The revision 6 hardware capture now shows the
approved splash filling the complete 16:9 output with the artwork centered and
no black right/bottom regions. The complete two-run log records boot counts 1
and 2, both XUR success markers, first-frame presentation, Back input and orderly
shutdown on both runs. The 16-byte settings file persists `BDS1`, version 3,
diagnostics enabled and boot count 2. Gate E is complete.

## Phase F approved-main-shell build

XuiTool saved an ignored XML inspection copy of the supplied `main.xur` without
modifying the approved binary:

```text
build/milestone000/xui-inspection/main-approved-inspected.xui
Bytes: 694714
SHA-256: b78e7fc77b895b23d91399fe78c623bf90d3364630428293325ee998e564027a
```

The inspected resource is a 1280x720 `MainScene` tab scene. Its direct `tab1`
child is a `ScnMain` tab scene with `TabCount=5`, `DefaultTab=3` and default
focus `Tab3`. Twelve distinct overrides are present. `ScnTabPresenter` was
already proven; the Phase F host adds registration-only implementations for the
eleven remaining observed names using their authored XUI scene/tab-scene/list
base types. It adds no data, messages, properties or synthetic controls.

Direct image/audio resolution for `main.xur` found 34 unique references. Two
are absent from the approved package and remain explicit `REFERENCE_GAP`:

```text
img-Xbox360Logo_Stacked.png
Images\Interface\Weather\Type\25.png
```

Current private package:

```text
build/console-test/BladeDashboard-M000-PhaseF-MainShell-20260901-201419/
default.xex bytes: 1548288
default.xex SHA-256: c2a441ab977340b626cb413fcb263c7006b917bd41da7fb29e6ca7e481c68d20
package files: 1142
manifest file records: 1141
approved skin files: 1139
approved skin hash mismatches: 0
```

The final package build log is
`build/logs/BladeDashboard-ConsoleTest-20260901-201412.log`; it contains zero
compiler/linker warnings and zero errors. `imagexex /DUMP` validates image size
`0x190000`, entry point `0x8214DD20`, hard-disk media support and approved
2.0.21256 XUI/runtime imports.

The 2026-09-02 hardware run passed functional Gate F. Its log loaded `skin.xur`
and `main.xur`, presented the first effects frame, reported a five-tab host and
navigated every zero-based runtime index from 0 through 4 before handling Back
and stopping cleanly. The authored `DefaultTab=3` is reported by the runtime as
`current=2`; initial focus was `XBox360Games`. No failure marker was logged.
The developer independently confirmed that the dashboard launched and all five
Blades were navigable.

Private evidence:

```text
build/milestone000/console-evidence/phase-f-main-shell.log
Bytes: 6517
SHA-256: d58afe51a4aaf3b8bfc553cf3edd798eee71c133181c9b848a3340e4a33a656b

build/milestone000/console-evidence/phase-f-main-shell.settings
Bytes: 16
SHA-256: d6fa108c88ff2ca78a0de49e83b1d5df19812bea0e17230bd4d1ecb7add76cd9
Decoded: BDS1, version 3, diagnostics enabled, boot count 1
```

This hardware result proves the standalone main-shell/navigation contract; it
does not grant visual-fidelity approval. Matched captures and F0/F1 comparison
work remain pending.

## Phase G installed-game list + launch build

XuiTool saved inspection-only XML copies of approved `gamelist.xur` and
`GameControls.xur`. Their metadata and exact observed controls are recorded in
`PHASE_G_GAME_LIBRARY_CONTRACT.md`; neither compiled XUR was changed.

Current private package:

```text
build/console-test/BladeDashboard-M000-PhaseG-InstalledGameLaunch-20260901-210223/
default.xex bytes: 1548288
default.xex SHA-256: 90e88860b47b02194cf3a95ae35ce707e7a36c65fb5b7291d4e97fcc41c06a8e
package files: 1143
manifest file records: 1142
approved skin files: 1139
approved skin hash mismatches: 0
```

The final build log is
`build/logs/BladeDashboard-ConsoleTest-20260901-210215.log`; it contains zero
compiler/linker warnings and zero errors. `imagexex /DUMP` validates image size
`0x190000`, entry point `0x821504C8`, hard-disk media support, and approved
2.0.21256 XUI/runtime imports.

The package adds only a Blade-owned `Config/library_roots.txt` beside the
unmodified 1,139-file approved skin tree. The service accepts 18 configured
local roots, scans no more than four directory levels, caps the presentation
model at 64 loose launchable images, and runs on the existing background
worker. Container-only XBLA launching remains unsupported and is not claimed.

Hardware status is `NOT_TESTED`. Follow `PHASE_G_CONSOLE_TEST_PLAN.md`; do not
advance Gate 3 from the static pass until a populated supplied game list and a
real selected-title launch are evidenced on console.

## Phase G revision 2 category-input build

The first Phase G hardware probe rendered the supplied main shell and showed
focus on `XBox360Games`, but A produced no visible navigation. No matching log
was available from the mounted console paths. The revision therefore addresses
the two bounded failure modes supported by the evidence: a missing ancestor
`XN_PRESS` notification and a category request made before the background scan
is ready. It does not modify the supplied XURs or broaden recognized controls.

Current private package:

```text
build/console-test/BladeDashboard-M000-PhaseG-R2-CategoryInput-20260901-211819/
default.xex bytes: 1548288
default.xex SHA-256: a6ccf87046e9994bb61ec7d1999d01be34298bba687a310a58fc6140ae12a124
package files: 1143
manifest file records: 1142
manifest missing/mismatched records: 0/0
approved skin files: 1139
approved skin hash mismatches: 0
```

The final build log is
`build/logs/BladeDashboard-ConsoleTest-20260901-211812.log`; the XDK build
completed with zero compiler/linker warnings and zero errors. `imagexex /DUMP`
validates image size `0x190000`, entry point `0x821507F0`, and approved
2.0.21256 XUI/runtime imports. Hardware status remains `NOT_TESTED` for this
revision; Gate 3 is still open.

## Phase G revision 3 scene-cast and storage build

Revision 2 hardware proved the category fallback and then failed every supplied
`gamelist.xur` creation with `0x80300016`. The installed XDK defines that result
as `XUI_ERR_CAST_FAILED`. The inspected resource's `GameListScene` is an
`XuiTabScene` with the `ScnGameView` override, while revision 2 registered the
override as a plain scene. Revision 3 corrects the compatibility base to the
observed most-derived tab-scene contract.

The returned scan also reported 18 configured roots but zero existing roots.
Revision 3 therefore initializes standard standalone aliases before starting
the background worker: `Hdd:`/`Hdd1:` map to
`\Device\Harddisk0\Partition1`, and `Usb0:`-`Usb2:` map to
`\Device\Mass0`-`Mass2`. Each existing/create/availability result is logged.

Current private package:

```text
build/console-test/BladeDashboard-M000-PhaseG-R3-SceneCastStorage-20260901-213125/
default.xex bytes: 1548288
default.xex SHA-256: 9e6466a8dc190c01e61d2ea0862e3da050b86eb58126f7370bc68416099810d0
package files: 1143
manifest file records: 1142
manifest missing/mismatched records: 0/0
approved skin files: 1139
approved skin hash mismatches: 0
```

The final build log is
`build/logs/BladeDashboard-ConsoleTest-20260901-213118.log`; the XDK build
completed with zero compiler/linker warnings and zero errors. `imagexex /DUMP`
validates image size `0x190000`, entry point `0x82150B00`, and approved
2.0.21256 XUI/runtime imports. Hardware status is `NOT_TESTED`; Gate 3 remains
open.

## Phase G revision 4 ConsoleFont title build

Revision 3 ran on hardware and proved all five supplied category scenes open
and navigate. One category displayed `1 de 5`, proving five discovered entries
were inserted, while every row title remained blank. The supplied list visual
explicitly requests `ConsoleFont`; the revision 3 host had registered only an
Arial default.

Matching original Freestyle source registers the default typeface under the
exact name `ConsoleFont` from `file://flash:\xenonjklatin.xtt` before loading
the skin. Revision 4 attempted that system locator and used the approved
package's existing `Font/xenonclatin.xtt` only as a logged fallback. It also
aligns `XM_GET_SOURCE_TEXT` with the original item-data/association-0 check and
logs the first four title callbacks. The approved XURs and font assets are not
modified.

Current private package:

```text
build/console-test/BladeDashboard-M000-PhaseG-R4-ConsoleFontTitles-20260901-215557/
default.xex bytes: 1548288
default.xex SHA-256: 6cf87b1d19d3deda2418961916d71aadc2fed71557a5dca156470ddcbb08a1e0
package files: 1143
manifest file records: 1142
manifest missing/mismatched records: 0/0
approved skin files: 1139
approved skin hash mismatches: 0
```

The build log is
`build/logs/BladeDashboard-ConsoleTest-20260901-215550.log`; the XDK rebuild
completed with zero compiler/linker warnings and zero errors. `imagexex /DUMP`
validates image size `0x190000`, entry point `0x82150C60`, hard-disk media
support and approved 2.0.21256 XUI/runtime imports. The subsequent hardware
result removed all text and exposed `item_data=0`; Revision 5 below supersedes
this package. Gate 3 remains open.

## Phase G revision 5 English/list-binding build

Revision 4 hardware preserved graphics and controls but removed every text
glyph after the system `ConsoleFont` became the global default. Its log also
proved the standalone list issues association 0 with `item_data=0`, which the
copied FSD guard rejected. Independent discovery completed with 18 configured
roots, 2 existing roots and 13 launchable entries; the only opened category was
Xbox 360 and it contained zero entries.

Revision 5 returns to the R3-proven supplied Arial global default and registers
`ConsoleFont` only as a non-default alias to the same renderable file. It serves
valid association-0 title requests for either item-data flag, logs category
totals and every discovered image path, and applies the owner-requested English
labels to instantiated scene objects at runtime. Approved XURs remain unchanged.

Current private package:

```text
build/console-test/BladeDashboard-M000-PhaseG-R5-EnglishListBinding-20260901-222427/
default.xex bytes: 1581056
default.xex SHA-256: f1337111355b9af55202fc93bf48543d3dcc26bf20e4625a41754c466f65524b
package files: 1143
manifest file records: 1142
manifest missing/mismatched records: 0/0
approved skin files: 1139
approved skin hash mismatches: 0
```

The final build log is
`build/logs/BladeDashboard-ConsoleTest-20260901-222419.log`; the XDK rebuild
completed with zero compiler/linker warnings and zero errors. `imagexex /DUMP`
validates image size `0x1A0000`, entry point `0x821513E8`, hard-disk media
support and approved 2.0.21256 XUI/runtime imports.

Revision 5 subsequently passed functional Gate 3 on hardware. The returned log
records 12 launchables across two available roots, populated emulator/homebrew
lists, complete row navigation, B returns, orderly shutdown and SNES dispatch;
the owner confirmed the launch succeeded. Evidence hashes are recorded in
`PHASE_G_CONSOLE_TEST_RESULTS.md`. Six command labels remain Portuguese, so
English localization and migration-fidelity approval remain open.
