# Phase F Console Test Results — Approved Main Shell

## Current result

**FUNCTIONAL RUNTIME PASS — GATE F PASSED; MATCHED VISUAL CAPTURES PENDING**

| Field | Result |
|---|---|
| Package | `BladeDashboard-M000-PhaseF-MainShell-20260901-201419` |
| `default.xex` SHA-256 | `c2a441ab977340b626cb413fcb263c7006b917bd41da7fb29e6ca7e481c68d20` |
| Approved `main.xur` visible | Yes; developer confirmed the dashboard launched |
| `main.xur` success marker | Present |
| Authored tab host `count=5` | Passed |
| Runtime initial tab | `current=2`, the zero-based third authored tab |
| Initial focus | `XBox360Games`, class `XuiNavButton` |
| Blade navigation | Passed; runtime log visits tabs 0, 1, 2, 3 and 4 |
| Exact input-by-input mapping | Not separately captured |
| Back clean exit | Passed |
| Gate F | **Passed 2026-09-02 as a functional architecture/navigation gate** |

## Static evidence

- XuiTool inspection copy: 694,714 bytes,
  SHA-256 `b78e7fc77b895b23d91399fe78c623bf90d3364630428293325ee998e564027a`;
- root: `XuiTabScene`, ID `MainScene`, class override `MainScene`, default
  focus `tab1`;
- nested main tab host: `XuiTabScene`, ID `tab1`, class override `ScnMain`,
  `TabCount=5`, `DefaultTab=3`, default focus `Tab3`;
- twelve distinct class overrides are present; `ScnTabPresenter` was already
  implemented for Gate E and eleven exact registration-only façades were added;
- all 1,139 packaged approved resource hashes match the golden extraction;
- build completed with zero compiler/linker warnings and zero errors;
- `imagexex` validates the XEX and its approved 2.0.21256 XUI/runtime imports.

Two paths referenced by the supplied main scene are absent from the approved
package: `img-Xbox360Logo_Stacked.png` and
`Images\Interface\Weather\Type\25.png`. They remain `REFERENCE_GAP`; no
substitute was added.

## Hardware result

The developer reported that the dashboard launched and all five Blades were
navigable. The log independently proves:

- approved `skin.xur` and `main.xur` loaded;
- the main tab host instantiated with count 5 and runtime current tab 2;
- the first effects frame rendered and presented;
- navigation visited every zero-based tab index: `0, 1, 2, 3, 4`;
- focus moved through authored controls including `XBox360Games`, `Button2`,
  `Settings`, `legend_a`, `control_ListItem`, and `ProfileSignIn`;
- Back requested exit and the host stopped cleanly;
- no failure, failed HRESULT or initialization error was logged.

The runtime corrects an earlier static-test expectation: XUI reports
`DefaultTab=3` as zero-based `current=2`, meaning the authored third tab. The
settings file contains `BDS1`, version 3, diagnostics enabled and boot count 1;
this package was tested from a fresh Config state.

Preserved ignored evidence:

| File | Bytes | SHA-256 |
|---|---:|---|
| `phase-f-main-shell.log` | 6,517 | `d58afe51a4aaf3b8bfc553cf3edd798eee71c133181c9b848a3340e4a33a656b` |
| `phase-f-main-shell.settings` | 16 | `d6fa108c88ff2ca78a0de49e83b1d5df19812bea0e17230bd4d1ecb7add76cd9` |

Gate F is passed as a functional standalone navigation gate because the
unchanged approved `main.xur` supplies the geometry/animations and all five
authored tabs run under the new host. This is not a visual-fidelity approval:
no matched capture set was attached, so per-Blade comparison and F0/F1 grading
remain open before any screen can be called fidelity-approved.
