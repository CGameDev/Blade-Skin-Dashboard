# Console Test Results — Milestone 000 Approved Splash Host

## Current result

**REVISION 6 PASSED — GATE E COMPLETE**

| Field | Result |
|---|---|
| Package | `BladeDashboard-M000-ApprovedSplash-20260901-192810` |
| `default.xex` SHA-256 | `23293e6c52850fc13347c55b7ba955f1c9e327f92f5ee89a659bda9b141810cc` |
| Console model | Not recorded |
| Kernel/dashboard version | Not recorded |
| Exploit/devkit environment | Homebrew-enabled environment required by the tested XEX; exact configuration not recorded |
| Display mode | 1920x1080 backbuffer; 16:9 capture |
| Launcher used | Aurora console-test workflow |
| Approved splash visible | Yes; full-frame, centered and correctly scaled in revision 6 capture |
| `skin.xur` success marker | Present in both runs |
| `SplashScreen.xur` success marker | Present in both runs |
| Back clean exit | Passed in both runs |
| Second-run boot count | Passed; counts 1 then 2, persisted value 2 |
| Gate E | **Passed 2026-09-01** |

## Revision 1 result

The `20260901-182213` package was launched twice. Both attempts returned to
Aurora during initialization. The log proved settings persistence (boot counts 1
and 2) and recorded the same failure each time:

```text
Approved BladeDash skin.xur load failed (HRESULT=0x80300004)
Application initialization failed (HRESULT=0x80300004)
```

The installed XDK defines `0x80300004` as `XUI_ERR_CLASS_NOTREG`. Static
inspection found the exact approved dependency: `ScnTabPresenter` is the only
`ClassOverride` in `skin.xui`, occurring on 38 supplied `XuiScene` visuals.

Revision 2 registers a minimal `ScnTabPresenter` scene façade before loading the
skin. Its presentation-model/data behavior remains deliberately unimplemented
until observed.

## Revision 2 result

Revision 2 ran twice and logged the new `ScnTabPresenter` registration marker,
proving the revised XEX was deployed. Both runs still stopped at `LoadSkin` with
`XUI_ERR_CLASS_NOTREG`.

The approved source contains 181 `XuiSoundXAudio` elements. The XDK's own
Aquatica sample registers this optional class explicitly before loading a skin
containing it. Revision 3 adds `XuiSoundXAudioRegister()` before the already
observed `ScnTabPresenter` registration and calls the corresponding unregister
function during shutdown. Its hardware result is recorded below.

## Revision 3 result

Revision 3 no longer returned to Aurora. The supplied log records successful
`skin.xur` and `SplashScreen.xur` initialization, and the background queue probe
completed. The display remained black until the user exited through the Guide.
This proves that the previous class-registration failures were resolved and
narrows the failure to the presentation path. It does not pass Gate E.

XuiTool was used to save the supplied binary `SplashScreen.xur` as an ignored,
non-production XML inspection copy. The observed scene is 1280x720, declares
`ClassOverride=ScnSplashScreen`, and has `EnableEffects=true` on the scene and
both full-screen image layers. The host had used `CXuiModule::Init`, for which
the installed XDK leaves effects pre-render disabled. Revision 4 attempted to:

- initializes through `CXuiModule::InitEx` with `XuiD3DXTextureLoader` and the
  XDK `D3DXCompileShader` callback, enabling the effects pre-render pass;
- registers a minimal exact-name `ScnSplashScreen` scene compatibility class
  only when the runtime does not already provide it;
- logs the instantiated scene tree and one-shot pre-render/render/present
  failures;
- logs `First XUI effects frame rendered and presented.` after the first
  successful frame presentation.

The approved XUR, images, skin and other resources were not modified.

## Revision 4 result

Revision 4 launched twice and returned to Aurora after a black screen. Both
runs stopped before class registration or resource loading with:

```text
XUI initialization failed (HRESULT=0x80070057)
Application initialization failed (HRESULT=0x80070057)
```

