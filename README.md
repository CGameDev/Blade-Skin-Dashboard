# Blade-Skin-Dashboard

Standalone Xbox 360 Blade dashboard project based on the developer-approved working **BladeDash(2005)** Freestyle 3/FSD XUI skin.

## Product authority

**`BladeDash(2005)` is the absolute visual and behavioral authority for this project.**

The project owner has already run and approved this frontend as the desired dashboard experience. When the package defines a screen, layout, animation, transition, focus state, navigation behavior, menu hierarchy, dialog, loading state, sound event, or other presentation detail, that implementation is the product specification.

Retail Xbox 360 Blades build **2.0.6770 is supplemental historical reference only**. Use it only when the approved BladeDash package does not adequately define a required state or behavior.

Do not modify a working BladeDash-defined state simply to make it closer to a Retail 6770 screenshot or historical archive.

See `docs/AUTHORITY_HIERARCHY.md`.

## Project goal

The implementation strategy is **working-skin transposition / host replacement**, not screenshot-driven recreation.

The approved package already contains the Blade presentation: XUI/XUR scenes, animations, geometry, textures, audio, configuration, fonts, meshes/shaders, dialogs, lists, navigation presentation, and supporting resources.

The standalone project must preserve that frontend wherever technically possible and replace the Freestyle Dash host/runtime underneath it.

The final result is an independent Xbox 360 dashboard XEX and does **not** require Freestyle Dash, Aurora, or the CCLOS application at runtime.

## Canonical implementation seed

Developer-local package:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

Expected extraction directory:

```text
references/local/BladeDash(2005)/
```

The raw package remains developer-local unless redistribution is intentionally approved. Codex must still use it as the canonical frontend source on the development machine.

## Codex/contributor read order

Read before implementation:

1. `docs/AUTHORITY_HIERARCHY.md`
2. `docs/WORKING_SKIN_BASELINE.md`
3. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
4. `docs/SHARED_CORE_ARCHITECTURE.md`
5. `docs/FIDELITY_DIRECTIVE.md`
6. `docs/CODEX_EXECUTION_RULES.md`
7. `docs/REFERENCE_MATRIX.md`

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is legacy/supplemental scope material only. It must not override the authority hierarchy or Milestone 000.

## Implementation model

```text
BladeDash(2005) XUI/XUR/resources
              |
Blade/FSD compatibility facade
              |
Blade presentation models
              |
Blade-specific adapters
              |
Shared ConsoleCrate/CCLOS-derived services
+ Xbox 360/XDK platform services
              |
Standalone BladeDashboard.xex
```

### Preserve first

Before creating replacement UI, Codex must attempt to reuse the supplied:

- Blade geometry and XUI visual definitions;
- existing XUR scenes;
- focus/highlight states;
- controller navigation behavior;
- animation timelines;
- XMA audio cues;
- textures/backgrounds/jewels/separators;
- controller glyphs and list/button visuals;
- dialogs and loading presentation;
- configuration XML;
- CoverFlow meshes/shaders where retained.

### Replace underneath

The standalone runtime supplies equivalents for the old FSD host services, including as needed:

- XEX lifecycle and XUI scene hosting;
- controller/input routing;
- installed-content discovery;
- title launch;
- profiles/achievements;
- storage/system/network information;
- settings;
- Marketplace/catalog/download services;
- Title Updates;
- file/path management;
- background tasks, cache and diagnostics.

## Shared backend rule

Reuse proven ConsoleCrate/CCLOS backend capability through clean service interfaces and Blade-specific adapters.

Do not reuse CCLOS screens, widgets, view models, navigation classes, or visual components.

Guiding principle:

> **BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

## Existing from-scratch attempts

Do not blindly delete prior work. Preserve reusable backend/platform/build code, but quarantine or discard recreated Blade UI that competes with the approved BladeDash frontend unless it solves a proven missing state.

## Retail 6770 usage

Retail 2.0.6770 may help fill genuine gaps when BladeDash does not define a required state. It is not the acceptance target for states already defined and approved in BladeDash.

For BladeDash-defined states, the primary fidelity comparison is:

```text
Known-good BladeDash(2005)
          vs
Standalone BladeDashboard.xex
```

## Repository boundary

Do not commit Xbox 360 XDK binaries, original Microsoft dashboard executables/extracted executable code, credentials, or third-party resources whose redistribution status has not been intentionally approved.

The project may commit newly written standalone runtime code, adapters, manifests/hashes, compatibility documentation, tooling, and approved redistributable resources.

## Status

**Canonical direction:** preserve the approved `BladeDash(2005)` frontend, replace the FSD host beneath it, and use shared ConsoleCrate/CCLOS services through clean adapters. Retail 6770 fills only genuine frontend gaps.
