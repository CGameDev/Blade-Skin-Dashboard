# BladeDash(2005) Fidelity Directive

## Status

**NON-NEGOTIABLE PROJECT RULE**

This document governs UI, navigation, animation, audio, layout, interaction, and presentation fidelity in Blade-Skin-Dashboard.

If another document, implementation shortcut, framework default, generated design, historical reference, or developer assumption conflicts with this directive, **this directive and `AUTHORITY_HIERARCHY.md` win**.

---

# 1. Canonical target

The canonical visual and behavioral target is:

**The developer-approved `BladeDash(2005)` working Freestyle 3/FSD skin package.**

Approved local package:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

The project owner has run this skin and approved its appearance and behavior as the desired frontend.

**BladeDash(2005) is the authority.**

Retail Xbox 360 Blades build 2.0.6770 is supplemental historical reference and is used only for a required state or behavior not adequately defined by BladeDash.

---

# 2. Fidelity objective

The goal is not to recreate Retail 6770 from screenshots.

The goal is to transpose the approved working BladeDash frontend onto a new standalone Xbox 360 host while preserving its visible and interactive behavior.

For states already defined by BladeDash, the intended acceptance reaction is:

> The same BladeDash state running on the standalone host should be difficult to distinguish from the known-good BladeDash state running under its original host.

Host replacement must not visibly reinvent the dashboard.

---

# 3. Authority order

When evidence disagrees, use this order:

1. developer-approved `BladeDash(2005)` running behavior and supplied resources;
2. BladeDash XUI/XUR/XML/audio/resource definitions;
3. explicit project-owner decisions recorded in this repository;
4. confirmed Retail 2.0.6770 evidence, only for gaps not defined by BladeDash;
5. nearby Retail Blades builds for unresolved gaps when equivalence is supported;
6. other historical/community material as clues only;
7. memory, generated mockups, assumptions, or creative guesses are never authoritative.

A Retail 6770 difference is **not** automatically a BladeDash defect.

Do not alter an approved BladeDash-defined state merely because a historical reference differs.

---

# 4. Forbidden interpretation

Codex and contributors must not treat the project as:

- a fresh Retail 6770 recreation;
- Blade-inspired;
- Blade-themed;
- a modernized Blade dashboard;
- a Metro/Blade hybrid;
- a CCLOS skin;
- a concept dashboard;
- a chance to improve or normalize the approved skin;
- a reason to redraw working states from screenshots.

The approved skin is the product frontend.

---

# 5. No unsolicited design decisions

Codex has zero authority to redesign BladeDash-defined presentation.

Without an explicit owner decision or documented technical incompatibility, do not independently:

- change proportions or blade widths;
- change menu spacing or text placement;
- change fonts/sizing/alignment;
- change colors, gradients, gloss, transparency, or textures;
- substitute icons;
- simplify separators;
- alter focus/highlight states;
- alter controller legends;
- move status information;
- change menu hierarchy;
- alter navigation semantics;
- alter animation direction, timing, sequencing, or easing;
- replace dialogs/loading states;
- replace existing XMA sound-event timing;
- import CCLOS visual language;
- normalize quirks merely because another historical source looks different.

Preserve the approved frontend first.

---

# 6. Reuse-first rule

For a state present in BladeDash, Codex must:

1. identify the existing XUI/XUR/resource that defines it;
2. identify the host/data/event contract it expects;
3. reuse the existing presentation;
4. implement the missing standalone host contract behind it;
5. bind dynamic data through presentation models/adapters;
6. run the state under the standalone host;
7. compare it against the known-good BladeDash state;
8. correct migration regressions before declaring it complete.

Do not require a Retail 6770 screenshot before reusing a state that BladeDash already defines.

---

# 7. Reference-gap rule

A `REFERENCE_GAP` exists only when:

1. BladeDash does not adequately define the required state/behavior;
2. no explicit owner decision defines it; and
3. supplemental historical evidence is insufficient.

For a genuine gap, consult Retail 2.0.6770 first.

If Retail 6770 defines the missing piece, reconstruct only that missing piece in a manner compatible with the approved BladeDash frontend.

Do not use a gap in one state as permission to redesign other BladeDash-defined states.

---

# 8. Fidelity dimensions

For BladeDash-defined states, validate the standalone migration across all applicable dimensions.

## Geometry

Verify:

- active/inactive blade positions;
- blade width/curvature;
- separators and visible blade edges;
- content bounds;
- menu origin and row spacing;
- dialog dimensions;
- image/art bounds;
- controller legend positions;
- safe-area behavior.

## Typography

Verify:

- font selection;
- size/weight;
- capitalization;
- baseline and spacing;
- alignment;
- truncation/wrapping;
- selected/disabled text behavior.

## Surface treatment

Verify:

- colors;
- gradients;
- gloss;
- metallic separators;
- transparency/alpha;
- highlights;
- shadows/effects;
- selected/disabled brightness.

## Navigation

Verify:

- horizontal blade switching;
- vertical movement;
- initial focus;
- focus persistence/restoration;
- wrap/no-wrap behavior;
- A/B/X/Y behavior;
- shoulder/trigger behavior where defined;
- child-view/back behavior.

## Motion

Verify:

- direction;
- start/end positions;
- travel distance;
- duration;
- easing;
- sequencing;
- content refresh timing;
- dialog motion;
- full-screen transitions.

## Audio

Verify:

- focus move;
- confirm/cancel;
- blade change;
- dialog/error events;
- trigger timing relative to animations.