`0x80070057` is `E_INVALIDARG`. The installed XDK API and helper implementation
show why: `InitEx` forwards its structure to `XuiRenderInitEx`, which requires a
caller-supplied D3D/XUI device. Passing the null device used by the standalone
`CXuiModule::Init` path is invalid.

Revision 5 restores the proven standalone initializer and explicitly enables
the inherited host-loop `m_bUsingEffects` flag after successful initialization.
This makes the standard `CXuiModule::Run` loop call the retained diagnostic
`PreRender` override without replacing the internally owned D3D device or
requiring a caller-supplied one. The effects diagnosis remains hardware-
unconfirmed at that point; the revision 5 result is recorded below.

## Revision 5 result

Revision 5 visibly rendered the supplied BladeDash splash for the first time.
The capture contains the approved Xbox 360 splash artwork, the `Idle` loading
status and the expected green/gray background. This closes the prior black-
screen presentation blocker and proves that the standalone renderer plus
effects pre-render path can present the approved resource.

The captured image is 1595x899. The rendered 16:9 scene occupies approximately
two-thirds of each axis in the upper-left, which is consistent with the
approved 1280x720 scene being drawn without scaling into a 1920x1080
backbuffer. The right and bottom portions remain black. Gate E is therefore not
yet complete, and the current console log was unavailable after the removable
drive was disconnected.

The installed XDK's Aquatica sample documents the matching host behavior: query
the render-target size and apply a view matrix scaling 1280x720 coordinates to
the actual backbuffer. Revision 6 applies that same XDK pattern during both the
effects pre-render and final render passes. It changes no supplied XUI geometry
or resource.

## Revision 6 result

Revision 6 visibly renders the approved BladeDash splash across the complete
16:9 output. The supplied Xbox 360 artwork and `Idle` status are centered, the
background reaches all four edges, and the revision 5 black regions at the
right and bottom are gone. This confirms the XDK-documented backbuffer view
transform fixed the presentation-scale defect without altering the supplied
scene geometry.

The developer-provided capture is preserved in the ignored local evidence tree:

```text
build/milestone000/console-evidence/revision-6-full-backbuffer.png
Bytes: 1741926
SHA-256: 1d952a4ecfe1ad2490dc5412158628f9c762fcd9df593cc7c98f3cb652d2ad67
Captured dimensions: 1595x899
```

## Revision 6 runtime and persistence evidence

The final log contains two complete runs with no failure marker. Each run
records the XUI renderer, 1920x1080 backbuffer, 1.500x view scale, both approved
resource-load successes, instantiated `ScnSplashScreen`, background queue
completion, first presented effects frame, Back request, and orderly proof-host
shutdown. Boot counts advance from 1 to 2.

The 16-byte settings file matches the source-defined big-endian schema:

```text
42 44 53 31 00 00 00 03 00 00 00 01 00 00 00 02
magic: BDS1
version: 3
diagnosticsEnabled: 1
consoleTestBootCount: 2
```

Preserved ignored evidence:

| File | Bytes | SHA-256 |
|---|---:|---|
| `revision-6-full-backbuffer.png` | 1,741,926 | `1d952a4ecfe1ad2490dc5412158628f9c762fcd9df593cc7c98f3cb652d2ad67` |
| `revision-6-blade_dashboard.log` | 4,224 | `04224431f34d67aaf3d5c0afe4f938d8b7504f26de95aec24806e31992c971e9` |
| `revision-6-blade_dashboard.settings` | 16 | `be40fc8499af414bec20a8cba72e04eebaca64a4f03e8e2451bf9c6895886ba1` |

All Gate E pass criteria are satisfied. This proves the approved supplied
splash can be hosted, rendered and exited by the standalone XEX with Blade-owned
persistence. It does not claim that the later main-scene/FSD compatibility
bridge or production services are complete.

## Evidence captured

- complete uncropped screen capture;
- complete `Logs/blade_dashboard.log` from two runs;
- persisted `Config/blade_dashboard.settings`;
- relevant launcher/runtime observations.

The pass is based on console capture and runtime evidence, not compilation or
package inspection alone.
