# Blade Dashboard Authority Hierarchy

## Status

**NON-NEGOTIABLE PROJECT AUTHORITY RULE**

This document defines which source wins when UI, behavior, navigation, animation, audio, geometry, layout, or presentation references disagree.

## Absolute authority

The developer-approved and developer-tested `BladeDash(2005)` package is the **absolute visual and behavioral authority** for this project wherever it defines a state, resource, animation, interaction, menu hierarchy, sound event, focus behavior, transition, layout, or presentation detail.

Approved local source:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

The project owner has already run this skin and approved its appearance and behavior as the desired product frontend.

Therefore:

> **When BladeDash(2005) defines something, BladeDash(2005) wins.**

Codex must not alter a BladeDash-defined state merely to make it look more like a Retail 6770 screenshot, archive artifact, nearby dashboard build, community recreation, or remembered historical behavior.

## Retail 2.0.6770 role

Retail Xbox 360 Blades build 2.0.6770 is now **supplemental historical reference only**.

Use Retail 6770 only when the approved `BladeDash(2005)` package does not adequately define the required state or behavior.

Examples of valid Retail 6770 use:

- a required screen is absent from BladeDash;
- a host behavior is not encoded or observable in the skin resources;
- a missing icon/state needs historical confirmation;
- an ambiguous system interaction has no BladeDash evidence;
- a newly implemented fallback state must remain visually consistent with the Blade era;
- a technical incompatibility forces reconstruction of a portion of the UI that cannot be reused.

Retail 6770 must **not** be used to override an existing, working, owner-approved BladeDash implementation.

## Authority order

When evidence conflicts, use this order:

1. **Developer-approved `BladeDash(2005)` running behavior and supplied resources** — absolute authority.
2. `BladeDash(2005)` XUI/XUR/XML/audio/resource definitions and measurable package behavior.
3. Project-owner explicit decisions recorded in repository documentation.
4. Confirmed Retail 2.0.6770 material — only for gaps not defined by BladeDash.
5. Nearby Retail Blades builds when the required missing behavior is demonstrably equivalent.
6. Other historical/community material as structural clues only.
7. Memory, assumptions, generated mockups, or creative guesses — never authoritative.

## Stable presentation contract

For BladeDash-defined states, the existing frontend contract is frozen unless a documented technical limitation requires a change.

Preserve:

- XUI/XUR scene hierarchy;
- blade geometry and positioning;
- menu layout and labels unless dynamic data intentionally replaces content;
- focus and selected states;
- controller navigation behavior;
- transition direction and timing;
- animation timelines;
- colors, gradients, textures and visual effects;
- XMA/audio event timing;
- dialogs and loading presentation;
- CoverFlow presentation where retained;
- typography placement and sizing;
- visual quirks and inconsistencies present in the approved skin.

Do not "fix" the approved skin to match another historical source.

## Backend freedom, frontend stability

Backend implementations may change freely behind adapters as long as the BladeDash presentation contract remains stable.

Canonical architecture:

```text
BladeDash(2005) frontend
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

The backend adapts to BladeDash. BladeDash does not adapt visually to the backend.

## Reference-gap behavior

A `REFERENCE_GAP` exists only when all of the following are true:

1. the required state/behavior is not adequately defined by BladeDash;
2. no owner decision already defines it;
3. available Retail 6770 evidence is insufficient.

Do not mark a BladeDash-defined state as a reference gap simply because a matching Retail 6770 screenshot has not been collected.

## Migration fidelity

For states already present in BladeDash, fidelity testing primarily compares:

```text
Known-good BladeDash(2005) under its working host
                     vs
Standalone BladeDashboard.xex using the migrated presentation
```

The goal is to prove that host replacement did not alter the approved frontend.

Retail 6770 comparisons are optional supplemental research for these states and must not become a reason to modify an otherwise faithful BladeDash migration.

## Missing-state fidelity

Only for states not defined by BladeDash should Retail 6770 become the primary historical source for reconstructing the missing presentation.

Those reconstructed states must be visually compatible with the approved BladeDash frontend and must not trigger broad redesign of existing BladeDash-defined states.

## Final rule

**BladeDash(2005) is the product specification. Retail 6770 fills gaps; it does not overrule the product specification.**
