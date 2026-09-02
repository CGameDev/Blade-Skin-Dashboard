# Milestone 000 Checkpoint — 2026-09-02

## Outcome

Milestone 000 has begun on the new working-skin transposition authority. The
retired from-scratch Blade implementation is quarantined and is not present in
the active tree.

Previous published baseline before this save point:

```text
Repository: CGameDev/Blade-Skin-Dashboard
Branch: main
Commit: d9bc65e
```

## Phase status

| Phase | Status | Evidence |
|---|---|---|
| A — source acquisition and golden copy | Complete; Gate A passed | Supplied ZIP and read-only local golden copy match the approved hash; extraction and per-file manifest created |
| B — XDK/XuiTool and external resources | Local tooling portion complete; runtime gate open | Approved `skin.xui` and `main.xur` open in installed XuiTool; relative `xuipkg` source compile succeeds; resource gaps recorded in `BUILD_ENVIRONMENT.md` |
| C — previous-work audit and CCLOS provenance | Complete for initial checkpoint | Legacy attempt stashed/audited; exact ConsoleCrateLive `main` SHA recorded before reuse |
| D — FSD dependency/contract map | Started | Initial `skin.xml` host concepts and all 58 root XURs inventoried in `FSD_COMPATIBILITY_MATRIX.md` |
| E — standalone proof of architecture | Complete; Gate E passed | Revision 6 renders the approved splash full-frame; two logged runs prove both XUR loads, effects presentation, clean Back exit and Blade-owned boot persistence |
| F — FSD compatibility/presentation bridge | Complete; Gate F passed | The approved main scene presented on console, reported five tabs, navigated runtime indices 0–4, handled Back and stopped cleanly without a logged FSD/Aurora dependency or failure |
| G — owner-approved feature mapping | In progress; functional Gate 3 passed | R5 discovered and displayed 12 loose launchables, navigated populated emulator/homebrew lists, returned through B and launched SNES after orderly shutdown; six Portuguese labels and fidelity comparison remain open |
| H and later | Not started | Complete the recorded localization fix before advancing to the next owner-approved feature slice |

## Gate A evidence

Supplied archive:

```text
F:\references\local\BladeDash(2005).zip
Bytes: 124835326
SHA-256: b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
Entries: 1249 (1139 files, 110 directory entries)
Unsafe paths: 0
Duplicate paths: 0
```

Golden local copy:

```text
references/local/BladeDash(2005).zip
Read-only: true
SHA-256: b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

The source ZIP was not changed. The extraction is unflattened and ignored by
Git.

Key approved-file hashes:

| File | Bytes | SHA-256 |
|---|---:|---|
| `skin.xui` | 7,224,751 | `d79715c0e36b08baa6fa09a5db2b5c8d7d3c193df0b159096d6476c296796fd1` |
| `skin.xml` | 7,299 | `a71f9a52062fa76995e74477f3c895c81d9790215d9b41ba8c789d3fb6ea1cec` |
| `skin.extract` | 6,097 | `a4354e7b0c556d698fdff94a4c539894c2f31c3dbb3de4ebd3937315445b5cc8` |
| `main.xur` | 104,766 | `c22b6dd2c4253ee5ec35a0bc0c3311ed539f0731a04b24be607381e629ca3d36` |
| `Settings/MenuSettings.xml` | 4,584 | `4e73c67d7c2b587286da3921e72f9eb331a29e3bd9c614d89459dbbc5d852f21` |

## XUI/tooling evidence

- XDK root: `C:\Program Files (x86)\Microsoft Xbox 360 SDK`
- XuiTool/xuipkg version: 2.0.21256.0
- approved `skin.xui`: opens successfully in XuiTool
- approved `main.xur`: opens successfully as an individual XuiTool document
- source compile: `skin.xui` -> debug XZP entry `skin.xur`, succeeds with
  installed `xuipkg`
- approved resources saved/edited during validation: none

The reproducible static audit is `tools/Validate-BladeSkinResources.ps1`.
Thirty local references remain unresolved: the absent configured ERASBD font,
28 other absent source-XUI paths, and one outside-root developer-desktop path.
Four additional `sharedres://` references are explicit host contracts. The
approved frontend has not been altered to conceal these findings.

## Previous-work disposition

The former implementation was captured in:

```text
stash@{0}: retired-from-scratch-audit-snapshot-20260901
object: cdd652d2a958652b02d7aa62f9d98b1f773d68f2
```

Reusable runtime/build candidates are listed in `LEGACY_ATTEMPT_AUDIT.md`. The
synthetic GAME-001 Blade, generic colored panels, substitute-font presentation,
Retail-6770-led state specs and retired packaging rules remain quarantined.

