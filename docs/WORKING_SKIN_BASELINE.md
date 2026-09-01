# Working Skin Baseline — BladeDash(2005)

## Status

**Canonical implementation seed for the standalone Blade dashboard.**

This document changes the implementation strategy of this repository. The dashboard is no longer to be recreated from scratch when the developer-verified working `BladeDash(2005)` skin already provides the corresponding UI, animation, navigation resource, audio, geometry, or presentation state.

The historical Retail 2.0.6770 dashboard remains the **fidelity validation target**, but the working skin is now the **primary implementation starting point**. If older repository guidance conflicts with this rule, this document wins for implementation strategy.

## Developer-verified source package

Expected developer-local path:

```text
references/local/BladeDash(2005).zip
```

Expected extraction path:

```text
references/local/BladeDash(2005)/
```

These paths are intentionally under `references/local/`, which is excluded from Git.

Verified package fingerprint:

```text
SHA-256: b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

Use the fingerprint to ensure Codex is working from the exact package approved by the project owner.

## Package inventory from analysis

The supplied ZIP is about 120 MiB compressed and about 144 MiB extracted, with 1,139 files in 110 directories.

Important resource counts:

```text
786 .png
120 .dds
75  .xma
58  .xur
29  .jpg
17  .xml
11  .html
9   .inc
6   .css
6   .js
4   .fx
3   .x
2   .ttf
1   .xui
1   .xus
1   .xtt
1   .wmv
```

This is an already-authored XUI presentation implementation, not a screenshot/reference pack.

### Key files

`skin.xui`

- 7,224,751 bytes
- 277,528 lines
- XUI canvas version `000c`
- 448 direct top-level resources/visuals
- includes Blade geometry, highlights, jewels, bend/straight blade states, labels, list controls, loading visuals, timeline animation data, sound triggers, panels and dialogs
- SHA-256: `d79715c0e36b08baa6fa09a5db2b5c8d7d3c193df0b159096d6476c296796fd1`

`skin.xml`

- identifies the skin as `PreNXE 2005`
- skin compatibility `Min='3' Max='3'`
- version `3.0.735`
- exposes FSD host-facing configuration contracts
- SHA-256: `a71f9a52062fa76995e74477f3c895c81d9790215d9b41ba8c789d3fb6ea1cec`

`skin.extract`

- identifies the extracted base as `Default (Extracted)`
- author `TeamFSD`
- version `3.0`
- confirms a Freestyle 3/FSD skin architecture rather than an Aurora-only runtime

`main.xur`

- compiled primary scene resource
- SHA-256: `c22b6dd2c4253ee5ec35a0bc0c3311ed539f0731a04b24be607381e629ca3d36`

`Settings/MenuSettings.xml`

- demonstrates data/config-driven menu/tab presentation
- SHA-256: `4e73c67d7c2b587286da3921e72f9eb331a29e3bd9c614d89459dbbc5d852f21`

## Existing compiled scene set

The package already contains scene resources for major dashboard functions, including `main.xur`, `SplashScreen.xur`, `Achievements.xur`, `avatar.xur`, game-list variants, `gameinfo.xur`, `GameControls.xur`, `savedgames.xur`, `TitleUpdateManager.xur`, `Trainers.xur`, `CopyDVD.xur`, file-manager scenes, path-manager scenes, settings scenes, weather, music, utilities, updater and other support scenes.

Codex must inventory and reuse these resources before creating replacement scenes.

## FSD host contracts visible in the skin

The package does not contain the Freestyle Dash executable/source code. Therefore the standalone XEX must replace the FSD runtime behind the UI.

The skin configuration exposes useful contract boundaries such as:

- `CoverFlow`
- `VideoManager`
- `AchievementManager`
- `HTTPServer`
- `ScnGameView`
- `GamesList`
- `FilesList`
- `ActiveTUList`
- `SrcFilesList`
- `DestFilesList`
- `PathList`
- `ScnProfile`
- `ScnPopup`
- `ScnSysInfo`
- `ScnTabPresenter`
- `ScnTeamFSD`
- `ScnWeather`

Do not redesign the UI to avoid these contracts. Implement a compatibility layer behind the existing UI.

## Target architecture

```text
BladeDash(2005) XUI/XUR/resources
              |
              v
