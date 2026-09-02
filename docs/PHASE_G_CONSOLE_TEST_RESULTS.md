# Phase G Console Test Results — Installed-Game List + Launch

## Current result

**REVISION 5 FUNCTIONAL PASS — PARTIAL ENGLISH LOCALIZATION REMAINS**

| Field | Result |
|---|---|
| Package | `BladeDashboard-M000-PhaseG-R5-EnglishListBinding-20260901-222427` |
| `default.xex` SHA-256 | `f1337111355b9af55202fc93bf48543d3dcc26bf20e4625a41754c466f65524b` |
| XDK build | Passed; 0 warnings, 0 errors |
| XEX validation | Passed; image size `0x1A0000`, entry `0x821513E8`, approved 2.0.21256 runtime imports |
| Approved resource preservation | 1,139/1,139 files present; 0 hash mismatches |
| Package manifest | 1,142 listed payload files; 0 missing/mismatched records |
| Scan-root configuration | 18 configured roots; 2 existed; 12 loose launchables discovered |
| Hardware game-list result | Passed: 5 emulator and 7 homebrew titles visibly rendered and navigated with correct counters; Xbox 360/XBLA/Xbox Classic each reported 0 |
| Hardware selected-title launch | Passed: owner confirmed SNES launched after orderly Blade shutdown; log records queue, stop, and dispatch |
| Localization | Partial: main/list content is visible and mostly English; six command labels remain Portuguese |
| Gate 3 | Functionally passed; migration-fidelity approval remains open |

## Revision 1 hardware result

The owner confirmed that the approved main shell still rendered and that focus
reached `XBox360Games`, but pressing A produced no visible action. This is a
functional failure at the category-activation boundary; no game-list or launch
success is inferred. The supplied uncropped capture is preserved privately at:

```text
build/milestone000/console-evidence/phase-g-r1-main-category-no-action.png
Bytes: 1891340
SHA-256: 8458b596927b7d1de9254341f51c9782b4b64474b66b928d1ddba83ed6bb13c3
```

No matching console log was available in the mounted paths for this result, so
the precise distinction between an unreceived `XN_PRESS` and a scan-timing
drop could not be made from runtime telemetry. Revision 2 covers both observed
possibilities without changing the approved resources: it routes an A-button
edge from the already-proven controller service when focus is one of the five
exact supplied category IDs, and it retains the request until the background
scan reaches `ScanReady`.

## Revision 2 hardware result

Revision 2 proved that raw A input and exact focused-category resolution work:
the log repeatedly records `Controller A fallback routed focused category` for
all five supplied controls. It then reaches the intended scene boundary but
every `XuiSceneCreate(gamelist.xur)` call fails with `0x80300016`, which the
installed XDK defines as `XUI_ERR_CAST_FAILED`.

The approved inspection copy explains the mismatch: `ScnGameView` is applied
to the `GameListScene` `XuiTabScene`, while Revision 2 registered that class as
a plain `XuiScene`. Revision 3 registers the observed most-derived tab-scene
base. It also suppresses the delayed notification duplicate visible after each
raw A fallback.

The same log reports `configured_roots=18 existing_roots=0 games=0`. A
standalone XEX does not inherit the `Hdd1:`/`Usb*:` aliases created by
Aurora/FSD. Revision 3 establishes the standard Xbox device mappings before
the background scan and logs each alias result independently.

Private returned evidence:

```text
phase-g-r2-blade_dashboard.log
Bytes: 14930
SHA-256: 1e63f989bc8cbf8bf5fde5b74c77e0127c98fec83700d23b744ea6b4a74533e4

phase-g-r2-library_roots.txt
Bytes: 779
SHA-256: 592d124b7760d1372a413f22ba079d691ba2d953665e26984da515e76802a63e

phase-g-r2-blade_dashboard.settings
Bytes: 16
SHA-256: d6fa108c88ff2ca78a0de49e83b1d5df19812bea0e17230bd4d1ecb7add76cd9
Decoded: BDS1, version 3, diagnostics enabled, boot count 1

phase-g-r2-game-category-still-active.png
Bytes: 1883634
SHA-256: ad5a05e6366486e777535c6d791eb64e2db02919800181160e44e9c047b69504
```

All four files are retained under
`build/milestone000/console-evidence/`. The log ends with a clean Back exit.

## Revision 3 hardware result

