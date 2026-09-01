# Blade-Skin-Dashboard

Standalone Xbox 360 **Blade Dashboard** project based on the developer-approved working **BladeDash(2005)** Freestyle 3/FSD XUI skin.

## Product authority

**`BladeDash(2005)` is the absolute visual and behavioral authority.**

When the approved package defines a screen, layout, animation, transition, focus state, navigation behavior, menu hierarchy, dialog, loading state, sound event, or presentation detail, that implementation is the product specification.

Retail Xbox 360 Blades build **2.0.6770 is supplemental historical reference only** and may fill only genuine states/details not adequately defined by BladeDash.

See `docs/AUTHORITY_HIERARCHY.md`.

## Owner-approved product scope

Explicit scope decisions are recorded in `docs/OWNER_DECISIONS.md` and must not be reinterpreted by Codex.

Key decisions:

- product name: **Blade Dashboard**;
- preserve the BladeDash frontend and keep it externally editable through the verified XUI/XuiTool resource workflow wherever technically possible;
- retain BladeDash features whenever ConsoleCrate/CCLOS Core or Xbox platform services can supply real standalone functionality underneath them;
- CopyDVD uses CCLOS Disc-to-GOD functionality behind the Blade CopyDVD UI;
- Achievements, Title Updates and Trainers use the corresponding CCLOS/Xbox backend functionality behind their existing Blade scenes;
- Marketplace uses ConsoleCrate/CCLOS services behind the existing Blade Marketplace presentation;
- Downloads use the proven CCLOS download architecture behind Blade progress/state presentation;
- **Watch TV is integrated into the existing Blade Media / Media Center experience; the Blade Media UI must not be visually redesigned or replaced with CCLOS Watch TV UI**;
- authoritative backend-reference source is `CGameDev/ConsoleCrateLive` branch `main`, with exact reused commit recorded during implementation;
- authoritative production service is `consolecratelive.online`;
- Blade owns its own local Config/Cache/Data/Logs/Skins state and does not require a CCLOS local installation;
- default deployment root is `Hdd1:\Apps\BladeDashboard\` with `default.xex` as the deployable entrypoint;
- no new CCLOS-style OOBE;
- v1 primary acceptance target is 16:9 HD / 720p;
- raw BladeDash assets remain developer/private-build material until redistribution is intentionally reviewed.

## Project goal

This is a **working-skin transposition / host replacement** project, not screenshot-driven recreation.

The approved package already contains the Blade presentation: XUI/XUR scenes, animations, geometry, textures, audio, configuration, fonts, meshes/shaders, dialogs, lists and navigation presentation.

The standalone project preserves that frontend and replaces the Freestyle Dash host/runtime underneath it with a standalone XEX plus Blade-specific adapters backed by reusable ConsoleCrate/CCLOS services and Xbox platform APIs.

The final result does **not** require Freestyle Dash, Aurora, or the CCLOS application at runtime.

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

The raw package remains developer-local unless redistribution is intentionally approved.

## Codex/contributor read order

Read before implementation:

1. `AGENTS.md`
2. `docs/AUTHORITY_HIERARCHY.md`
3. `docs/OWNER_DECISIONS.md`
4. `docs/WORKING_SKIN_BASELINE.md`
5. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
6. `docs/SHARED_CORE_ARCHITECTURE.md`
7. `docs/FIDELITY_DIRECTIVE.md`
8. `docs/CODEX_EXECUTION_RULES.md`
9. `docs/REFERENCE_MATRIX.md`
10. relevant checkpoint/compatibility/provenance reports

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is retired legacy material only.

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
Hdd1:\Apps\BladeDashboard\default.xex
```

Guiding principle:

> **BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

## Feature-retention model

Do not remove a Blade feature simply because FSD supplied its original implementation. If there is a real ConsoleCrate/CCLOS/Xbox replacement, keep the existing Blade UI and connect that service underneath it.

Examples:

```text
Blade CopyDVD        -> BladeDiscCopyAdapter    -> CCLOS Disc-to-GOD
Blade Achievements   -> BladeAchievementAdapter -> CCLOS/Xbox achievements
Blade Title Updates  -> BladeTitleUpdateAdapter -> CCLOS Title Updates
Blade Trainers       -> BladeTrainerAdapter     -> CCLOS trainer/runtime
Blade Marketplace    -> BladeMarketplaceAdapter -> ConsoleCrate Marketplace
Blade Media Center   -> BladeMediaAdapter       -> CCLOS Watch TV/media services
```

For obsolete services with no real replacement, do not fake them or leave dead calls. Preserve the Blade presentation and use an existing disabled/unavailable state or record `OWNER_DECISION_REQUIRED`.

## Shared backend rule

Reuse proven ConsoleCrate/CCLOS backend capability through clean service interfaces and Blade-specific adapters.

Do not reuse CCLOS screens, widgets, view models, navigation classes, or visual components.

## Repository boundary

Do not commit Xbox 360 XDK binaries, original Microsoft dashboard executables/extracted executable code, credentials, or third-party resources whose redistribution status has not been intentionally approved.

The project may commit newly written runtime code, adapters, manifests/hashes, compatibility/provenance documentation, tooling and approved redistributable resources.

## Status

**Canonical direction:** preserve the approved BladeDash frontend, keep its practical features, replace the FSD host beneath it, and connect proven ConsoleCrate/CCLOS services through clean adapters. Retail 6770 fills only genuine frontend gaps.
