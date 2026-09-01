# AGENTS.md — Blade-Skin-Dashboard

These instructions apply to the entire repository.

## Mission

Build a **standalone Xbox 360 Blade Dashboard** using the developer-approved, developer-tested `BladeDash(2005)` Freestyle 3/FSD skin as the product frontend and canonical implementation seed.

The final standalone XEX must preserve the supplied working Blade presentation and behavior wherever technically possible while replacing Freestyle Dash host/runtime dependencies with newly owned runtime code and Blade-specific adapters backed by proven ConsoleCrate/CCLOS services.

This is a working-skin host-replacement project, not a from-scratch Blade recreation project.

## Absolute authority rule

**`BladeDash(2005)` is the absolute visual and behavioral authority.**

When the approved package defines a screen, scene, geometry, focus state, navigation behavior, animation, transition, menu hierarchy, dialog, loading state, sound event, typography placement, visual effect, or other presentation detail, that implementation wins.

Retail Xbox 360 Blades build 2.0.6770 is **supplemental historical reference only** and may be used only when `BladeDash(2005)` does not adequately define the required state or behavior.

Do not change a working BladeDash-defined state merely because Retail 6770 footage, a nearby build, a community recreation, or remembered behavior differs.

Read `docs/AUTHORITY_HIERARCHY.md` for the complete precedence rules.

## Owner decisions are authoritative

Read `docs/OWNER_DECISIONS.md` for explicit product/scope choices. Codex must not turn an owner decision into a guess, `REFERENCE_GAP`, or alternate design.

Key owner-approved rules include:

- product name is **Blade Dashboard**;
- keep the Blade frontend externally editable through the verified XUI/XuiTool resource workflow wherever technically possible;
- when BladeDash contains a feature that ConsoleCrate/CCLOS Core or Xbox platform services can implement, retain the Blade feature and replace the old FSD service underneath it;
- examples include CopyDVD -> CCLOS Disc-to-GOD, Achievements -> CCLOS/Xbox achievement services, Title Updates -> CCLOS TU services, Trainers -> CCLOS trainer/runtime services, Marketplace/downloads -> ConsoleCrate services;
- the existing Blade Media / Media Center UI is retained and must not be visually redesigned; CCLOS Watch TV functionality is connected underneath it through Blade media adapters;
- `CGameDev/ConsoleCrateLive` `main` is the authoritative CCLOS backend-reference source, with exact source commit recorded before reuse;
- `consolecratelive.online` is the authoritative production ConsoleCrate service; do not revive deprecated NAS/Cloudflare CCLOS infrastructure;
- Blade owns its local Config/Cache/Data/Logs/Skins state and does not depend on a CCLOS local installation;
- default installation root is `Hdd1:\Apps\BladeDashboard\` with deployable entrypoint `default.xex`;
- no new CCLOS-style OOBE;
- v1 primary acceptance target is 16:9 HD / 720p;
- raw BladeDash assets remain developer/private-build material until redistribution is explicitly reviewed.

## Read first

Before changing UI, navigation, architecture, Marketplace behavior, build tooling, XUI resources, media behavior, or backend integration, read in this order:

1. `README.md`
2. `docs/AUTHORITY_HIERARCHY.md`
3. `docs/OWNER_DECISIONS.md`
4. `docs/WORKING_SKIN_BASELINE.md`
5. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
6. `docs/SHARED_CORE_ARCHITECTURE.md`
7. `docs/FIDELITY_DIRECTIVE.md`
8. `docs/CODEX_EXECUTION_RULES.md`
9. `docs/REFERENCE_MATRIX.md`
10. relevant checkpoint/compatibility/provenance reports

`AUTHORITY_HIERARCHY.md` and `OWNER_DECISIONS.md` override older conflicting wording anywhere else in the repository.

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is retired/legacy scope material only. It must not override BladeDash-defined presentation or Milestone 000 sequencing.

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

The package contains the working XUI/XUR/resources and is the first implementation source Codex must inspect.

Never silently substitute another Blade skin.

## Hard rules

- Do not rebuild working Blade UI from screenshots.
- Do not use Retail 6770 to override a BladeDash-defined state.
- Do not modernize or reinterpret the approved frontend.
- Do not add creative design changes.
- Do not use Metro/NXE visual language.
- Do not reuse CCLOS visual components.
- Do reuse ConsoleCrate/CCLOS backend/service logic behind Blade adapters when useful.
- Do not delete a BladeDash feature solely because its original FSD implementation is unavailable when a real ConsoleCrate/CCLOS/Xbox service can replace it.
- Do not call CCLOS presentation screens, widgets, navigation classes or view models from Blade code.
- Do not require CCLOS to be running for Blade to function.
- Prefer neutral shared service interfaces such as `LibraryService`, `MarketplaceService`, `DownloadService`, `TitleUpdateService`, `LaunchService`, `MediaService`, `DiscCopyService`, and equivalent platform abstractions.
- Do not perform a speculative large shared-core refactor before the standalone Blade proof-of-architecture succeeds.
- Do not depend on Aurora or Freestyle Dash at runtime.
- Do not replace working geometry, timelines, animations, focus states, dialogs, or audio unless a documented technical limitation requires it.
- Do not create generic Blade panels when the approved skin already supplies the presentation.
- Preserve an untouched golden copy of the approved skin before editing.
- Do not leave FSD-era buttons silently calling dead services; map them to real replacements, use an existing Blade disabled/unavailable behavior, or record `OWNER_DECISION_REQUIRED`.

A `REFERENCE_GAP` exists only when the required state is not adequately defined by BladeDash, no owner decision defines it, and supplemental historical evidence is insufficient.

## Implementation strategy

For every state already implemented in `BladeDash(2005)`:

1. inspect and reuse the existing XUI/XUR/resource;
2. preserve its visual and behavioral contract;
3. identify the FSD host/data/event contract it expects;
4. implement a compatibility facade/presentation model behind it;
5. map that facade to owned platform services or proven ConsoleCrate/CCLOS backend logic;
6. run the existing scene on the standalone host;
7. compare the standalone result to the known-good BladeDash behavior;
8. modify the UI only when a documented technical incompatibility requires it.

Do not redraw first and wire the backend later.

## Feature-retention rule

When an approved BladeDash feature can be backed by real standalone functionality, **keep the Blade frontend and replace the backend underneath it**.

Canonical examples:

```text
Blade CopyDVD scene
    -> BladeDiscCopyAdapter
    -> CCLOS Disc-to-GOD service