The owner confirmed that all five category menus opened and could be navigated.
One returned capture shows `1 de 5`, proving that the standalone storage scan,
category adapter, `GamesList` initialization, item insertion, selection and
counter update all reached a five-item presentation model. Another category
correctly shows `0 de 0`. The rows in the five-item category are present but
their title presenters are blank, so this is not an HDD discovery failure.

The approved `Button_GameList` title presenters explicitly name
`ConsoleFont`; the approved `skin.xui` contains 188 such font references. The
Revision 3 host registered only `Arial`. The matching original Freestyle host
source resolves the missing contract: it registers the default typeface under
the exact name `ConsoleFont` before loading the skin. The original `GamesList`
source also confirms main-title data association 0 with item-data requests,
matching the standalone adapter's binding.

Revision 4 attempted that exact host contract without modifying the approved
XURs. It used the original Freestyle system locator first and logged initial
title callbacks. The resulting hardware regression and corrected standalone
contract are recorded below; this earlier hypothesis is not treated as a pass.

No complete R3 log, settings file or tested roots file was available at the
mounted paths for this report. The three uncropped captures are preserved
privately at:

```text
phase-g-r3-main-game-categories.png
Bytes: 1889956
SHA-256: 759ff8586745f5126a0054279e29b2c7695466a4d0c5ab1c08f38d62cf43261a

phase-g-r3-empty-category.png
Bytes: 1745706
SHA-256: cbd5c9620b387a9ef65848450b8d0c6582f1f424367afcf3847cedfb90c41ecd

phase-g-r3-five-blank-items.png
Bytes: 1760225
SHA-256: a48a0d85adbdfa9dde0f550f0592ea4081d23d666cec971274569a11340d4512
```

## Revision 4 hardware result

Revision 4 regressed all main-shell and game-list text while leaving the
approved artwork, focus chrome and button icons visible. The log proves the
original system `ConsoleFont` descriptor registered successfully, but using it
as the global default produced no rendered glyphs in this standalone host.
Revision 5 restores the R3-proven supplied Arial default and registers
`ConsoleFont` only as a non-default compatibility alias to that same working
font. This keeps default and explicit-font presenters on one proven renderable
path.

The log also resolves the list callback: XUI requested item 0, association 0,
with `item_data=0`. Revision 4 copied the original FSD `item_data=1` guard and
therefore rejected the standalone request. Revision 5 accepts either item-data
flag when the observed association and visible index are valid. It resets the
bounded callback diagnostic for every newly opened list.

Discovery did not fail. The background service reported 18 configured roots,
2 existing roots and 13 launchable entries. The owner opened the Xbox 360
category twice; both opens correctly logged `items=0`. No other category was
opened during this run, so the 13 entries were never requested for display.
Revision 5 logs totals per category plus every discovered title and image path.
The next procedure opens Homebrew first to test the already-proven application
inventory, then checks Xbox 360 separately. Container/GOD titles remain outside
this loose-image checkpoint.

At the owner's direction, Revision 5 applies English replacements to the
existing instantiated main and game-list scene objects. The approved XUR files
remain byte-identical; this is a runtime localization layer, not a rebuilt UI.

Private returned evidence:

```text
phase-g-r4-blade_dashboard.log
Bytes: 7080
SHA-256: 8c47b62f0b865f6b210d5cbc78a0ef90b1ca6f8c4223afced83645f6132d651a

phase-g-r4-blade_dashboard.settings
Bytes: 16
SHA-256: d6fa108c88ff2ca78a0de49e83b1d5df19812bea0e17230bd4d1ecb7add76cd9
Decoded: BDS1, version 3, diagnostics enabled, boot count 1

phase-g-r4-main-no-text.png
Bytes: 1808665
SHA-256: 708ba8b8953af6d2745c66cfae864591626a394cd5318192517863c9cf438d17

phase-g-r4-gamelist-no-text.png
Bytes: 1713010
SHA-256: 65c1e70159f36fb0fa9c0e56ac42bf990a6b8918bbed718659f0fd1478cc6ec0
```

## Revision 5 hardware result

The owner reported that all functional test steps passed. The log independently
records 18 configured roots, 2 existing roots and 12 launchable loose images:
5 emulators and 7 homebrew applications. Both populated categories supplied
visible item titles through association 0, selection traversed all rows, and
the counters displayed `1 of 5` and `1 of 7`. Empty Xbox 360, XBLA and Xbox
Classic categories each matched their logged zero totals.

