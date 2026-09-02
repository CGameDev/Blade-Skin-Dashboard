# Phase G Console Test Plan — Installed-Game List + Launch

## Status

**REVISION 5 COMPLETED — FUNCTIONAL GATE 3 PASSED**

The 2026-09-02 run completed this procedure. Populated emulator and homebrew
lists rendered and navigated, B returned to the main shell, and SNES launched
after clean shutdown. Six Portuguese game-list command labels remain an open
localization fix; matched visual/interaction fidelity remains open.

This is testing-cadence gate 3. It preserves the approved main shell and
`gamelist.xur`, replaces the missing FSD `xbox360.xur` redirect with a
standalone adapter, scans configured roots off the render/input thread, and
queues a selected loose title through the existing clean-shutdown launch path.

It does not use the retired synthetic Blade UI, alter an approved XUR, or
depend on Aurora/FSD/CCLOS after launch.

## Package

```text
build/console-test/BladeDashboard-M000-PhaseG-R5-EnglishListBinding-20260901-222427/
```

```text
default.xex bytes: 1581056
default.xex SHA-256: f1337111355b9af55202fc93bf48543d3dcc26bf20e4625a41754c466f65524b
package files: 1143
manifest file records: 1142 (manifest self-hash intentionally excluded)
approved resource files: 1139
approved resource hash mismatches: 0
build warnings: 0
build errors: 0
```

The package is developer-private because it contains the owner-supplied
BladeDash resource tree. Do not redistribute it.

## Pre-test configuration

Open `Config/library_roots.txt` in the package and confirm that at least one
`XBOX360=` root contains a safe loose test title below it. The title directory
must contain `default.xex` within four directory levels of the configured root.
For the first Revision 5 check, also retain `HOMEBREW=Hdd1:\Apps`; the returned
R4 log proves launchable applications exist in the scanned inventory even
though its Xbox 360 selection contained zero items.

The supplied defaults include:

```text
XBOX360=Hdd1:\Games
XBOX360=Usb0:\Games
XBOX360=Usb1:\Games
XBOX360=Usb2:\Games
```

Add another local `Hdd`, `Hdd1`, or `Usb0`-`Usb2` root if the console uses a
different path. Do not point this test at container-only XBLA content; this
checkpoint intentionally supports loose images only.

## Installation

Copy the complete package to:

```text
Hdd1:\Apps\BladeDashboard\
```

Preserve the package layout. Replace the earlier test XEX and `Skins` payload.
Use the new `Config/library_roots.txt`; `Config/blade_dashboard.settings` may be
preserved if continued boot-count evidence is desired. Clear or preserve the
old log intentionally—the returned file must contain the Phase G start marker.

## Test procedure

1. Launch `default.xex`.
2. Confirm the approved main shell still renders and briefly verify all five
   main Blades still navigate.
3. Confirm the visible labels are restored and use English text. Return to the
   Games Blade, highlight `Homebrew`, and press A once. The R4 log found 13
   launchable entries but opened only the empty Xbox 360 category, so Homebrew
   is the first binding check. If the
   background scan is still running, leave the selection in place and allow up
   to 15 seconds for the queued request to open automatically.
4. Confirm the supplied game-list scene opens. When the configured root
   contains a valid loose title, confirm at least one folder name is visibly
   rendered in the left list. A nonzero counter with blank rows is a failure.
5. Move through at least two titles when available. Confirm the localized
   `N of total` counter follows selection.
6. Press B once. Confirm the main shell returns and remains navigable.
7. Open `Xbox 360` and record whether it is empty. Return to a populated
   category, select a safe entry, and press A / `Play`.
8. Confirm Blade Dashboard closes and the selected application/title starts.
9. Relaunch Blade Dashboard and use the controller Back/View button from the
   main shell for a clean exit.
10. Return the complete `Logs/blade_dashboard.log`, the tested
    `Config/library_roots.txt`, and uncropped captures of the populated list.

## Expected log sequence

```text
Starting Milestone 000 Phase G Revision 5 English text and list-binding checkpoint.
Storage alias: alias=Hdd1: target=\Device\Harddisk0\Partition1 existed=<n> created=<n> available=1 result=<HRESULT>.
Registered supplied Arial as the default and ConsoleFont compatibility alias; global text rendering preserved.
Registered 3 observed gamelist/GameControls compatibility classes.
Approved BladeDash main.xur initialized under the standalone host.
English text compatibility applied: scene=main.xur replacements=<nonzero> result=0x00000000.
Installed-game background scan completed: configured_roots=<n> existing_roots=<n> games=<n> capacity_reached=0.
Installed-game category total: category=HOMEBREW games=<nonzero>.
Discovered launchable entry: index=<index> category=HOMEBREW title=<folder name> image=<path>.
Opening approved gamelist.xur category=HOMEBREW items=<nonzero>.
Approved game-list selection: index=<index> title=<folder name>.
Approved gamelist.xur initialized through the standalone library adapter.
English text compatibility applied: scene=gamelist.xur replacements=<nonzero> result=0x00000000.
GamesList title supplied: item=<index> data=0 item_data=0 title=<folder name>.
Approved gamelist.xur returned to the main shell.
Queueing installed-game launch index=<index> title=<folder name> image=<device path>.
Installed-game launch queued; requesting clean XUI shutdown.
Milestone 000 Phase G Revision 5 English text and list-binding checkpoint stopped.
Dispatching queued launch after clean shutdown.
```

When the supplied `XN_PRESS` does not reach its compatibility host, expect this
additional diagnostic before the open marker:

```text
Controller A fallback routed focused category: id=XBox360Games category=XBOX360.
```

If A is pressed before scanning completes, also expect the queued-request and
scan-ready markers. The scan-completed line must occur before the successful
category-open line.

## Failure routing

- If A on a category still does nothing after 15 seconds, do not keep retrying.
  Return the complete new log. Absence of the fallback marker means the raw
  controller edge was not observed; a fallback marker without an open marker
  narrows the problem to scanning or `gamelist.xur` creation/navigation.
- If `XUI_ERR_CAST_FAILED` (`0x80300016`) returns, preserve the log; it means
  the corrected supplied `ScnGameView` tab-scene contract still has another
  runtime cast boundary.
- If every storage-alias line ends with `available=0`, return the complete log
  and state whether Blade Dashboard was launched from internal HDD or USB.
- If `Homebrew` reports `items=0` even though a category-total line is nonzero,
  return the tested roots file and log; that would be an adapter-selection
  mismatch. If only Xbox 360 is zero, the per-category/path lines distinguish
  an alternate loose root from unsupported container/GOD storage.
- If the counter is nonzero but title rows are blank, return an uncropped
  capture and the complete log. `GamesList title supplied` proves the source
  binding and narrows the remaining failure to typeface/presenter rendering;
  `title request ignored` now records only an invalid index/data/runtime
  contract; `item_data=0` alone is accepted.
- If the list opens but is otherwise black or incomplete, return an uncropped
  capture and log; do not substitute another game-list scene.
- If the selected title does not start and Aurora returns, the final dispatch
  marker distinguishes a post-shutdown platform/path failure from a UI event
  failure.

## Pass gate

Gate 3 passes functionally only when a real configured title is shown, B returns
to the main shell, and A launches the selected loose image after orderly Blade
shutdown. Matched known-good BladeDash captures are still required for visual
and interaction fidelity approval.

Revision 5 met the functional gate on 2026-09-02. This plan is retained as the
exact historical procedure and is no longer the active hardware request.
