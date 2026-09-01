# Blade-Skin-Dashboard

Standalone Xbox 360 Blade dashboard project based on the developer-verified working **BladeDash(2005)** Freestyle 3/FSD XUI skin, with visual validation against the **Retail Xbox 360 Blades Dashboard build 2.0.6770**.

## Project goal

The implementation strategy is now **working-skin transposition**, not screenshot-driven recreation.

The approved `BladeDash(2005)` package already contains the working Blade presentation: XUI/XUR scenes, animations, geometry, textures, audio, configuration, fonts, meshes/shaders and supporting resources. The standalone project should preserve that presentation wherever technically possible and replace the Freestyle Dash host/runtime underneath it.

The final result is an independent Xbox 360 dashboard XEX and **does not require Freestyle Dash or Aurora at runtime**.

Modern CCLOS/ConsoleCrate backend services may provide library, launch, Marketplace, download, Title Update, system and other functionality through Blade-specific adapters. CCLOS visual components must not replace the Blade presentation.

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

The raw package remains developer-local unless redistribution is intentionally approved. Codex must still use it as the canonical implementation source on the development machine.

## Codex/contributor read order

Read before implementation:

1. `docs/WORKING_SKIN_BASELINE.md`
2. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
3. `docs/FIDELITY_DIRECTIVE.md`
4. `docs/CODEX_EXECUTION_RULES.md`
5. `docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md`
6. `docs/REFERENCE_MATRIX.md`

The working-skin baseline and Milestone 000 supersede older from-scratch UI sequencing.

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
CCLOS/ConsoleCrate backend logic
+ Xbox 360/XDK platform services
              |
Standalone BladeDashboard.xex
```

### Preserve first

Before creating replacement UI, Codex must attempt to reuse the supplied:

- Blade geometry and XUI visual definitions;
- existing XUR scenes;
- focus/highlight states;
- animation timelines;
- XMA audio cues;
- textures/backgrounds/jewels/separators;
- controller glyphs and list/button visuals;
- configuration XML;
- coverflow meshes/shaders where usable.

### Replace underneath

The standalone runtime must supply equivalents for the old FSD host services, including as needed:

- XEX lifecycle and XUI scene hosting;
- controller/navigation routing;
- installed-content discovery;
- title launch;
- profiles/achievements;
- storage/system/network information;
- settings;
- Marketplace/catalog/download services;
- Title Updates;
- file/path management;
- background tasks, cache and diagnostics.

## Existing from-scratch attempts

Do not blindly delete prior work. Preserve reusable backend/platform/build code, but quarantine or discard recreated Blade UI that competes with the approved working skin unless it solves a proven missing state.

See `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`.

## Fidelity target

The Retail 2.0.6770 archive remains the historical validation target:

- `thedev0ps/Xbox-360-Dashboard-Archive`
- `Blades/Retail/6770`
- https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770

The developer-tested `BladeDash(2005)` runtime is also a migration reference: the standalone host should not alter the working skin's geometry, focus behavior, animation timing, menu hierarchy or audio timing without an intentional documented reason.

## Repository boundary

Do not commit Xbox 360 XDK binaries, original Microsoft dashboard executables/extracted executable code, credentials, or third-party resources whose redistribution status has not been intentionally approved.

The project may commit newly written standalone runtime code, adapters, manifests/hashes, compatibility documentation, tooling and approved redistributable resources.

## Status

**Implementation strategy revised:** use the working `BladeDash(2005)` skin as the base project and transpose it to a standalone dashboard host. Milestone 000 is now the mandatory first engineering path.