Blade presentation compatibility layer
              |
              v
Blade-specific adapters
              |
   +----------+----------+----------+
   |          |          |          |
 Library  Marketplace Profiles  System/Storage
 Launch   Downloads   Achievements Network/Settings
   \          |          |          /
    +---------+----------+---------+
              |
              v
CCLOS/ConsoleCrate backend logic
+ Xbox 360/XDK platform services
              |
              v
Standalone BladeDashboard.xex
```

**Reuse CCLOS backend capability, not CCLOS visual components.**

## Reuse first

Codex should preserve wherever technically possible:

- Blade geometry and XUI visual definitions;
- scene resources that already load correctly;
- focus/highlight states;
- transitions/timelines;
- button/list visuals;
- audio cues;
- backgrounds, jewels and separators;
- image/texture resources;
- menu geometry and controller glyphs;
- loading visuals and dialogs;
- coverflow meshes/shaders where usable;
- existing visual configuration XML.

Do not replace working UI merely because newly written code would be cleaner.

## Newly implemented/adapted runtime

The standalone product still needs owned code for:

- XEX entry/lifecycle;
- XUI initialization/resource loading;
- scene host/navigation coordination;
- controller input routing;
- FSD-compatible scene/control binding layer;
- installed-content discovery and launch;
- profile/achievement/system/storage/network data;
- settings persistence;
- background work/tasking;
- HTTP/network capability;
- ConsoleCrate Marketplace and download adapters;
- Title Update integration where retained;
- cache/artwork lookup;
- logging, diagnostics and error handling.

Where CCLOS already has a proven backend implementation, port/reuse the backend logic through a Blade-specific adapter instead of rebuilding the same subsystem.

## XuiTool rule

The owner has verified that the supplied skin is editable in XuiTool. Codex must inspect the actual developer-local XDK/XuiTool environment and test this real package before assuming a resource needs to be recreated.

Required first checks:

1. locate `references/local/BladeDash(2005).zip`;
2. verify SHA-256;
3. extract without changing directory structure;
4. preserve an untouched golden copy;
5. locate `skin.xui` and `main.xur`;
6. open/test the package with the installed XuiTool workflow;
7. document which `.xur`/`.xui` assets can be opened, edited, regenerated or repacked;
8. create a derivative working copy for standalone-host testing.

Do not invent XuiTool command-line flags.

## Public-repository boundary

The working ZIP contains third-party/historical resources whose redistribution status has not been established here. Keep the owner-supplied package under `references/local/` during development, do not commit the raw ZIP automatically, do not upload XDK binaries, and do not assume every supplied font/resource is redistributable. Record hashes/manifests in Git and add only intentionally approved distributable resources.

This does **not** mean Codex should ignore the package. It remains the implementation baseline on the developer machine.

## Precedence over the old from-scratch strategy

For any UI/state already implemented in `BladeDash(2005)`:

1. use the working skin resource first;
2. make the standalone host satisfy its expected data/event contract;
3. validate against the known-good running skin and Retail 6770 references;
4. modify the UI only for a documented incompatibility or fidelity defect.

Do **not** start by drawing replacement Blade panels from screenshots. Do **not** recreate animations already present in `skin.xui`. Do **not** rebuild working scene geometry unless the supplied scene is proven unusable.

The older Retail 6770 milestone remains useful for feature scope, backend goals and fidelity acceptance, but its from-scratch UI construction sequence is superseded by this baseline.

## Feasibility conclusion

**Feasible and preferred.**

The supplied package materially reduces project uncertainty because the difficult presentation work already exists in a working Xbox 360 XUI implementation. The primary engineering challenge is now replacing the FSD host/runtime with a standalone XEX plus compatible service adapters. CCLOS/ConsoleCrate backend code can provide much of the required modern functionality while the supplied Blade skin remains responsible for presentation.

Treat this as a **working-skin runtime transposition/host replacement project**, not a screenshot-driven recreation project.