## Backend provenance

The required authoritative source was resolved before any backend reuse:

```text
Repository: CGameDev/ConsoleCrateLive
Branch: main
Commit: e8440b672c88ab07dab2e2a52bbcb55c809336d9
```

No ConsoleCrateLive subsystem has been copied or ported at this checkpoint.

## Fidelity status

No new production UI was created and no BladeDash XUR, geometry, timeline,
audio, texture or navigation resource was replaced. Revision 5 does apply the
owner-requested English text properties at runtime and aliases the missing
`ConsoleFont` name to the supplied renderable Arial; neither is a font/text
fidelity approval. Gate E proves the splash.
Gate F now proves the approved main shell loads and its five-Blade navigation
runs on the standalone host. This is a functional runtime result, not visual-
fidelity approval: matched per-Blade captures, overlays/differences and F0/F1
grading remain open.

## Open blockers and gaps

- the main root/class/tab/focus graph and basic five-tab navigation are proven,
  but its FSD data/action messages and exact input/transition semantics remain
  unextracted;
- external host handling for `sharedres://` and the absent declared ERASBD font
  is unproven;
- the complete runtime resource-provider/package strategy remains provisional;
- revision 3 ran on console and proved both approved XURs initialize, but its
  basic XUI initialization left the effects pre-render path disabled;
- Phase G revision 2 proved A/category routing but supplied game-list creation
  failed with `XUI_ERR_CAST_FAILED`; it also proved all configured standalone
  storage roots were unavailable. Revision 3 fixed both boundaries: all five
  categories opened, and one list contained five selectable rows, but the
  explicit `ConsoleFont` title presenters rendered blank. Revision 4 made the
  system font global and removed all text; its log found 13 launchables, zero
  in the opened Xbox 360 category, and an `item_data=0` source request. Revision
  5 restores visible list text, accepts that callback, renders 12 discovered
  titles across the emulator/homebrew categories and launches SNES after clean
  shutdown. Six command labels remain Portuguese;
- one CCLOS-backed feature remains a later Milestone 000 gate.

## Next permitted work

Resume with the six-label game-list localization gap (`Opções`, `Favoritos`,
`Voltar`, `Jogar`, `Menu Favoritos`, and `Ordenar`) while preserving the
approved XURs. Then continue the next owner-approved Phase G service slice.
Capture all five main Blades and matched game-list states at a later
visual-comparison checkpoint before granting fidelity approval.

## Phase F main-shell test artifact

```text
Package: build/console-test/BladeDashboard-M000-PhaseF-MainShell-20260901-201419/
default.xex bytes: 1548288
default.xex SHA-256: c2a441ab977340b626cb413fcb263c7006b917bd41da7fb29e6ca7e481c68d20
Package files: 1142
Manifest file records: 1141
Approved skin files: 1139
Approved skin hash mismatches: 0
Build warnings/errors: 0/0
Hardware status: FUNCTIONAL PASS; GATE F COMPLETE (2026-09-02)
```

The ignored XuiTool inspection copy of approved `main.xur` is 694,714 bytes
with SHA-256
`b78e7fc77b895b23d91399fe78c623bf90d3364630428293325ee998e564027a`.
It proves a `MainScene` root, nested `ScnMain` tab host, five authored tabs,
default tab 3 and twelve distinct class overrides. Eleven were new beyond the
already proven `ScnTabPresenter`; all were mapped to their observed XUI base
types without invented properties or behavior.

Two scene references are absent from the approved package:
`img-Xbox360Logo_Stacked.png` and
`Images\Interface\Weather\Type\25.png`. They are logged as `REFERENCE_GAP` and
were not substituted.

The console evidence is preserved privately at:

```text
build/milestone000/console-evidence/phase-f-main-shell.log
Bytes: 6517
SHA-256: d58afe51a4aaf3b8bfc553cf3edd798eee71c133181c9b848a3340e4a33a656b

build/milestone000/console-evidence/phase-f-main-shell.settings
Bytes: 16
SHA-256: d6fa108c88ff2ca78a0de49e83b1d5df19812bea0e17230bd4d1ecb7add76cd9
```

The log proves `skin.xur` and `main.xur` initialization, the first effects
frame, a five-tab host, navigation through every runtime index (`0`, `1`, `2`,
`3`, `4`), Back input and orderly shutdown with zero failure marker. Authored
`DefaultTab=3` appears at runtime as zero-based `current=2`; the initial focused
control is `XBox360Games`. The settings record is `BDS1`, version 3,
diagnostics enabled and boot count 1, consistent with a fresh Config state.
The developer also confirmed visually that the dashboard launched and all five
Blades were navigable. No complete matched per-Blade capture set was supplied,
so this evidence passes functional Gate F only.

