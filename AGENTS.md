# AGENTS.md — Blade-Skin-Dashboard

These instructions apply to the entire repository.

## Mission

Build a **standalone Xbox 360 Blade dashboard** using the developer-verified working `BladeDash(2005)` Freestyle 3/FSD skin as the canonical implementation seed.

The final standalone XEX must preserve the supplied working Blade presentation wherever technically possible while replacing Freestyle Dash host/runtime dependencies with newly owned runtime code and Blade-specific adapters backed by proven CCLOS/ConsoleCrate services.

The visual validation target remains the **Xbox 360 Retail Blades Dashboard build 2.0.6770**.

This is no longer a from-scratch Blade UI recreation project when the approved skin already implements the state.

## Read first

Before changing UI, navigation, architecture, Marketplace behavior, build tooling, or XUI resources, read in this order:

1. `README.md`
2. `docs/WORKING_SKIN_BASELINE.md`
3. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
4. `docs/FIDELITY_DIRECTIVE.md`
5. `docs/CODEX_EXECUTION_RULES.md`
6. `docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md`
7. `docs/REFERENCE_MATRIX.md`

`WORKING_SKIN_BASELINE.md` and Milestone 000 take precedence over older from-scratch implementation sequencing.

## Canonical implementation seed

Developer-local source package:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

Expected extracted source:

```text
references/local/BladeDash(2005)/
```

The package includes the working XUI/XUR/resources and is the first implementation source Codex must inspect.

Do not silently substitute a different Blade skin.

## Canonical visual target

- Validation target: **Retail 2.0.6770**
- Primary historical build reference: `https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770`
- Older Blades builds are validation/reference-only and must not be blended into the final UI without evidence.

The historical archive validates fidelity. It is no longer the first place Codex should start drawing UI that already exists in the approved working skin.

## Hard rules

- Do not rebuild working Blade UI from screenshots.
- Do not modernize the UI.
- Do not reinterpret the UI.
- Do not add creative design changes.
- Do not use Metro/NXE visual language.
- Do not reuse CCLOS visual components.
- Do reuse CCLOS backend/service logic behind Blade adapters when useful.
- Do not depend on Aurora or Freestyle Dash at runtime.
- Do not replace working geometry, timelines, animations, focus states or audio without a documented technical/fidelity reason.
- Do not create generic colored Blade panels when the approved skin already supplies the Blade presentation.
- Do not guess missing 6770 states.
- Do not claim fidelity completion without comparison evidence.
- Preserve an untouched golden copy of the approved skin before editing.

If a visual fact is unknown and the working skin does not define it, mark it `REFERENCE_GAP`.

## Implementation strategy

For any state already implemented in the approved `BladeDash(2005)` package:

1. inspect/reuse the existing XUI/XUR/resource;
2. identify the FSD host/data/event contract it expects;
3. implement a compatibility facade/presentation model behind it;
4. map that facade to owned platform services or proven CCLOS/ConsoleCrate backend logic;
5. run the scene on the standalone host;
6. validate against the known-good skin and Retail 6770 evidence;
7. modify the UI only when a documented incompatibility/fidelity defect requires it.

Do not redraw first and wire backend later.

## Host-replacement architecture

Maintain separation:

```text
Approved Blade XUI/XUR UI
        |
FSD/Blade compatibility facade
        |
Blade presentation models
        |
Blade adapters
        |
Standalone services / CCLOS backend logic / Xbox 360 platform APIs
```

The UI must not bind directly to CCLOS screen/widget implementations.

## Marketplace

Use the existing ConsoleCrate/CCLOS Marketplace infrastructure through an adapter layer.

Do not create a duplicate Marketplace backend.

Map modern catalog/download data into the existing Blade presentation contract. Backend concepts must not change the visible Blade UI.

## Standalone requirement

The final application must be an independent Xbox 360 dashboard XEX.

Do not require Aurora or Freestyle Dash for rendering, data, navigation, launching, Marketplace behavior, settings, game lists or profile/system information.

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

Discard or quarantine UI that competes with the approved working skin unless it solves a proven missing/unusable state.

Record this in `docs/LEGACY_ATTEMPT_AUDIT.md`.

## XUI/XuiTool

The project owner has verified that the approved skin can be edited in XuiTool.

Inspect the developer's actual local Xbox 360 XDK/XUI environment before assuming paths or commands.

Record actual findings in `docs/BUILD_ENVIRONMENT.md`.

Codex must test the supplied `skin.xui`/XUR workflow directly before generating replacement UI.

Do not invent undocumented XuiTool command-line switches.

Automate supported/repeatable steps. Document unavoidable GUI-only XuiTool steps precisely.

Do not commit proprietary XDK files.

## Local source / redistribution boundary

The approved ZIP is developer-local implementation material and is intentionally expected under `references/local/`, which is Git-ignored.

Do not automatically commit the raw ZIP, XDK files, original Microsoft dashboard binaries, extracted executable code, or resources whose redistribution status has not been intentionally approved.

This repository may record hashes, manifests, compatibility notes, newly written code and intentionally approved resources.

Keeping the raw source package local does not make it optional: Codex must use it as the implementation baseline on the developer machine.

## Fidelity testing

For major states, compare where practical:

1. Retail 6770 historical reference;
2. known-good `BladeDash(2005)` running under its original host;
3. the standalone BladeDashboard XEX using the migrated presentation.

Produce where useful:

- side-by-side comparison;
- 50/50 overlay;
- difference visualization;
- discrepancy report.

Severity:

- F0 = blocker
- F1 = major
- F2 = moderate
- F3 = minor

No fidelity-approved screen may have open F0/F1 issues.

## Testing cadence

Do not demand manual console testing after every tiny edit.

Batch hardware testing at meaningful checkpoints, especially:

- existing Blade resource rendered by standalone host;
- main Blade shell/navigation;
- installed game list + launch;
- Marketplace integration;
- system/profile/settings group;
- final regression/fidelity pass.

Continue compile/static/resource validation between hardware gates.

## Documentation

Do not leave critical project decisions only in chat/session history.

At the end of each meaningful checkpoint, update repository documentation with references used, source resources reused, compatibility contracts implemented, files changed, build status, fidelity status, open discrepancies, limitations and next work.

## Definition of done

A screen is not done because a replacement recreation compiles or resembles Blades.

For states present in the approved working skin, success means the standalone host runs the existing presentation with equivalent geometry, typography, colors, focus behavior, navigation, transition behavior and audio timing while providing the required live backend behavior.

## Final instruction

**Do not rebuild what already works. Transpose the approved Blade skin onto a standalone host and replace the missing FSD runtime behind it.**
