# BladeDash Reference and Gap Matrix

## Purpose

This file tracks where the approved `BladeDash(2005)` package already defines the product frontend, which standalone service replaces each FSD-era host dependency, and where supplemental historical research is actually needed.

**Do not block implementation of a BladeDash-defined state merely because a Retail 6770 screenshot has not been collected.**

Authority is defined by `docs/AUTHORITY_HIERARCHY.md`. Product/scope choices are defined by `docs/OWNER_DECISIONS.md`.

---

# Reference/status labels

- `BLADEDASH_DEFINED` — approved skin directly defines the state/behavior/presentation.
- `BLADEDASH_MIGRATION_VERIFIED` — standalone host reproduces the approved state/behavior.
- `BLADEDASH_PARTIAL` — approved skin defines part of the state, but host behavior/details require additional implementation/evidence.
- `BLADEDASH_GAP_RETAIL_6770` — BladeDash does not define the required state and confirmed Retail 6770 evidence supplies it.
- `CONSOLECRATE_BACKED` — retained BladeDash feature has an owner-approved ConsoleCrate/CCLOS backend direction.
- `PLATFORM_BACKED` — retained BladeDash feature is implemented primarily through Xbox/platform services.
- `SERVICE_EVALUATION` — BladeDash defines the UI but the original external service is obsolete/uncertain and a real replacement must be evaluated.
- `REFERENCE_GAP` — BladeDash, owner decisions and available historical evidence do not define the required presentation/behavior.
- `TECHNICAL_LIMITATION` — exact behavior cannot currently be reproduced because of platform/runtime constraints.
- `OWNER_DECISION_REQUIRED` — a product/scope choice not already resolved in `OWNER_DECISIONS.md` is required.
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

For any state/resource present here, BladeDash is the visual/behavioral authority.

---

# Supplemental historical source

Retail Xbox 360 Blades build 2.0.6770 may be consulted only for genuine gaps not adequately defined by BladeDash.

Historical archive:

`https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770`

Boundary: original Microsoft binaries/resources are historical reference only and are not project runtime/source dependencies.

---

# Owner-resolved feature matrix

Codex must replace initial resource guesses with exact scene/control paths and compatibility status during Milestone 000.