## Phase G revision 5 test artifact

```text
Package: build/console-test/BladeDashboard-M000-PhaseG-R5-EnglishListBinding-20260901-222427/
default.xex bytes: 1581056
default.xex SHA-256: f1337111355b9af55202fc93bf48543d3dcc26bf20e4625a41754c466f65524b
Package files: 1143
Manifest file records: 1142
Manifest missing/mismatched records: 0/0
Approved skin files: 1139
Approved skin hash mismatches: 0
Build warnings/errors: 0/0
Hardware status: REVISION 5 FUNCTIONAL PASS; PARTIAL ENGLISH LOCALIZATION
```

Revision 2 proved raw A routing for all five supplied category IDs, but every
supplied game-list creation failed with XDK-defined `XUI_ERR_CAST_FAILED`. Its
returned log also proved that all 18 configured roots were unavailable because
the standalone process inherited none of Aurora/FSD's device aliases. Revision
3 corrected `ScnGameView` from a plain-scene registration to the supplied
outermost `XuiTabScene` contract, suppresses delayed duplicate activation, and
establishes/logs standard HDD/USB aliases before discovery. On hardware all
five category menus opened; the `1 de 5` capture proves populated rows, but the
labels were blank. Revision 4 then removed all global text and rejected the
observed standalone `item_data=0` title callback, although discovery found 13
launchables. Revision 5 restores the renderable Arial default, aliases
`ConsoleFont`, accepts that callback, localizes instantiated text toward
English, and records per-category/path diagnostics. Its hardware run found 12
launchables (5 emulators and 7 homebrew applications), visibly rendered and
navigated both populated lists, returned through B, and launched SNES after
clean shutdown. The owner confirmed every functional test passed. Six command
labels remain Portuguese, so localization and matched migration-fidelity
approval remain open. No supplied XUR changed. Returned evidence is retained
under `build/milestone000/console-evidence/`; exact hashes are recorded in
`PHASE_G_CONSOLE_TEST_RESULTS.md`. Gate 3 is functionally passed.

## Phase E build artifact

```text
Package: build/console-test/BladeDashboard-M000-ApprovedSplash-20260901-192810/
default.xex bytes: 1548288
default.xex SHA-256: 23293e6c52850fc13347c55b7ba955f1c9e327f92f5ee89a659bda9b141810cc
Package files: 1142
Approved skin files: 1139
Approved skin hash mismatches: 0
Hardware status: REVISION 6 PASSED; GATE E COMPLETE
```

This build uses no generated/recreated Blade scene. It calls the XDK-supported
`LoadSkin`/`LoadFirstScene` sequence against the supplied resources in an external
`Skins/BladeDash(2005)` tree.

The first hardware attempt reached `LoadSkin` but returned
`XUI_ERR_CLASS_NOTREG` (`0x80300004`) on both runs. Approved-source inspection
identified `ScnTabPresenter` as the only class override (38 uses). The revised
build registered that exact minimal scene façade but exposed a second optional
class requirement. The approved source contains 181 `XuiSoundXAudio` objects;
revision 3 also performed the XDK-documented XAudio sound-class registration.
That revision loaded both approved XURs and stayed active, but rendered black.
The supplied splash scene inspection shows `EnableEffects=true` on the scene and
both full-screen image layers; the host's basic initializer did not activate
XUI pre-render. Revision 4's `InitEx` attempt failed
before class registration with `E_INVALIDARG` because the standalone host did
not supply the D3D/XUI device required by that API. Revision 5 restores the
proven internally owned renderer and directly enables its inherited effects
pre-render loop, registers the exact observed `ScnSplashScreen` override when
needed, and retains scene/render diagnostics.

Revision 5 then visibly rendered the approved splash and `Idle` status. The
scene appeared at authored 1280x720 size in the upper-left of the 1080p output,
leaving black on the right and bottom. Revision 6 applies the exact backbuffer
view-scaling pattern demonstrated by the installed XDK Aquatica sample during
both effects pre-render and final render. Its capture fills the complete 16:9
output with centered approved artwork, closing the revision 5 scale defect.
The complete revision 6 log then proved both XUR load markers, first-frame
presentation, two clean Back exits and boot counts 1 then 2. The persisted
settings file contains the expected `BDS1`/version 3/diagnostics enabled/boot
count 2 values. Gate E is passed; Phase F is now permitted.
