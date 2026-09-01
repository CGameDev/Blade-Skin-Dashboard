# AGENTS.md — Blade-Skin-Dashboard

These instructions apply to the entire repository.

## Mission

Build a **standalone Xbox 360 Blade dashboard** using the developer-approved, developer-tested `BladeDash(2005)` Freestyle 3/FSD skin as the product frontend and canonical implementation seed.

The final standalone XEX must preserve the supplied working Blade presentation and behavior wherever technically possible while replacing Freestyle Dash host/runtime dependencies with newly owned runtime code and Blade-specific adapters backed by proven ConsoleCrate/CCLOS services.

This is a working-skin host-replacement project, not a from-scratch Blade recreation project.

## Absolute authority rule

**`BladeDash(2005)` is the absolute visual and behavioral authority.**

When the approved package defines a screen, scene, geometry, focus state, navigation behavior, animation, transition, menu hierarchy, dialog, loading state, sound event, typography placement, visual effect, or other presentation detail, that implementation wins.

Retail Xbox 360 Blades build 2.0.6770 is **supplemental historical reference only** and may be used only when `BladeDash(2005)` does not adequately define the required state or behavior.

Do not change a working BladeDash-defined state merely because Retail 6770 footage, a nearby build, a community recreation, or remembered behavior differs.

Read `docs/AUTHORITY_HIERARCHY.md` for the complete precedence rules.

## Read first

Before changing UI, navigation, architecture, Marketplace behavior, build tooling, or XUI resources, read in this order:

1. `README.md`
2. `docs/AUTHORITY_HIERARCHY.md`
3. `docs/WORKING_SKIN_BASELINE.md`
4. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
5. `docs/SHARED_CORE_ARCHITECTURE.md`
6. `docs/FIDELITY_DIRECTIVE.md`
7. `docs/CODEX_EXECUTION_RULES.md`
8. `docs/REFERENCE_MATRIX.md`

`AUTHORITY_HIERARCHY.md` overrides older Retail-6770-first wording anywhere else in the repository.

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is legacy/supplemental scope material only. It must not override BladeDash-defined presentation or Milestone 000 sequencing.

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
- Do not call CCLOS presentation screens, widgets, navigation classes or view models from Blade code.
- Do not require CCLOS to be running for Blade to function.
- Prefer neutral shared service interfaces such as `LibraryService`, `MarketplaceService`, `DownloadService`, `TitleUpdateService`, and `LaunchService`.
- Do not perform a speculative large shared-core refactor before the standalone Blade proof-of-architecture succeeds.
- Do not depend on Aurora or Freestyle Dash at runtime.
- Do not replace working geometry, timelines, animations, focus states, dialogs, or audio unless a documented technical limitation requires it.
- Do not create generic Blade panels when the approved skin already supplies the presentation.
- Preserve an untouched golden copy of the approved skin before editing.

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
Standalone BladeDashboard.xex
```

Guiding principle:

**BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

See `docs/SHARED_CORE_ARCHITECTURE.md` for mandatory service boundaries.

## Marketplace

Use the existing ConsoleCrate/CCLOS Marketplace infrastructure through an adapter layer.

Do not create a duplicate Marketplace backend.

Map catalog/download data into the existing BladeDash presentation contract. Backend concepts must not alter the visible frontend.

## Standalone requirement

The final application must be an independent Xbox 360 dashboard XEX.

Do not require Aurora, Freestyle Dash, or the CCLOS application for rendering, data, navigation, launching, Marketplace behavior, settings, game lists, or profile/system information.

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
Standalone BladeDashboard.xex
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
- system/profile/settings group;
- final migration regression pass.

Continue compile/static/resource validation between hardware gates.

## Documentation

At every meaningful checkpoint, record source resources reused, compatibility contracts implemented, files changed, build status, console-test status, migration fidelity status, limitations, gaps, and next work.

Do not leave critical decisions only in Codex chat history.

## Definition of done

For states present in the approved skin, success means the standalone host runs the **existing approved presentation** with equivalent geometry, typography, colors, focus behavior, navigation, transitions, animations, and audio timing while providing the required live backend behavior.

For states absent from BladeDash, use the authority hierarchy to reconstruct only the missing portion without redesigning existing approved states.

## Final instruction

**BladeDash(2005) is the product specification. Preserve it. Replace the missing FSD runtime underneath it. Use Retail 6770 only to fill genuine gaps.**
