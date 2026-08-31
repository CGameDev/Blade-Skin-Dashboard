# Retail 6770 Blades Fidelity Directive

## Status

**NON-NEGOTIABLE PROJECT RULE**

This document governs every UI, navigation, animation, audio, layout, and presentation decision in Blade-Skin-Dashboard.

If another document, implementation shortcut, generated design, framework default, or developer assumption conflicts with this directive, **this directive wins**.

---

# 1. Canonical target

The canonical visual and behavioral target is:

**Microsoft Xbox 360 Retail Blades Dashboard — system/dashboard build 2.0.6770**

Primary reference repository:

https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770

Older Blades builds may be studied only when a 6770 state cannot be adequately observed. They must never be blended into the final UI merely because an older screenshot is easier to find.

Build 6770 is the authority.

---

# 2. Exact-replica objective

The target is not “inspired by” the Blades dashboard.

The target is a **standalone recreation whose rendered UI, motion, hierarchy, and controller response are as close to Retail 6770 as technically possible**.

The intended acceptance reaction is:

> When the recreated dashboard and an original Retail 6770 dashboard are shown side by side under equivalent conditions, a viewer familiar with the Xbox 360 Blades dashboard should have difficulty distinguishing them from appearance and interaction alone.

This means visual similarity is not a secondary polish task. Fidelity is a functional requirement.

---

# 3. Forbidden interpretation

Codex and contributors MUST NOT describe or implement this project as:

- Blade-inspired
- Blade-themed
- a modernized Blade dashboard
- a Metro/Blade hybrid
- an Aurora Blade skin
- a CCLOS skin
- a reinterpretation
- a concept dashboard
- an approximation where exact information is available
- a “cleaner” version of Blades
- a “more modern” version of Blades
- a version with usability improvements that change the visible UI

Do not modernize awkward original behaviors simply because a contemporary alternative seems better.

Historical quirks that are observable and technically reproducible are part of the target.

---

# 4. No unsolicited design decisions

Codex has **zero authority to redesign the visual interface**.

Codex must not independently:

- change proportions;
- change blade widths;
- change menu spacing;
- change font sizing;
- change alignment;
- substitute modern icons;
- introduce rounded cards;
- introduce Metro tiles;
- change gradients;
- flatten gloss effects;
- simplify metallic separators;
- add floating UI;
- change the hierarchy;
- replace full-screen legacy views with blade views;
- replace blade navigation with tabs;
- alter controller legends;
- move status information;
- add new decorative transitions;
- change animation timing for taste;
- change colors for consistency;
- copy CCLOS visual components into this project.

When the reference looks unusual by modern standards, reproduce it.

---

# 5. Reference-first rule

No major UI screen may be implemented from memory.

Before implementing a screen or state, Codex must:

1. Identify the exact Retail 6770 screen/state being recreated.
2. Record the reference source in `docs/REFERENCE_MATRIX.md`.
3. Capture or identify at least one reliable still reference.
4. Where motion occurs, identify a motion/video reference or derive the state sequence from repeated observation.
5. Record observable geometry, hierarchy, focus state, text placement, colors, and controller behavior.
6. Implement only after the reference is documented.
7. Capture the recreated state.
8. Compare recreated and original states.
9. Correct discrepancies before declaring the screen complete.

If reliable information is unavailable, Codex must mark the item `REFERENCE GAP` rather than inventing a solution.

---

# 6. Source priority order

When references disagree, use this order:

1. **Confirmed Retail 6770 footage/screenshot/state from original hardware or the canonical 6770 build.**
2. Multiple independent Retail 6770 visual references.
3. Retail 6717/6690/6683 material only when the element is demonstrably unchanged in 6770.
4. Earlier Blades material only as structural evidence.
5. Community recreation material only as a clue, never as visual authority.
6. Memory, assumptions, or generated guesses are not acceptable references.

The existing Aurora Blade skin is supplementary reference only. It is not authoritative.

---

# 7. Required fidelity dimensions

Each recreated state must be evaluated against the original for all applicable dimensions below.

## 7.1 Geometry

Verify:

- active blade position;
- inactive blade edge positions;
- blade width;
- blade curvature;
- separator width;
- separator curvature;
- visible left/right tab widths;
- content-area width;
- top margins;
- bottom margins;
- side margins;
- row heights;
- list spacing;
- panel dimensions;
- dialog dimensions;
- gamercard dimensions;
- image/art dimensions;
- controller legend location;
- safe-area behavior.

## 7.2 Typography

Verify:

