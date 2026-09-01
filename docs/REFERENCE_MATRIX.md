# BladeDash Reference and Gap Matrix

## Purpose

This file tracks where the approved `BladeDash(2005)` package already defines the product frontend and where supplemental historical research is actually needed.

**Do not block implementation of a BladeDash-defined state merely because a Retail 6770 screenshot has not been collected.**

Authority is defined by `docs/AUTHORITY_HIERARCHY.md`.

---

# Reference status labels

- `BLADEDASH_DEFINED` — approved skin directly defines the state/behavior/presentation.
- `BLADEDASH_MIGRATION_VERIFIED` — standalone host reproduces the approved state/behavior.
- `BLADEDASH_PARTIAL` — approved skin defines part of the state, but some host behavior/details require additional evidence.
- `BLADEDASH_GAP_RETAIL_6770` — BladeDash does not define the required state and confirmed Retail 6770 evidence supplies it.
- `CONFIRMED_NEARBY_BUILD_UNCHANGED` — nearby Retail Blades build used only for a genuine BladeDash gap with evidence of equivalence.
- `STRUCTURAL_REFERENCE_ONLY` — useful for hierarchy/behavior clues only.
- `REFERENCE_GAP` — BladeDash, owner decisions, and available historical evidence do not adequately define the required state.
- `TECHNICAL_LIMITATION` — exact behavior cannot currently be reproduced because of platform/runtime constraints.
- `OWNER_DECISION_REQUIRED` — scope/design choice must come from the project owner.
- `NOT_APPLICABLE` — outside retained standalone scope.

---

# Canonical frontend source

Approved developer-local package:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

Expected extraction:

```text
references/local/BladeDash(2005)/
```

For any state/resource present here, BladeDash is the authority.

Useful package evidence includes:

- `skin.xui`;
- compiled `.xur` scenes;
- XML configuration;
- XMA audio;
- textures/DDS resources;
- fonts;
- meshes/shaders;
- running behavior under the known-good host.

---

# Supplemental historical source

Retail Xbox 360 Blades build 2.0.6770 may be consulted only for genuine gaps not adequately defined by BladeDash.

Historical archive:

`https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770`

Boundary: original Microsoft binaries/resources are historical reference only and are not project runtime/source dependencies.

Structural reference when needed:

`https://github.com/flipacholas/Architecture-of-consoles/blob/master/articles/xbox-360.Rmd.md`

---

# Initial BladeDash inventory matrix

Codex must replace these initial classifications with exact scene/resource paths and compatibility status during Milestone 000.

