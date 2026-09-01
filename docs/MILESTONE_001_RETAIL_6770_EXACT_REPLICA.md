# Milestone 001 — Retail 6770 Exact Replica — RETIRED

## Status

**RETIRED / LEGACY — DO NOT EXECUTE AS AN IMPLEMENTATION MILESTONE**

This file previously defined a from-scratch Retail 2.0.6770 recreation strategy.

That implementation strategy has been superseded by the developer-approved `BladeDash(2005)` working-skin transposition architecture.

Do not restart screenshot-driven UI recreation from this milestone.

The prior version remains available in Git history for historical context if needed.

## Current authority

Read and follow, in order:

1. `../AGENTS.md`
2. `AUTHORITY_HIERARCHY.md`
3. `WORKING_SKIN_BASELINE.md`
4. `MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
5. `SHARED_CORE_ARCHITECTURE.md`
6. `FIDELITY_DIRECTIVE.md`
7. `CODEX_EXECUTION_RULES.md`
8. `REFERENCE_MATRIX.md`

## Product specification

**`BladeDash(2005)` is the absolute visual and behavioral authority.**

When the approved package defines a state, behavior, geometry, animation, transition, menu hierarchy, focus state, dialog, loading presentation, or sound event, that implementation wins.

Retail Xbox 360 Blades build 2.0.6770 is now supplemental historical reference only and may be used only when `BladeDash(2005)` does not adequately define a required state or behavior.

Retail 6770 must never be used to override a working, owner-approved BladeDash-defined state.

## Current implementation objective

The active objective is:

```text
BladeDash(2005) approved frontend
              |
FSD/Blade compatibility facade
              |
Blade presentation models
              |
Blade adapters
              |
Shared ConsoleCrate/CCLOS-derived services
+ Xbox 360 platform services
              |
Standalone BladeDashboard.xex
```

The standalone XEX replaces the old Freestyle Dash host underneath the approved frontend.

## Scope retained from the historical milestone

The following functional goals remain useful where they fit the approved BladeDash frontend and current project scope:

- standalone Xbox 360 XEX lifecycle;
- XUI/XuiTool workflow;
- scene/navigation hosting;
- Games/library integration;
- real content discovery;
- game/application launching;
- ConsoleCrate Marketplace integration;
- downloads;
- Title Updates;
- profile/gamercard integration where available;
- system/storage/network data;
- settings persistence;
- media functions retained by the project owner;
- dialogs/error/loading behavior;
- performance safeguards;
- build/release documentation;
- regression/fidelity tooling.

These functions must be connected **behind the existing BladeDash presentation**, not implemented as a new Retail-6770-from-scratch frontend.

## UI rule

Do not:

- recreate the Blade shell from Retail screenshots;
- redraw BladeDash-defined screens;
- change BladeDash geometry to match Retail 6770;
- replace BladeDash animations/timelines because another build differs;
- import CCLOS UI;
- modernize the approved frontend;
- create generic colored Blade panels;
- require FSD, Aurora, or CCLOS at runtime.

## Retail 6770 usage

Retail 2.0.6770 remains useful only for a **genuine BladeDash gap**.

Valid process:

1. prove the required state/detail is not adequately defined by BladeDash;
2. document the exact gap;
3. consult confirmed Retail 6770 evidence;
4. reconstruct only the missing portion;
5. keep it compatible with the approved BladeDash frontend;
6. do not modify unrelated BladeDash-defined states.

## Active milestone

Proceed with:

`MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`

## Final rule

**This Retail-6770-from-scratch milestone is retired. BladeDash(2005) is the product specification; Retail 6770 fills genuine gaps only.**