The owner selected SNES. The log records the selected image, orderly XUI
shutdown, the Revision 5 stop marker and post-shutdown dispatch; the owner
confirmed that the target launched. This satisfies the functional Gate 3
contract for a real configured loose image.

The English localization pass is incomplete. The supplied game-list command
chrome still displays `Opções`, `Favoritos`, `Voltar`, `Jogar`,
`Menu Favoritos`, and `Ordenar`. The list title, dynamic item titles, counter,
release/rating fields and unavailable states are English. This is an open
localization discrepancy and prevents fidelity/localization approval, but it
does not invalidate the installed-list and launch functional pass.

Private returned evidence:

```text
phase-g-r5-blade_dashboard.log
Bytes: 24816
SHA-256: e43d97646d9f78bcc694abaf4985834b1a8fe315de390764e4a264187d967427

phase-g-r5-blade_dashboard.settings
Bytes: 16
SHA-256: d6fa108c88ff2ca78a0de49e83b1d5df19812bea0e17230bd4d1ecb7add76cd9
Decoded: BDS1, version 3, diagnostics enabled, boot count 1

phase-g-r5-library_roots.txt
Bytes: 779
SHA-256: 592d124b7760d1372a413f22ba079d691ba2d953665e26984da515e76802a63e

phase-g-r5-emulators-populated-partial-english.png
Bytes: 1800707
SHA-256: f6d36d406456451b7ae1d4ebc8aa931fee466195a108f29bcff9f714b9fa8248

phase-g-r5-homebrew-populated-partial-english.png
Bytes: 1802748
SHA-256: 3b1df0f44f4ac21e777197f39a19365a0554c8dde943758046988d1061234fbd
```

## Static evidence

- approved `gamelist.xur`: 20,400 bytes, SHA-256
  `238c7e8b91b2ae544ebb3fa9e701c6c9d2b9ffcd53fae67518f018affb16cb5d`;
- approved `GameControls.xur`: 7,663 bytes, SHA-256
  `b04de199e90b6bcd724e41c50c9cc94dd1ec87e692ec6523a11b236059d08265`;
- ignored XuiTool inspection copies and exact contracts are recorded in
  `PHASE_G_GAME_LIBRARY_CONTRACT.md`;
- the five approved main category controls all target absent `xbox360.xur`;
  the compatibility layer recognizes only those exact IDs and navigates to
  supplied `gamelist.xur` without modifying or creating a XUR;
- revision 2 preserves the authored `XN_PRESS` handler but adds a controller-
  edge fallback because the R1 hardware result proved that notification did
  not produce navigation; a per-frame guard prevents duplicate activation;
- a category request made while the background scan is running is queued and
  opened on `ScanReady` instead of being silently discarded;
- `ScnGameView`, `GamesList`, and `ScnGameControls` are registered from the
  observed resource contracts; revision 3 corrects `ScnGameView` to the
  supplied outermost `XuiTabScene` contract;
- standard `Hdd:`, `Hdd1:`, and `Usb0:`-`Usb2:` aliases are established before
  scanning using their observed Xbox kernel device mappings;
- list title data association 0 is backed by a fixed-capacity presentation
  model, and the existing `Jogar` action queues its selected image;
- R4 hardware proves the system `ConsoleFont` default removes all rendered
  text in this standalone host and proves list callbacks use `item_data=0`;
  R5 therefore retains the renderable Arial default, aliases `ConsoleFont`,
  and binds valid association-0 requests independently of the item-data flag;
- an owner-requested English runtime localization pass changes text properties
  only after the approved scenes instantiate; packaged XUR hashes are unchanged;
- enumeration executes on the existing background queue, not XUI input/render;
- launch is dispatched through `XLaunchNewImage` only after XUI, settings,
  input, and background services shut down cleanly;
- the authoritative CCLOS snapshot remains clean at commit
  `e8440b672c88ab07dab2e2a52bbcb55c809336d9`; exact loose-image discovery and
  launch provenance is recorded in `BACKEND_PROVENANCE.md`.

Revision 5 functionally passes Gate 3 for loose-image discovery, visible list
binding, navigation, return, orderly shutdown and launch. The next fix is the
six-label English localization gap; metadata/artwork, container discovery and
matched visual/interaction fidelity remain separately open.