| ID | Area | BladeDash state/feature | Frontend authority | Standalone direction |
|---|---|---|---|---|
| ROOT-001 | Root | Main dashboard shell | BLADEDASH_DEFINED | Reuse `main.xur`/corresponding XUI; standalone host owns lifecycle/navigation. |
| ROOT-002 | Root | Splash/loading presentation | BLADEDASH_DEFINED | Reuse existing splash/loading resources and timing. No CCLOS OOBE. |
| BLADE-001 | Navigation | Horizontal Blade navigation | BLADEDASH_DEFINED | Preserve timelines/focus behavior; replace FSD host events only. |
| BLADE-002 | Navigation | Active/inactive blade geometry | BLADEDASH_DEFINED | Use existing geometry; do not redraw from Retail screenshots. |
| GAME-001 | Games | Game list/browse | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | `GamesList` -> Blade library adapter -> CCLOS/ConsoleCrate game discovery. |
| GAME-002 | Games | Game detail/info | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Existing `gameinfo` presentation -> metadata/cache/launch adapters. |
| GAME-003 | Games | Game controls/actions | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Existing controls -> standalone/CCLOS launch and action services. |
| ACH-001 | Achievements | Achievements UI | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Existing Achievements UI -> BladeAchievementAdapter -> CCLOS/Xbox achievement service. |
| TU-001 | Title Updates | Title Update manager | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Existing TU UI -> BladeTitleUpdateAdapter -> CCLOS Title Update service. |
| TRAIN-001 | Trainers | Trainer scene | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Existing Trainers UI -> BladeTrainerAdapter -> CCLOS trainer/runtime handling. |
| DVD-001 | Disc | CopyDVD scene | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Existing `CopyDVD` UI -> BladeDiscCopyAdapter -> CCLOS Disc-to-GOD service. |
| SAVE-001 | Saved Games | Saved-game view | BLADEDASH_DEFINED + PLATFORM_BACKED | Preserve existing UI; implement through available Xbox storage/content services. |
| FILE-001 | Files | File/path manager family | BLADEDASH_DEFINED + PLATFORM_BACKED | Existing file/path UI -> filesystem adapters + reusable ConsoleCrate filesystem logic. |
| PROF-001 | Profile | Profile/gamercard/avatar | BLADEDASH_DEFINED + PLATFORM_BACKED | Existing UI -> Xbox profile/platform services + reusable CCLOS helpers where applicable. |
| SYS-001 | System | System information/settings | BLADEDASH_DEFINED + PLATFORM_BACKED | Existing UI -> Xbox platform/system services. |
| NET-001 | Network | Network/status/settings | BLADEDASH_DEFINED/PARTIAL + PLATFORM_BACKED | Preserve existing Blade state; map to standalone network service. Retail 6770 only for a genuinely absent presentation detail. |
| COVER-001 | CoverFlow | CoverFlow presentation | BLADEDASH_DEFINED + CONSOLECRATE_BACKED | Preserve meshes/shaders/UI; feed library/artwork through adapters. |
| MARKET-001 | Marketplace | Marketplace-facing state(s) | BLADEDASH_DEFINED/PARTIAL + CONSOLECRATE_BACKED | Existing Blade Marketplace hierarchy -> BladeMarketplaceAdapter -> ConsoleCrate Marketplace. Visible name remains `Marketplace`. |
| DOWNLOAD-001 | Downloads | Download/progress state(s) | BLADEDASH_DEFINED/PARTIAL + CONSOLECRATE_BACKED | Blade presentation -> BladeDownloadAdapter -> CCLOS queue/high-throughput download pipeline. |
| MEDIA-001 | Media | Existing Media / Media Center UI | BLADEDASH_DEFINED | **Frozen presentation. Must not be visually redesigned.** |
| MEDIA-002 | Media | Watch TV functionality | BLADEDASH_DEFINED frontend pattern + CONSOLECRATE_BACKED | Existing Blade Media Center -> BladeMediaAdapter -> CCLOS Watch TV/media services. Use existing list/menu/control geometry only. |
| POPUP-001 | Dialogs | Popup/dialog family | BLADEDASH_DEFINED | Preserve existing dialog presentation; map `ScnPopup` behavior. |
| HTTP-001 | Web/HTTP | HTTP server/web-facing settings | BLADEDASH_DEFINED + SERVICE_EVALUATION | Retain only with a real standalone service; never leave dead FSD-era endpoints. |
| WEATHER-001 | Weather | Weather scene | BLADEDASH_DEFINED + SERVICE_EVALUATION | Preserve UI; implement only if a real replacement service is available/approved. Otherwise use existing unavailable behavior or owner decision. |
| LEGACY-NET-001 | Legacy network | Xlink Kai/JQE-era functions | BLADEDASH_DEFINED + SERVICE_EVALUATION | Evaluate real replacement. Do not fake or revive dead services merely for completeness. |
| PLUGIN-001 | Plugins/updater | FSD-era plugin/update functions | BLADEDASH_DEFINED + SERVICE_EVALUATION | Evaluate real standalone replacement; no dead calls. |
| GUIDE-001 | Guide | Guide/overlay behavior | BLADEDASH_PARTIAL | Determine package-defined behavior vs platform technical limits; Retail evidence only for missing portion. |

---

# Required per-state implementation record

For each retained state, add/update:

```text
State ID:
BladeDash scene/resource:
BladeDash authority status:
Owner scope status:
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
CCLOS provenance entry:
Migration status:
Technical limitations:
Genuine missing details:
Retail 6770 evidence required? yes/no
Retail 6770 source (only when required):
Open fidelity issues:
```

---

# Evidence and scope rules

1. Start with the approved BladeDash package and known-good running behavior.
2. Start with `OWNER_DECISIONS.md` before asking the owner whether a listed feature is retained.
3. Do not search Retail 6770 first for a state already defined by BladeDash.
4. Do not mark a state `REFERENCE_GAP` because historical screenshots are missing when BladeDash defines it.
5. For retained FSD-era features, first look for a real ConsoleCrate/CCLOS Core or Xbox platform replacement.
6. CopyDVD, Achievements, Title Updates and Trainers are explicitly retained and mapped to CCLOS-backed functionality.
7. Watch TV is explicitly retained as functionality beneath the **unchanged Blade Media Center presentation**.
8. Do not import CCLOS Watch TV/Marketplace/Downloads UI.
9. For obsolete services with no real replacement, do not fake behavior or leave dead calls.
10. Keep non-redistributable captures/resources developer-local and record metadata/path placeholders in Git.
11. Record exact CCLOS source commit provenance for reused backend subsystems in `BACKEND_PROVENANCE.md`.

---

# Milestone 000 required inventory pass

Before substantial new UI is created, Codex must inventory/classify:

- all `.xur` scenes;
- relevant `skin.xui` resources;
- XML menu/configuration definitions;
- host-facing class/data contracts;
- navigation/event bindings;
- animation timelines;
- audio triggers;
- owner-retained service mappings;
- obsolete services requiring evaluation.

Then create/update `docs/FSD_COMPATIBILITY_MATRIX.md`.

## Final rule

**BladeDash-defined states are already referenced. Owner-retained features keep their Blade face and receive real ConsoleCrate/CCLOS/Xbox functionality underneath. Retail 6770 research begins only where BladeDash and owner decisions end.**