Blade Achievements scene
    -> BladeAchievementAdapter
    -> CCLOS/Xbox achievement service

Blade Title Update scene
    -> BladeTitleUpdateAdapter
    -> CCLOS Title Update service

Blade Trainers scene
    -> BladeTrainerAdapter
    -> CCLOS trainer/runtime service

Blade Media Center
    -> BladeMediaAdapter
    -> CCLOS Watch TV/media services
```

The existing Blade Media Center presentation is frozen. Watch TV functionality must use its existing scenes/list/control patterns; do not import or recreate the CCLOS Watch TV UI.

## Shared-core architecture

```text
BladeDash(2005) XUI/XUR frontend
        |
FSD/Blade compatibility facade
        |
Blade presentation models
        |
Blade adapters
        |
Shared ConsoleCrate/CCLOS-derived services
        |
Xbox 360 platform APIs
        |
Standalone BladeDashboard/default.xex
```

Guiding principle:

**BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

See `docs/SHARED_CORE_ARCHITECTURE.md` for mandatory service boundaries.

## Marketplace

Use the existing ConsoleCrate/CCLOS Marketplace infrastructure through an adapter layer.

Visible name: **Marketplace**.

Do not create a duplicate Marketplace backend or a new ConsoleCrate top-level Blade.

Map catalog/download data into the existing BladeDash presentation contract. Backend concepts must not alter the visible frontend.

## Standalone requirement

The final application must be an independent Xbox 360 dashboard XEX.

Default deploy path:

```text
Hdd1:\Apps\BladeDashboard\default.xex
```

Do not require Aurora, Freestyle Dash, or the CCLOS application for rendering, data, navigation, launching, Marketplace behavior, settings, games, media, or profile/system information.

The standalone XEX replaces the old host, not the Blade presentation.

## Previous from-scratch attempts

Audit before deleting.

Preserve reusable non-UI work such as:

- XEX/build foundations;
- XDK discovery/build scripts;
- network/services;
- filesystem utilities;
- launch helpers;
- ConsoleCrate adapters;
- cache/parsing logic;
- diagnostics;
- tests;
- background task/performance infrastructure.

Discard or quarantine UI that competes with the approved BladeDash frontend unless it solves a proven missing/unusable state.

Record the audit in `docs/LEGACY_ATTEMPT_AUDIT.md`.

## XUI/XuiTool

The project owner has verified that the approved skin can be edited in XuiTool.

Inspect the developer's actual local Xbox 360 XDK/XUI environment before assuming paths or commands.

Record findings in `docs/BUILD_ENVIRONMENT.md`.

Codex must test the supplied `skin.xui`/XUR workflow directly before generating replacement UI.

Prefer externally editable/repackable resources over permanently embedding the whole presentation in the XEX when the verified runtime supports that architecture.

Do not invent undocumented XuiTool command-line switches.

Do not commit proprietary XDK files.

## Local source / redistribution boundary

The approved ZIP is developer-local implementation material and is intentionally expected under `references/local/`, which is Git-ignored.

Do not automatically commit the raw ZIP, XDK files, original Microsoft dashboard binaries, extracted executable code, or resources whose redistribution status has not been intentionally approved.

Keeping the raw source package local does not make it optional: Codex must use it as the implementation baseline on the developer machine.

## Fidelity testing

For BladeDash-defined states, primary migration validation is:

```text
Known-good BladeDash(2005) under its working host
                    vs
Standalone Blade Dashboard
```

The standalone host must preserve geometry, typography placement, colors, focus behavior, navigation, transition behavior, animation timing, and audio timing.

Retail 6770 may be consulted only for states or details not adequately defined by BladeDash. It must not be used to "correct" an approved BladeDash-defined state.

## Testing cadence

Do not demand manual console testing after every tiny edit.

Batch hardware testing at meaningful checkpoints, especially:

- existing Blade resource rendered by standalone host;
- main Blade shell/navigation;
- installed game list + launch;
- Marketplace integration;
- media/Watch TV integration;
- system/profile/settings group;
- final migration regression pass.

Continue compile/static/resource validation between hardware gates.

## Documentation

At every meaningful checkpoint, record source resources reused, FSD compatibility contracts implemented, CCLOS source commit used, adapters/services connected, files changed, build status, console-test status, migration fidelity status, limitations, gaps, and next work.

Do not leave critical decisions only in Codex chat history.

## Definition of done

For states present in the approved skin, success means the standalone host runs the **existing approved presentation** with equivalent geometry, typography, colors, focus behavior, navigation, transitions, animations, and audio timing while providing the required live backend behavior.

For states absent from BladeDash, use the authority hierarchy to reconstruct only the missing portion without redesigning existing approved states.

## Final instruction

**BladeDash(2005) is the product specification. Preserve it. Keep every practical Blade feature by replacing its FSD backend with real ConsoleCrate/CCLOS Core or Xbox functionality. Keep the Media Center UI intact while adding Watch TV underneath it. Use Retail 6770 only to fill genuine gaps.**