- font family or the closest redistributable/locally available equivalent required by the runtime;
- size;
- weight;
- capitalization;
- line spacing;
- baseline;
- letter spacing where observable;
- alignment;
- truncation behavior;
- wrapping behavior;
- highlight/selected text behavior;
- disabled text behavior.

## 7.3 Color and surface treatment

Verify:

- blade base colors;
- gradients;
- gloss layers;
- metallic/silver separators;
- highlight colors;
- transparency;
- translucency;
- blur-like treatment where reproducible;
- shadows;
- background brightness;
- selected-state brightness;
- disabled-state brightness;
- overlay dimming.

Do not derive final colors from screenshots captured through unknown post-processing when a cleaner reference is available.

## 7.4 Icons and imagery

Verify:

- visual size;
- position;
- aspect ratio;
- crop;
- selected state;
- disabled state;
- animation state;
- relationship to text.

Do not place copyrighted Microsoft assets in public release packages unless the project owner separately establishes redistribution rights.

## 7.5 Navigation

Verify:

- horizontal blade switching;
- vertical list movement;
- initial focus;
- focus persistence;
- wrap/no-wrap behavior;
- A/confirm behavior;
- B/back behavior;
- X/Y behavior where present;
- shoulder/trigger behavior where present;
- Guide-button behavior where implementable;
- focus restoration when returning from deeper views;
- full-screen transition behavior.

## 7.6 Motion

Verify:

- animation direction;
- start position;
- end position;
- travel distance;
- duration;
- easing profile;
- relative movement of foreground/background layers;
- sequencing between blade movement and content refresh;
- focus transition timing;
- dialog opening/closing motion;
- full-screen segue behavior.

A generic slide or fade is not acceptable where the original motion is observable.

## 7.7 Audio event timing

Where audio is implemented, verify:

- event trigger;
- timing relative to motion;
- one-shot vs repeated behavior;
- focus-move behavior;
- confirm behavior;
- cancel behavior;
- blade-change behavior;
- error behavior;
- notification behavior.

Release packages must use audio that may legally be distributed.

---

# 8. Blade architecture rule

The UI must be implemented as a real Blade-oriented state architecture, not a set of unrelated pages wearing Blade-colored headers.

Top-level categories share the Blades hierarchy and transition horizontally.

Where Retail 6770 keeps neighboring blade edges visible, the recreation must keep them visible.

Where Retail 6770 transitions into a full-screen child view and removes the neighboring blade indicators to reclaim space, the recreation must do the same.

Do not force all screens into one visual template.

---

# 9. Full-screen legacy-view rule

Some original Blades views transition away from the constrained top-level blade layout and use more of the display area.

Examples documented in historical references include game/library and storage-style deeper views.

Codex must reproduce the specific 6770 behavior of each screen.

The existence of visible side blades on the main dashboard does **not** authorize keeping them visible on every child screen.

---

# 10. Marketplace fusion rule

The Marketplace frontend must look and behave like the Retail 6770 Marketplace experience to the maximum extent technically possible.

The backend is the existing ConsoleCrate / CCLOS Marketplace infrastructure.

Required architecture:

```text
ConsoleCrate Marketplace Services
              |
              v
BladeMarketplaceAdapter
              |
              v
Retail-6770-compatible UI model
              |
              v
Blades Marketplace XUI
```

The service adapts to the UI.

The UI does not visibly adapt to the modern service.

Do not expose CCLOS card layouts, CCLOS navigation, modern REST concepts, server filenames, internal API terminology, or modern download-manager visuals through the Blade frontend.

---

# 11. Standalone rule

The final dashboard must not require Aurora.

It must not depend on:

- Aurora scenes;
- Aurora skin APIs;
- Aurora navigation;
- Aurora database schemas;
- Aurora metadata exposure;
- Aurora launch behavior;
- Aurora UI events.

The old Aurora Blade skin may be inspected for project history and useful measurements but must not become the runtime foundation.

---

# 12. XUI/XuiTool rule

XUI is the preferred UI implementation technology where appropriate for the Xbox 360 target.

Codex must inspect the local development environment and document:

- installed XDK location;
- XuiTool location;
- usable XUI authoring/build tools;
- compiler/linker path;
- XDK include paths;
- XDK library paths;
- XEX packaging workflow;
- any repeatable command-line operations available for XUI/XUR generation.

Codex should automate repeatable build steps wherever technically possible.

Codex must **not assume** XuiTool has an undocumented CLI interface. If a GUI-only step remains necessary, document that step exactly and isolate it so the rest of the build remains reproducible.

