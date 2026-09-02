# Console Test Plan — Milestone 000 Approved Splash Host

## Status

**REVISION 6 PASSED — GATE E COMPLETE 2026-09-01**

This test is the first Phase E proof. It does not use the retired synthetic Blade
UI. It loads the developer-approved `BladeDash(2005)` skin and splash resources
unchanged.

## Package

```text
build/console-test/BladeDashboard-M000-ApprovedSplash-20260901-192810/
```

```text
default.xex bytes: 1548288
default.xex SHA-256: 23293e6c52850fc13347c55b7ba955f1c9e327f92f5ee89a659bda9b141810cc
approved resource files: 1139
approved resource hash mismatches: 0
```

The package is developer-private because it contains the owner-supplied
BladeDash resource tree. Do not redistribute it.

## Target

- Xbox 360 XDK, or homebrew-enabled JTAG/RGH Xbox 360 capable of launching an
  XDK-built unsigned XEX;
- 16:9 HD / 720p for the primary acceptance run;
- no Freestyle Dash, Aurora or CCLOS application required after launch.

## Installation

Copy the complete package folder without flattening or renaming its contents to:

```text
Hdd1:\Apps\BladeDashboard\
```

The required runtime layout is:

```text
Hdd1:\Apps\BladeDashboard\default.xex
Hdd1:\Apps\BladeDashboard\Skins\BladeDash(2005)\skin.xur
Hdd1:\Apps\BladeDashboard\Skins\BladeDash(2005)\SplashScreen.xur
Hdd1:\Apps\BladeDashboard\Skins\BladeDash(2005)\splash.dds
```

## Test procedure

1. Launch `default.xex`.
2. Wait at least ten seconds after the first visible frame.
3. Capture the complete 16:9 screen with no crop or overscan.
4. Record whether the approved BladeDash splash is visible, partially visible,
   distorted or black.
5. Press Back to request a clean exit.
6. Launch the build a second time, wait again, then press Back.
7. Retrieve the complete `Logs\blade_dashboard.log` and
   `Config\blade_dashboard.settings`.

## Expected success log

```text
Starting Milestone 000 approved BladeDash resource-host proof.
Milestone 000 console-test boot count: 1.
XUI standalone renderer initialized; supplied-scene effects pre-render is enabled.
XUI backbuffer 1920x1080; approved 1280x720 canvas view scale 1.500x1.500.
Registered XDK XuiSoundXAudio class for supplied skin audio objects.
Registered observed ScnTabPresenter compatibility class.
Registered observed ScnSplashScreen compatibility class.
Registered supplied Arial only as the Phase E host default; the absent ERASBD contract remains unresolved.
Approved BladeDash skin.xur loaded.
Approved BladeDash SplashScreen.xur initialized under the standalone host.
Scene node depth=0 class=ScnSplashScreen id=XuiScene1 shown=1 bounds=1280.0x720.0 opacity=1.000.
First XUI effects frame rendered and presented.
Background queue probe completed.
Controller Back pressed; requesting clean exit.
Milestone 000 approved BladeDash resource-host proof stopped.
```

If the platform already registers that exact class, the splash-class line is
`ScnSplashScreen was already provided by the runtime.` instead.

The second clean run should report boot count `2`.

## Failure handling

If the screen is black or the XEX returns immediately, preserve and return the
complete log. The host logs separate HRESULTs for:

- approved resource preflight;
- XUI initialization;
- temporary supplied-font registration;
- `skin.xur` load;
- `SplashScreen.xur` load;
- effects pre-render;
- final render/present.
- backbuffer query and the reported 1280x720 view scale.

Do not replace the failed resource with a generated scene. The next change must
address only the observed missing host/resource contract.

## Pass criteria

Gate E passes only when:

- `default.xex` launches without FSD/Aurora/CCLOS;
- the supplied approved splash scene visibly renders;
- both resource-load success markers appear;
- Back exits cleanly;
- the second-run boot count proves Blade-owned Config persistence;
- the capture and environment facts are recorded in
  `docs/CONSOLE_TEST_RESULTS.md`.

Revision 6 satisfied every criterion above. The preserved capture shows the
approved scene full-frame; the two-run log contains both resource-load markers,
first-frame presentation and two orderly Back exits; and the settings file
persists boot count 2. See `docs/CONSOLE_TEST_RESULTS.md` for hashes and exact
evidence.
