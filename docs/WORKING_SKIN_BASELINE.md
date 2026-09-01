# Working Skin Baseline — BladeDash(2005)

## Status

**Canonical implementation seed and absolute visual/behavioral authority for the standalone Blade dashboard.**

The developer-verified working `BladeDash(2005)` skin is not merely a reference or starting point. It is the approved product frontend.

When this package defines a UI state, geometry, animation, navigation behavior, focus state, dialog, sound event, transition, menu hierarchy, loading presentation, or other visual/behavioral detail, **BladeDash(2005) wins**.

Retail Xbox 360 Blades build 2.0.6770 is supplemental historical evidence only and may be used when the approved package does not adequately define the required state or behavior.

See `docs/AUTHORITY_HIERARCHY.md`.

## Developer-verified source package

Expected local path:

```text
references/local/BladeDash(2005).zip
```

Expected extraction path:

```text
references/local/BladeDash(2005)/
```

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

This is an already-authored and working XUI presentation implementation, not a screenshot/reference pack.

### Key files

`skin.xui`

- 7,224,751 bytes
- 277,528 lines
- XUI canvas version `000c`
- 448 direct top-level resources/visuals
- includes Blade geometry, highlights, jewels, bend/straight states, labels, list controls, loading visuals, animation timelines, sound triggers, panels, and dialogs
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

The package already contains major dashboard scenes including:

- `main.xur`
- `SplashScreen.xur`
- `Achievements.xur`
- `avatar.xur`
- game-list variants
- `gameinfo.xur`
- `GameControls.xur`
- `savedgames.xur`
- `TitleUpdateManager.xur`
- `Trainers.xur`
- `CopyDVD.xur`
- file/path manager scenes
- settings scenes
- weather
- music/video
- utilities/updater/support scenes

Codex must inventory and reuse these resources before creating replacements.

## FSD host contracts visible in the skin

The package does not contain the Freestyle Dash executable/source. The standalone XEX must therefore replace the FSD runtime behind the approved UI.

The skin exposes host-facing concepts such as:

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

Do not redesign the frontend to avoid these contracts. Implement compatibility facades behind the existing UI.

## Target architecture

```text
BladeDash(2005) XUI/XUR/resources
              |
Blade/FSD compatibility facade
              |
Blade presentation models
              |
Blade-specific adapters
              |
Shared ConsoleCrate/CCLOS-derived backend services
+ Xbox 360/XDK platform services
              |
Standalone BladeDashboard.xex
```

**Reuse CCLOS/ConsoleCrate backend capability, not CCLOS visual components.**

## Frontend preservation rule

Preserve wherever technically possible:

- Blade geometry and XUI definitions;
- scene hierarchy/resources;
- focus/highlight states;
- controller navigation behavior;
- transitions/timelines;
- button/list visuals;
- audio cues and event timing;
- backgrounds, jewels, separators, textures;
- menu geometry and controller glyphs;
- loading visuals and dialogs;
- CoverFlow meshes/shaders where retained;
- visual configuration XML;
- approved quirks/inconsistencies.

Do not replace working UI because newly written code would be cleaner or because Retail 6770 differs.

## Newly implemented/adapted runtime

The standalone product needs owned/shared code for:

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
- ConsoleCrate Marketplace/download adapters;
- Title Update integration;
- cache/artwork lookup;
- logging, diagnostics, and error handling.

Where ConsoleCrate/CCLOS already has a proven backend implementation, reuse/port it through a Blade-specific adapter instead of rebuilding the same subsystem.

## XuiTool rule

The owner has verified that this skin is editable in XuiTool. Codex must inspect the developer-local XDK/XuiTool environment and test this real package before assuming a resource needs recreation.

Required first checks:

1. locate the approved ZIP;
2. verify SHA-256;
3. extract without changing directory structure;
4. preserve an untouched golden copy;
5. locate `skin.xui` and `main.xur`;
6. open/test the package with the installed XuiTool workflow;
7. document which XUI/XUR assets can be opened, edited, regenerated, or repacked;
8. create a derivative working copy for standalone-host testing.

Do not invent XuiTool command-line flags.

## Public-repository boundary

The working ZIP contains third-party/historical resources whose redistribution status has not been established here. Keep the package developer-local under `references/local/` unless redistribution is intentionally approved.

Do not commit proprietary XDK binaries, original Microsoft dashboard binaries/executable code, or assume every supplied resource is redistributable.

This does not make the package optional. It remains the product frontend baseline on the developer machine.

## Retail 6770 supplemental rule

Retail 2.0.6770 may be consulted only when BladeDash does not adequately define a required state or behavior.

For a genuine missing state:

1. identify the exact BladeDash gap;
2. consult confirmed Retail 6770 evidence;
3. reconstruct only the missing portion;
4. keep it visually compatible with the approved BladeDash frontend;
5. do not alter unrelated BladeDash-defined states.

For BladeDash-defined states, missing Retail screenshots are not a blocker and are not a `REFERENCE_GAP`.

## Migration fidelity

For existing BladeDash states, primary comparison is:

```text
Known-good BladeDash(2005) under its original host
                         vs
Standalone BladeDashboard.xex using the migrated frontend
```

Validate geometry, focus, navigation, transitions, animation timing, menu hierarchy, dialogs, and audio timing.

Retail 6770 comparison is optional supplemental research for these states and cannot overrule the approved frontend.

## Precedence over old from-scratch strategy

For every state already implemented in BladeDash:

1. use the existing resource first;
2. make the standalone host satisfy its data/event contract;
3. validate against known-good BladeDash behavior;
4. modify presentation only for a documented technical incompatibility or explicit owner decision.

Do not start by drawing replacement Blade panels from screenshots. Do not recreate animations already present in `skin.xui`. Do not rebuild scene geometry unless the supplied resource is proven unusable.

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is legacy/supplemental scope material only and cannot override this baseline.

## Feasibility conclusion

**Feasible and preferred.**

The difficult presentation work already exists in a working Xbox 360 XUI implementation. The primary engineering challenge is replacing the FSD host/runtime with a standalone XEX plus compatible service adapters.

Treat this as a **working-skin runtime transposition/host replacement project**.

## Final rule

**BladeDash(2005) is the product specification. Retail 6770 fills genuine gaps only.**
