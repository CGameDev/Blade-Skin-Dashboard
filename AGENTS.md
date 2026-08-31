# AGENTS.md — Blade-Skin-Dashboard

These instructions apply to the entire repository.

## Mission

Recreate the **Xbox 360 Retail Blades Dashboard build 2.0.6770** as a standalone Xbox 360 dashboard with extremely high visual and interaction fidelity.

This is an exact-replica project, not a Blade-inspired redesign.

## Read first

Before changing UI, navigation, architecture, Marketplace behavior, build tooling, or XUI resources, read:

1. `docs/FIDELITY_DIRECTIVE.md`
2. `docs/CODEX_EXECUTION_RULES.md`
3. `docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md`
4. `docs/REFERENCE_MATRIX.md`

These files are the repository system of record.

## Canonical target

- Target dashboard: **Retail 2.0.6770**
- Primary build reference: `https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770`
- Older Blades builds are reference-only and must not be blended into the final UI.

## Hard rules

- Do not modernize the UI.
- Do not reinterpret the UI.
- Do not add creative design changes.
- Do not use Metro/NXE visual language.
- Do not reuse CCLOS visual components.
- Do not depend on Aurora at runtime.
- Do not guess missing 6770 states.
- Do not silently use older-build screenshots as 6770 evidence.
- Do not claim fidelity completion without comparison evidence.

If a visual fact is unknown, mark it `REFERENCE_GAP`.

## Reference-first implementation

Before implementing a production screen/state:

1. Add or confirm the state in `docs/REFERENCE_MATRIX.md`.
2. Identify a reliable Retail 6770 reference.
3. Record reference confidence.
4. Measure/document geometry and behavior.
5. Implement the static state.
6. Match focus/navigation.
7. Match transitions/animation.
8. Connect dynamic data/backend services.
9. Capture the recreation.
10. Compare it against the reference.
11. Resolve F0/F1 discrepancies before marking complete.

## Visual authority

When implementation and the original reference disagree, **the reference wins**.

Do not “fix” original inconsistencies unless explicitly instructed by the project owner.

## Marketplace

Use the existing ConsoleCrate/CCLOS Marketplace infrastructure through an adapter layer.

Do not create a duplicate Marketplace backend.

Modern backend data must be mapped into the original-style Retail 6770 frontend. Backend concepts must not change the visible UI.

## Architecture

Maintain separation:

`XUI UI -> presentation models -> adapters -> services/platform`

Do not bind UI directly to modern service response structures when an adapter can preserve the original interface contract.

## Standalone requirement

The final application must be an independent Xbox 360 dashboard XEX.

Do not require Aurora for rendering, data, navigation, launching, or Marketplace behavior.

## XUI/XuiTool

Inspect the developer's local Xbox 360 XDK/XUI environment before assuming paths or commands.

Record actual findings in `docs/BUILD_ENVIRONMENT.md`.

Do not invent undocumented XuiTool command-line switches.

Automate supported/repeatable steps. Document unavoidable GUI-only XuiTool steps precisely.

Do not commit proprietary XDK files.

## Proprietary reference boundary

Do not commit or redistribute original Microsoft dashboard binaries, original dashboard executable code, proprietary dashboard resource packages, or non-redistributable XDK components.

The dashboard archive is reference material, not implementation source.

Use newly written code and redistributable project resources in releases.

## Fidelity testing

For major states, use matched captures and produce where practical:

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

Batch hardware testing at meaningful checkpoints, but continue build/static validation throughout development.

## Documentation

Do not leave critical project decisions only in chat/session history.

At the end of each meaningful checkpoint, update repository documentation with references used, files changed, build status, fidelity status, open discrepancies, limitations, and next work.

## Definition of done

A screen is not done because it compiles or resembles Blades.

It is done only when the reference, geometry, typography, colors, focus behavior, navigation, transition behavior, and comparison gate defined by `docs/FIDELITY_DIRECTIVE.md` are satisfied.

## Final instruction

**Optimize for evidence-backed Retail 6770 fidelity, not originality.**