---

# 9. Stable frontend contract

Once a BladeDash-defined state works correctly under the standalone host, freeze its visible/behavioral contract.

Backend milestones may change:

- service implementation;
- data sources;
- caching;
- download mechanics;
- scanner implementation;
- networking;
- launch implementation;
- Title Update logic;
- persistence.

They must not change the approved frontend contract unless the owner explicitly authorizes it.

---

# 10. Backend adaptation rule

Canonical architecture:

```text
BladeDash XUI/XUR frontend
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
```

The backend adapts to BladeDash.

BladeDash must not be visually reshaped to accommodate CCLOS/backend terminology or schemas.

---

# 11. Marketplace fusion rule

The existing BladeDash Marketplace-facing presentation is authoritative wherever present.

Backend:

```text
ConsoleCrate Marketplace Services
              |
BladeMarketplaceAdapter
              |
BladeDash-compatible presentation model
              |
Existing BladeDash XUI
```

Do not expose CCLOS cards, CCLOS navigation, REST concepts, server paths, API terminology, or CCLOS download-manager visuals through the Blade frontend.

If BladeDash lacks a required Marketplace state, consult Retail 6770 as supplemental historical evidence for that missing state only.

---

# 12. Standalone rule

The final dashboard must not require Freestyle Dash, Aurora, or the CCLOS application.

It must own or link standalone service implementations for lifecycle, scene hosting, input, game discovery, launching, settings, network/filesystem operations, Marketplace, downloads, Title Updates, and other retained features.

The new XEX replaces the old host. It does not replace the approved frontend.

---

# 13. XUI/XuiTool rule

Codex must inspect the local Xbox 360 XDK/XUI environment and use the actual supported XuiTool/XUI workflow.

Test the supplied `skin.xui` and existing XUR resources directly before declaring any resource unusable or generating a replacement.

Do not invent undocumented XuiTool CLI options.

Do not commit proprietary XDK binaries.

---

# 14. Migration comparison requirement

For major BladeDash-defined states, compare:

```text
Known-good BladeDash(2005) under the working host
                        +
Standalone BladeDashboard.xex state
                        |
                        v
             equivalent capture conditions
                        |
                        +--> side-by-side
                        +--> overlay when useful
                        +--> difference inspection
                        +--> behavior/timing notes
```

Retail 6770 comparison is optional supplemental research for these states and cannot overrule the approved skin.

For a state absent from BladeDash, use Retail 6770 comparison as appropriate for that newly reconstructed state.

---

# 15. Severity levels

Log migration discrepancies as:

- **F0 BLOCKER** — wrong scene/hierarchy, missing major BladeDash element, replacement UI where reusable UI exists, broken navigation, major host-caused visual change.
- **F1 MAJOR** — visibly wrong geometry, font scale, animation, selected state, transition, or audio timing.
- **F2 MODERATE** — noticeable spacing, color, alpha, icon scale, timing, or alignment mismatch.
- **F3 MINOR** — subtle rendering/anti-aliasing/texture/timing differences.

No BladeDash-defined screen may be marked migration-fidelity-complete with open F0 or F1 discrepancies.

---

# 16. Change control

Once a state passes migration fidelity:

- freeze its presentation contract;
- do not modernize it during backend work;
- do not change animation timing without an owner-approved reason;
- do not change colors/layout because a Retail screenshot differs;
- do not normalize existing BladeDash inconsistencies;
- rerun regression checks when shared rendering/navigation code changes.

---

# 17. Status labels

Use these project states:

- `BLADEDASH_DEFINED` — approved skin defines the state/behavior.
- `BLADEDASH_MIGRATION_VERIFIED` — standalone host matches the approved skin.
- `BLADEDASH_GAP_RETAIL_6770` — BladeDash lacks the state and Retail 6770 supplies evidence.
- `REFERENCE_GAP` — BladeDash and available supplemental references do not define it.
- `TECHNICAL_LIMITATION` — platform/runtime prevents exact preservation.
- `OWNER_DECISION_REQUIRED` — an explicit design/scope choice is needed.

Do not use `REFERENCE_GAP` merely because Retail 6770 evidence has not been collected for a state that BladeDash already defines.

---

# 18. Definition of fidelity-complete

For a BladeDash-defined state:

- [ ] Approved BladeDash resource/state identified.
- [ ] Existing presentation reused wherever technically possible.
- [ ] Required FSD host contract identified/replaced.
- [ ] Geometry matches the known-good BladeDash state.
- [ ] Typography placement matches.
- [ ] Colors/effects match.
- [ ] Focus/controller behavior matches.
- [ ] Navigation hierarchy matches.
- [ ] Transition/animation behavior matches.
- [ ] Audio event timing matches where retained.
- [ ] Dynamic backend data does not alter the visible contract.
- [ ] Standalone capture/test produced.
- [ ] No F0 issues remain.
- [ ] No F1 issues remain.
- [ ] Remaining F2/F3 issues are documented.

For a state absent from BladeDash, document the gap and use Retail 6770 evidence under `AUTHORITY_HIERARCHY.md`.

---

# 19. Final acceptance standard

The project succeeds when the approved BladeDash frontend behaves under the standalone XEX as it did under its known-good host while gaining the required standalone ConsoleCrate/CCLOS-backed functionality.

**BladeDash(2005) wins. Retail 6770 fills gaps. Backend implementation must remain subordinate to the approved frontend contract.**