| ID | Area | State / contract | Initial authority | Migration / research action |
|---|---|---|---|---|
| ROOT-001 | Root | Main dashboard shell | BLADEDASH_DEFINED | Locate `main.xur`/corresponding `skin.xui` resources and reproduce under standalone host. |
| ROOT-002 | Root | Splash/loading presentation | BLADEDASH_DEFINED | Reuse existing splash/loading resources and preserve event timing. |
| BLADE-001 | Navigation | Horizontal Blade navigation | BLADEDASH_DEFINED | Preserve existing timelines/focus behavior; identify FSD host events. |
| BLADE-002 | Navigation | Active/inactive blade geometry | BLADEDASH_DEFINED | Use existing XUI geometry; do not remeasure from Retail screenshots unless resource becomes unusable. |
| GAME-001 | Games | Game list/browse presentation | BLADEDASH_DEFINED | Map `GamesList`/related contracts to Blade library adapter. |
| GAME-002 | Games | Game detail/info | BLADEDASH_DEFINED | Inventory `gameinfo.xur` and related actions. |
| GAME-003 | Games | Game controls/actions | BLADEDASH_DEFINED | Inventory `GameControls.xur`; map launch/action contracts. |
| ACH-001 | Achievements | Achievements UI | BLADEDASH_DEFINED | Inventory `Achievements.xur`; implement `AchievementManager` compatibility. |
| TU-001 | Title Updates | Title Update manager | BLADEDASH_DEFINED | Inventory `TitleUpdateManager.xur`; map to shared Title Update service. |
| SAVE-001 | Saved Games | Saved-game view | BLADEDASH_DEFINED | Inventory `savedgames.xur`; determine retained functionality. |
| TRAIN-001 | Trainers | Trainer scene | BLADEDASH_DEFINED | Inventory `Trainers.xur`; retain only if in final standalone scope. |
| DVD-001 | Disc | Copy DVD scene | BLADEDASH_DEFINED | Inventory `CopyDVD.xur`; determine standalone service mapping. |
| FILE-001 | Files | File/path manager family | BLADEDASH_DEFINED | Map file/path list contracts to standalone filesystem services. |
| PROF-001 | Profile | Profile/gamercard/avatar presentation | BLADEDASH_DEFINED | Map `ScnProfile`/avatar contracts to available Xbox/profile services. |
| SYS-001 | System | System information/settings | BLADEDASH_DEFINED | Map `ScnSysInfo`/settings contracts to platform services. |
| MEDIA-001 | Media | Music/video/media scenes | BLADEDASH_DEFINED | Inventory retained scenes and service requirements. |
| WEATHER-001 | Weather | Weather scene | BLADEDASH_DEFINED | Decide retained scope/service viability without redesigning scene. |
| POPUP-001 | Dialogs | Popup/dialog family | BLADEDASH_DEFINED | Preserve existing dialog presentation; map `ScnPopup` behavior. |
| COVER-001 | CoverFlow | CoverFlow presentation | BLADEDASH_DEFINED | Inventory meshes/shaders/resources and FSD host bindings. |
| HTTP-001 | Web/HTTP | HTTP server/web-facing settings | BLADEDASH_DEFINED | Determine retained scope and host-service replacement. |
| MARKET-001 | Marketplace | Marketplace-facing state(s) | BLADEDASH_PARTIAL | First inventory what BladeDash actually contains; use ConsoleCrate adapter. Consult Retail 6770 only for missing states. |
| NET-001 | Network | Network-facing state(s) | BLADEDASH_PARTIAL | Use existing skin state where present; Retail 6770 only for absent required presentation. |
| GUIDE-001 | Guide | Guide/overlay behavior | BLADEDASH_PARTIAL | Determine what package defines vs platform limitation. Use historical evidence only for missing portion. |

---

# Required per-state record

For each retained state, add or update a record containing:

```text
State ID:
BladeDash scene/resource:
BladeDash authority status:
Known-good runtime capture/path:
Relevant skin.xui resource/control IDs:
Expected FSD host contract(s):
Expected data fields:
Expected button/events:
Transition/navigation behavior:
Animation/timeline references:
Audio-event references:
Standalone facade:
Blade adapter:
Underlying service:
Migration status:
Technical limitations:
Genuine missing details:
Retail 6770 evidence required? yes/no
Retail 6770 source (only when required):
Open fidelity issues:
```

---

# Evidence collection rules

1. Start with the approved BladeDash package and known-good running behavior.
2. Do not search Retail 6770 first for a state already defined by BladeDash.
3. Do not mark a state `REFERENCE_GAP` merely because historical screenshots are missing.
4. If a BladeDash state is incomplete, identify the exact missing portion before historical research.
5. Use Retail 6770 only for that missing portion.
6. Nearby builds are lower-priority evidence for genuine gaps only.
7. Generated mockups are never authoritative evidence.
8. Do not silently replace BladeDash behavior because another historical source differs.
9. Keep non-redistributable captures/resources developer-local and record metadata/path placeholders in Git.
10. Migration comparison should use equivalent BladeDash original-host and standalone-host states whenever possible.

---

# Milestone 000 required inventory pass

Before substantial new UI is created, Codex must inventory and classify:

- all `.xur` scenes;
- relevant `skin.xui` resources;
- XML menu/configuration definitions;
- host-facing class/data contracts;
- navigation/event bindings;
- animation timelines;
- audio triggers;
- retained vs optional features.

Then create/update `docs/FSD_COMPATIBILITY_MATRIX.md`.

The purpose of research is now to **fill specific gaps**, not to recreate the existing BladeDash frontend from scratch.

---

# Final rule

**BladeDash-defined states are already referenced. Retail 6770 research begins only where BladeDash ends.**