Do not commit proprietary XDK binaries to this repository.

---

# 13. Clean-room / redistribution boundary

The canonical archive contains original Microsoft dashboard binaries/resources. Those files may be useful for historical identification and local reference, but they are not project source.

The public repository and distributable release must not include or require:

- `dash.xex` from the Microsoft dashboard;
- Microsoft dashboard executable code;
- extracted Microsoft source code;
- proprietary Microsoft XDK redistributables that cannot legally be shared;
- original proprietary resource packages such as `shrdres.xzp` unless redistribution permission is independently established;
- copied Microsoft copyrighted artwork/audio where redistribution is not permitted.

The implementation must use newly written application code.

Visual fidelity may be achieved through newly authored resources, runtime-generated geometry/effects, and developer-local comparison material that is not distributed.

Do not decompile or copy original executable implementation into project source.

---

# 14. Side-by-side validation requirement

Every major state must eventually support visual validation using two captures under equivalent output settings:

```text
Original Retail 6770 capture
            +
Recreated dashboard capture
            |
            v
Scale/align to common canvas
            |
            +--> 50/50 overlay
            +--> blink comparison
            +--> difference image
            +--> edge/alignment inspection
```

A fidelity helper may calculate difference metrics, but numeric scores do not replace human review.

Comparison captures must use equivalent:

- resolution;
- aspect ratio;
- overscan/safe-area assumptions;
- screen state;
- selected item;
- data population where possible;
- animation frame when comparing motion states.

---

# 15. Fidelity severity levels

Log discrepancies using:

- **F0 BLOCKER** — wrong screen structure, wrong blade geometry, wrong hierarchy, obvious modern redesign, incorrect major color, missing canonical element.
- **F1 MAJOR** — visibly wrong position/size, wrong font scale, wrong animation behavior, incorrect selected state, wrong full-screen behavior.
- **F2 MODERATE** — noticeable spacing, color, alpha, icon-scale, timing, or alignment mismatch.
- **F3 MINOR** — subtle pixel, anti-aliasing, texture, or timing differences that do not change the overall read.

No screen may be marked fidelity-complete with open F0 or F1 discrepancies.

F2 issues must be resolved unless a documented technical limitation prevents it.

F3 issues may remain only when documented and approved.

---

# 16. Change-control rule

Once a screen/state passes its fidelity gate:

- freeze its visual contract;
- do not refactor it into a visibly different layout;
- do not modernize it during backend work;
- do not alter animation timing without a new reference finding;
- do not change colors because another screen uses a different value;
- do not normalize historical inconsistencies.

A later backend milestone may change data plumbing without changing the approved visible state.

---

# 17. No assumption rule

When Codex encounters ambiguity, it must not silently guess.

Use one of these documented states:

- `CONFIRMED_6770`
- `CONFIRMED_NEARBY_BUILD_UNCHANGED`
- `REFERENCE_GAP`
- `TECHNICAL_LIMITATION`
- `OWNER_DECISION_REQUIRED`

For implementation work that can continue without the missing fact, leave a placeholder behind the canonical geometry rather than inventing new UI.

---

# 18. Definition of fidelity-complete

A state is not complete because it compiles or navigates.

A state is fidelity-complete only after all applicable items are true:

- [ ] Canonical Retail 6770 reference identified.
- [ ] Geometry documented.
- [ ] Blade boundaries match.
- [ ] Typography matches.
- [ ] Colors/gradients/transparency match.
- [ ] Icon/image placement matches.
- [ ] Initial focus matches.
- [ ] Controller navigation matches.
- [ ] Selected/focused/disabled states match.
- [ ] Transition direction matches.
- [ ] Transition duration/easing has been measured or visually matched.
- [ ] Full-screen vs blade-edge behavior matches.
- [ ] Recreated capture produced.
- [ ] Side-by-side comparison completed.
- [ ] Overlay/difference comparison completed where practical.
- [ ] No F0 issues remain.
- [ ] No F1 issues remain.
- [ ] Remaining F2/F3 differences are documented.
- [ ] Backend data, if connected, does not alter the visual contract.

---

# 19. Final acceptance standard

The project is considered successful only when the complete dashboard can be evaluated as a **Retail 6770 recreation**, not merely as a homebrew dashboard with a Blades theme.

Functional additions are valuable only when they remain visually subordinate to the original interface contract.

**The reference wins. Fidelity first. Backend second. Creative reinterpretation is not permitted.**
