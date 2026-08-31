# Blade-Skin-Dashboard

Standalone Xbox 360 dashboard project whose visual and interaction target is the **Retail Xbox 360 Blades Dashboard, build 2.0.6770**.

## Project goal

Recreate the Retail 6770 Blades dashboard as faithfully as technically possible so that a side-by-side comparison with the original is difficult to distinguish. The dashboard is implemented as a new standalone homebrew application and **does not run on Aurora**.

The original dashboard is the visual and behavioral specification. Modern ConsoleCrate services may replace unavailable backend services, but they must adapt to the original UI rather than redesigning it.

## Canonical implementation documents

Codex and contributors must read these files before implementing UI:

1. `docs/FIDELITY_DIRECTIVE.md`
2. `docs/CODEX_EXECUTION_RULES.md`
3. `docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md`
4. `docs/REFERENCE_MATRIX.md`

If implementation decisions conflict with those documents, the fidelity directive wins.

## Canonical reference

Primary historical reference:

- Xbox 360 Dashboard Archive
- `thedev0ps/Xbox-360-Dashboard-Archive`
- `Blades/Retail/6770`
- https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770

Secondary structural/UI reference:

- Architecture of Consoles — Xbox 360 / Blades section
- https://github.com/flipacholas/Architecture-of-consoles/blob/master/articles/xbox-360.Rmd.md

## Important clean-room boundary

Reference archives may contain Microsoft binaries or proprietary resources. They are **research/reference material only**. Do not commit, redistribute, package, or make this repository depend on original Microsoft dashboard binaries, extracted executable code, or proprietary resource packages.

The distributable project must use newly written code and redistributable project resources. If locally owned original material is used by the developer for visual comparison, it remains outside the repository and outside release packages.

## Backend rule

The existing ConsoleCrate / CCLOS Marketplace infrastructure is the Marketplace backend for this project. Do not create an independent duplicate Marketplace service.

The Blade dashboard frontend must remain visually faithful to Retail 6770. ConsoleCrate services are connected through adapter layers behind the UI.

## Status

Initial fidelity milestone specification created. Implementation must begin with reference capture, toolchain validation, and a pixel-accurate Blade shell before functional feature expansion.
