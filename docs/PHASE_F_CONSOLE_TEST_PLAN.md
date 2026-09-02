# Phase F Console Test Plan — Approved Main Shell

## Status

**COMPLETED — FUNCTIONAL GATE F PASSED 2026-09-02**

This test advances from the completed Gate E splash proof to the supplied
`main.xur`. It does not use the retired synthetic Blade implementation and does
not alter any approved BladeDash geometry, animation, texture or XUR.

## Package

```text
build/console-test/BladeDashboard-M000-PhaseF-MainShell-20260901-201419/
```

```text
default.xex bytes: 1548288
default.xex SHA-256: c2a441ab977340b626cb413fcb263c7006b917bd41da7fb29e6ca7e481c68d20
package files: 1142
approved resource files: 1139
approved resource hash mismatches: 0
```

The package is developer-private because it contains the owner-supplied
BladeDash resource tree. Do not redistribute it.

## Installation

Copy the complete package into the existing deployment root:

```text
Hdd1:\Apps\BladeDashboard\
```

Overwrite the prior `default.xex` and approved `Skins` payload, but preserve the
existing `Config` and `Logs` directories. The persisted boot count may therefore
continue from the Gate E value rather than restart at 1.

## Test procedure

1. Launch `default.xex` and wait at least 15 seconds.
2. Capture the complete screen without cropping or overscan.
3. Record whether the approved main shell is visible, partial, distorted or
   black.
4. Press D-pad Up, Down, Left and Right once each, then LB and RB once each.
5. Record every visible focus or Blade/tab change; do not infer behavior that is
   not visible.
6. Press Back to request a clean exit.
7. Return the complete `Logs\blade_dashboard.log` and the screen capture.

## Expected success markers

```text
Starting Milestone 000 Phase F approved BladeDash main-scene host proof.
Resolved 11 observed main.xur compatibility classes without invented behavior.
XUI standalone renderer initialized; supplied-scene effects pre-render is enabled.
XUI backbuffer 1920x1080; approved 1280x720 canvas view scale 1.500x1.500.
REFERENCE_GAP: approved main.xur references absent img-Xbox360Logo_Stacked.png; no substitute was introduced.
REFERENCE_GAP: approved main.xur references absent Weather Type/25.png; no substitute was introduced.
Approved BladeDash skin.xur loaded.
Approved BladeDash main.xur initialized under the standalone host.
Approved main.xur tab host resolved: count=5 current=2.
First XUI effects frame rendered and presented.
Approved main navigation state: tab=<index> focus=<id> class=<class>.
Controller Back pressed; requesting clean exit.
Milestone 000 Phase F approved BladeDash main-scene host proof stopped.
```

The runtime proves the authored `DefaultTab=3` resolves to zero-based
`current=2`, the third tab. Navigation state lines change only when the actual
XUI focus or selected tab changes.

## Failure handling

If the XEX returns to Aurora, remains black or renders only part of the scene,
return the complete log and capture. The next change must address the exact
logged host/resource contract. Do not replace the main scene with generated UI
and do not fill the two recorded resource gaps with guessed assets.

## Phase F test gate

This build passed the functional checkpoint: the approved `main.xur` visibly
rendered, its scene graph/default focus/first frame were logged, all five tabs
were visited, and Back exited cleanly. Gate F is therefore passed as an
architecture/navigation gate. Matched per-Blade captures remain required for
visual-fidelity approval.
