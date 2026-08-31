# Milestone 001 — Retail 6770 Exact Standalone Blades Replica

## Milestone type

**Foundation + complete first-production recreation milestone**

## Target repository

`CGameDev/Blade-Skin-Dashboard`

## Canonical UI target

**Xbox 360 Retail Blades Dashboard — build 2.0.6770**

## Core objective

Build a standalone Xbox 360 dashboard application that recreates the Retail 6770 Blades dashboard with extremely high visual and interaction fidelity.

The final target is not general resemblance. Under matched resolution/state, a side-by-side comparison should make the recreated dashboard difficult to distinguish from an original 6770 dashboard from visual presentation and interaction alone.

The application must be newly implemented, independent of Aurora, and capable of using modern ConsoleCrate backend services without exposing a modern visual layer.

---

# 0. Mandatory preconditions

Codex MUST read before implementation:

- `README.md`
- `docs/FIDELITY_DIRECTIVE.md`
- `docs/CODEX_EXECUTION_RULES.md`
- `docs/REFERENCE_MATRIX.md`

The fidelity directive overrides convenience and creative preference.

Do not implement screens before completing the relevant reference entry.

---

# 1. Scope

This milestone establishes the complete architecture and implements the major Retail 6770 dashboard experience to the point where the standalone dashboard can be built, launched, navigated, populated with real local/service data, and visually compared with the original.

Included:

- local Xbox 360/XDK environment discovery;
- XUI/XuiTool workflow discovery;
- standalone XEX project foundation;
- scene/navigation architecture;
- Retail 6770 top-level Blade shell;
- canonical top-level Blade navigation;
- full-screen child-view transitions;
- Games-facing dashboard views;
- Marketplace-facing dashboard views;
- Media-facing dashboard views;
- System/Settings-facing dashboard views;
- profile/gamercard presentation where APIs permit;
- controller focus/navigation states;
- dialogs and confirmation patterns needed by implemented flows;
- original-style loading/empty/error presentation where references exist;
- ConsoleCrate Marketplace adapter integration;
- local installed-content discovery;
- game/application launching;
- settings persistence;
- fidelity capture/comparison tooling;
- performance safeguards;
- build/release documentation.

Not included unless required for a canonical 6770 visible state:

- Metro/NXE UI;
- CCLOS UI components;
- Aurora skin runtime;
- a redesigned Marketplace;
- a modern dashboard guide/overlay redesign;
- speculative new top-level blades;
- feature additions that visibly change the original hierarchy.

---

# 2. Non-negotiable constraints

## 2.1 No Aurora dependency

Standalone means standalone.

Do not depend upon Aurora for:

- boot;
- scene rendering;
- data;
- game metadata;
- launching;
- focus/navigation;
- achievements;
- settings;
- storage;
- Marketplace;
- notifications.

The existing Blade-on-Aurora project is historical/supplementary reference only.

## 2.2 No CCLOS visual reuse

CCLOS may supply service infrastructure.

CCLOS visual components must not appear in the Blade recreation.

## 2.3 No visual modernization

Do not improve the design.

Do not make it cleaner.

Do not normalize inconsistencies.

Do not widen areas because modern displays are wider.

Do not replace original-looking dialogs with modern ones.

Do not add new animations when the original already defines the behavior.

## 2.4 No proprietary project-source dependency

Do not commit original Microsoft dashboard binaries, resource packages, extracted executable code, or proprietary XDK redistributables.

The canonical archive is reference material.

---

# 3. Canonical reference material

Primary:

`https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770`

The 6770 directory identifies original build artifacts such as `dash.xex` and `shrdres.xzp`. These are historical reference artifacts and must not become project runtime dependencies or redistributed project content.

Secondary structural reference:

`https://github.com/flipacholas/Architecture-of-consoles/blob/master/articles/xbox-360.Rmd.md`

This reference documents important Blades hierarchy behavior including overlapping top-level blades and deeper full-screen views.

Additional 6770-specific footage/screenshots may be added to `REFERENCE_MATRIX.md` after verification.

---

# 4. Target architecture

```text
+------------------------------------------------------------+
|                Retail 6770-compatible XUI UI               |
+------------------------------------------------------------+
| Scene Controllers | Focus Router | Animation Coordinator   |
+------------------------------------------------------------+
| Presentation Models / Blade-compatible View Models         |
+------------------------------------------------------------+
| Adapters                                                   |
| Marketplace | Library | Profile | Storage | Network | Media|
+------------------------------------------------------------+
| Services                                                   |
| HTTP | Cache | Filesystem | Launch | Settings | Metadata   |
+------------------------------------------------------------+
| Xbox 360/XDK platform                                      |
+------------------------------------------------------------+
```

Rules:

- UI must never bind directly to CCLOS UI classes.
- backend schemas must be translated through adapters;
- scene controllers own UI state, not networking;
- blocking work must stay off the render/input path;
- reference geometry must be centralized in reusable constants/data.

---

# 5. Proposed repository structure

Codex may adjust implementation-language details only when required by the detected XDK project type, but conceptual separation must remain.

```text
Blade-Skin-Dashboard/
  README.md
  docs/
    FIDELITY_DIRECTIVE.md
    CODEX_EXECUTION_RULES.md
    MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md
    REFERENCE_MATRIX.md
    BUILD_ENVIRONMENT.md
    ARCHITECTURE.md
    XUI_WORKFLOW.md
    CHECKPOINT_STATUS.md
  src/
    app/
    core/
    navigation/
    platform/
    services/
    adapters/
      marketplace/
      library/
      profiles/
      storage/
      network/
      media/
    presentation/
    diagnostics/
  ui/
    xui/
    bindings/
    resources/
    generated/
  tools/
    build/
    fidelity/
  tests/
    navigation/
    adapters/
    fidelity/
  build/
  releases/
```

Generated or proprietary toolchain content must be excluded appropriately.

---

# 6. Phase A — local toolchain discovery

## Goal

Establish the actual build environment before writing dashboard code.

## Tasks

- locate Xbox 360 XDK;
- record XDK version;
- locate `XuiTool.exe`;
- locate XUI headers/libraries;
- identify Visual Studio/XDK project integration;
- identify compiler/linker/XEX packaging tools;
- identify any supported XUI-to-XUR workflow;
- inspect current environment variables;
- identify a known working Xbox 360 project/build pattern available locally if present;
- verify Codex can run safe local build commands under the current sandbox/approval settings;
- record GUI-only XuiTool actions separately if automation is unavailable.

## Deliverable

`docs/BUILD_ENVIRONMENT.md`

It must contain actual detected paths, versions, verified commands, and unresolved prerequisites.

## Gate A

Do not begin full UI implementation until one minimal Xbox 360 XEX/XUI smoke project can be built or the exact blocking prerequisite has been documented.

---

# 7. Phase B — reference inventory and measurement system

## Goal

Convert “make it look like Blades” into a measurable specification.

## Tasks

For every known screen/state:

- identify canonical 6770 evidence;
- classify reference confidence;
- record source;
- determine reference resolution/aspect ratio;
- measure blade boundaries;
- measure content origin;
- measure row spacing;
- measure typography placement;
- sample colors/alpha from clean references;
- document focus states;
- document input behavior;
- document transition entry/exit;
- document whether neighboring blade edges remain visible;
- document known audio events;
- identify unknowns as `REFERENCE_GAP`.

Create a reusable state-spec template.

Recommended per-state metadata:

```text
ID:
Build:
Reference source:
Reference confidence:
Canvas:
Aspect ratio:
Safe area:
Entry state:
Initial focus:
Blade bounds:
Content bounds:
Text baselines:
Row spacing:
Colors/alpha:
Images/icons:
A action:
B action:
Other inputs:
Exit target:
Transition duration:
Transition easing:
Audio events:
Reference gaps:
Fidelity status:
```

## Gate B

No major state may progress to production XUI without a state specification.

---

# 8. Phase C — fidelity tooling

## Goal

Make visual comparison repeatable rather than subjective.

## Required tooling

Create local/developer tools capable of:

- normalizing captures to a known canvas;
- placing original/recreated captures side by side;
- creating 50/50 alpha overlays;
- creating absolute-difference images;
- optionally producing edge maps or coordinate guides;
- generating a small Markdown/JSON comparison report;
- recording open F0/F1/F2/F3 discrepancies.

Do not commit original proprietary reference captures if they are not redistributable.

The tool must accept local reference paths.

## Gate C

A simple synthetic comparison must prove the tool works before the first major screen is marked fidelity-complete.

---

# 9. Phase D — application shell

## Goal

Create a standalone XEX with deterministic lifecycle and no Aurora dependency.

## Required components

- application entry point;
- graphics/XUI initialization;
- root scene host;
- controller input service;
- scene-state manager;
- navigation history/context;
- async/background task queue appropriate to platform capabilities;
- logging/diagnostics;
- settings path abstraction;
- service abstraction;
- clean shutdown/launch handoff.

## Rules

Do not render placeholder modern menus as the production shell.

Temporary diagnostics must be clearly separated and removable.

## Gate D

The XEX must build and launch into a controlled empty/root XUI scene on target hardware or the closest verified local execution path available.

---

# 10. Phase E — canonical Blade shell

## Goal

Reproduce the defining Retail 6770 overlapping Blade structure before adding backend complexity.

## Required fidelity work

Implement and measure:

- all top-level blade boundaries present in the target state;
- active blade geometry;
- inactive neighboring blade geometry;
- metallic separators;
- blade color/surface treatment;
- background treatment;
- title/header placement;
- active menu region;
- right/secondary information area where present;
- controller legend;
- profile/status region where present;
- initial focus;
- horizontal switching;
- selected/focus visuals;
- blade slide motion;
- content transition timing.

## Critical rule

Do not proceed by creating five colored generic panels.

The geometry and rendering order must be based on measured 6770 evidence.

## Gate E

Required before moving to full content work:

- static shell comparison produced;
- no F0 shell discrepancies;
- no F1 shell discrepancies;
- blade-switch motion visually matched to reference within the best measurable tolerance;
- controller focus behavior verified.

---

# 11. Phase F — screen hierarchy recreation

## Goal

Recreate the original distinction between top-level Blade states and deeper full-screen states.

## Tasks

Implement a navigation model that supports at minimum:

```text
Top-level Blade
  -> option/action
    -> child view
       -> deeper view/dialog
       -> return restoring exact previous context
```

Some child views must be capable of removing visible neighboring blade indicators when the original does so.

## Required tests

- return restores previous blade;
- return restores previous list focus where original behavior supports it;
- full-screen child does not inherit top-level layout accidentally;
- transitions do not flash default/empty scenes;
- input is locked/debounced correctly during transition.

---

# 12. Phase G — Games experience

## Goal

Recreate Retail 6770 Games-facing UI and connect it to real installed content without changing the presentation.

## Backend responsibilities

Create an owned library/content adapter capable of supplying appropriate fields such as:

- display title;
- TitleID where available;
- content type;
- executable/launch path;
- storage location;
- artwork/thumbnail if the canonical screen uses it;
- recent/favorite state only where a matching UI concept exists or is explicitly approved later.

## UI responsibilities

- reproduce canonical Games blade state(s);
- reproduce any canonical full-screen list/library view used in 6770;
- preserve exact focus/list behavior;
- preserve original empty/loading/error treatment when known;
- launch selected content through the standalone dashboard's launch layer.

## Do not

- import CCLOS game cards;
- add modern metadata rows that 6770 does not show;
- add a modern details page by assumption;
- keep blade edges on a full-screen state when the original removes them.

## Gate G

One real installed title must be discoverable and launchable through a fidelity-approved Games flow.

---

# 13. Phase H — Marketplace experience using ConsoleCrate backend

## Goal

Make the original-style Marketplace experience functional using the existing ConsoleCrate/CCLOS Marketplace infrastructure.

## Required adapter

Create a dedicated Marketplace adapter responsible for:

- fetching/parsing current catalog data;
- mapping categories to Blade-era presentation concepts;
- mapping title names;
- mapping TitleIDs/content identifiers;
- mapping artwork fields where the canonical UI supports them;
- mapping availability;
- mapping size;
- starting downloads through existing infrastructure;
- exposing progress/status through a model that the original-style UI can display without modern visual leakage;
- handling offline/error/cache behavior.

## Server rule

Use the established ConsoleCrate production service infrastructure already used by CCLOS. Do not introduce a second Marketplace backend for this dashboard.

## Visual rule

The backend may be modern; the Marketplace UI must still follow the Retail 6770 reference.

Do not expose:

- modern cards;
- JSON fields;
- API terminology;
- server paths;
- infrastructure labels;
- CCLOS screen chrome.

## Compatibility strategy

If modern Marketplace categories exceed what the canonical screen visibly supports:

1. preserve the canonical top-level layout;
2. map compatible content into historically appropriate categories;
3. defer unmatched category presentation until an owner-approved fidelity-safe mapping exists;
4. do not create a new top-level UI pattern on your own.

## Gate H

At least one Marketplace item must:

- render through the canonical UI contract;
- load from ConsoleCrate infrastructure;
- show the expected canonical details/state;
- enter the existing download flow;
- report status without breaking 6770 visual fidelity.

---

# 14. Phase I — Media experience

## Goal

Recreate the canonical Media blade and its reachable views before adding any broader media functionality.

## Rules

- implement only referenced 6770-visible functions in this milestone;
- use standalone service abstractions behind the UI;
- do not import the CCLOS Media Center UI;
- do not invent Plex-like views;
- preserve canonical hierarchy and menu labels/states where documented.

Modern media-service integration may be introduced only through adapters and only when it can be presented inside a canonical state without redesign.

---

# 15. Phase J — System / Settings / Storage / Network experience

## Goal

Recreate the major System-facing flows using real local platform information where available.

Potential data sources include:

- storage devices/capacity;
- network state;
- display/runtime configuration;
- dashboard settings persistence;
- profile/settings information exposed through available APIs.

## Critical visual rule

Reproduce each 6770 state independently.

Do not force System, Storage, and Network into a shared modern settings template.

Historical full-screen transitions and unique layouts must be respected.

## Gate J

At minimum, implemented settings/storage/network screens must populate real data without changing approved reference geometry.

---

# 16. Phase K — profile/gamercard presentation

## Goal

Reproduce profile-facing 6770 UI wherever platform APIs and homebrew context permit.

## Rules

- match geometry first;
- bind real profile data second;
- if a field cannot be retrieved, use a fidelity-safe empty/unavailable state based on reference evidence;
- do not replace missing fields with invented modern profile widgets.

Any limitation caused by current Xbox services/homebrew environment must be documented as `TECHNICAL_LIMITATION`, not hidden through redesign.

---

# 17. Phase L — dialogs, overlays, notifications, error states

## Goal

Avoid destroying fidelity when non-happy-path states appear.

Catalog and implement the canonical dialog families required by current flows:

- confirmation;
- cancellation;
- warning;
- error;
- progress;
- storage/network failure;
- unavailable content;
- launch failure.

Use the original visual vocabulary and controller legends where references exist.

Do not fall back to a CCLOS popup or generic debug message box in Release builds.

---

# 18. Phase M — audio fidelity layer

## Goal

Match event timing and audio character while respecting redistribution boundaries.

Tasks:

- identify canonical event triggers;
- document original event timing;
- implement event mapping;
- use developer-local original audio only for comparison if legally possessed;
- ship only audio resources that may be redistributed;
- document any unavoidable acoustic difference separately from event-timing fidelity.

The visual milestone must not be blocked solely because a distributable exact audio asset is unavailable.

---

# 19. Phase N — performance and responsiveness

## Requirements

- input must remain responsive during catalog/library operations;
- blade motion must not hitch due to network access;
- artwork decoding must not block navigation;
- filesystem scans must be incremental/backgrounded where appropriate;
- service responses should be cached where safe;
- memory use must be measured on target hardware;
- animations must preserve their reference timing under normal load.

Add profiling/logging sufficient to identify frame/input stalls without exposing diagnostics in production UI.

---

# 20. Phase O — fidelity hardening

## Goal

Perform state-by-state final comparison rather than broad subjective review.

For every major state:

1. open exact original/reference state;
2. open recreated state with equivalent content/focus;
3. capture both at matched output geometry;
4. create side-by-side image;
5. create overlay;
6. create difference visualization;
7. log F0/F1/F2/F3 discrepancies;
8. correct all F0/F1;
9. correct F2 unless technically blocked;
10. rerun comparison;
11. freeze approved visual contract.

## Required report

`docs/CHECKPOINT_STATUS.md` must contain a table of every required state and its current fidelity level.

---

# 21. Phase P — hardware validation batching

Do not require a manual console test after every tiny commit.

Recommended hardware test batches:

### Batch 1 — foundation

- standalone XEX boot;
- XUI load;
- controller input;
- logging.

### Batch 2 — Blade engine

- top-level rendering;
- blade switching;
- focus behavior;
- motion.

### Batch 3 — major UI group

- Games;
- full-screen transitions;
- Settings/System.

### Batch 4 — service group

- Marketplace catalog;
- Marketplace download;
- installed-content scanning;
- launch handoff.

### Batch 5 — fidelity release candidate

- all canonical screens;
- all transitions;
- resource usage;
- regression pass;
- prolonged navigation/service stress.

Build/compile validation should happen continuously and is not deferred to these batches.

---

# 22. Required automated/static tests

Where practical, implement tests for:

- navigation state transitions;
- back-stack behavior;
- focus restoration;
- adapter mapping;
- Marketplace parser resilience;
- settings serialization;
- library deduplication;
- launch-model validation;
- missing artwork/data handling;
- reference geometry constants;
- accidental modification of frozen screen-state specifications.

Visual tests may compare generated geometry/state snapshots even when full XUI screenshot automation is unavailable.

---

# 23. Required documentation outputs

By milestone completion, the repository must contain:

- `docs/BUILD_ENVIRONMENT.md`
- `docs/ARCHITECTURE.md`
- `docs/XUI_WORKFLOW.md`
- `docs/REFERENCE_MATRIX.md` updated with implemented states
- `docs/CHECKPOINT_STATUS.md`
- build instructions
- deployment instructions
- known limitations
- fidelity exceptions
- service adapter documentation
- release/checkpoint notes

---

# 24. Screen/state checklist

The exact set must be refined from confirmed 6770 references. Initial recreation inventory:

- [ ] startup/root entry state
- [ ] canonical signed-in/signed-out home state(s) as evidenced
- [ ] every top-level blade present in Retail 6770
- [ ] Xbox Live/online-facing blade state(s) where present
- [ ] Games blade
- [ ] Games full-screen child/list state(s)
- [ ] Marketplace blade/state(s)
- [ ] Marketplace browsing state(s)
- [ ] Marketplace detail/action state(s)
- [ ] download/progress state(s) required by implemented Marketplace flow
- [ ] Media blade
- [ ] System blade
- [ ] Settings state(s)
- [ ] Storage state(s)
- [ ] Network state(s)
- [ ] profile/gamercard state(s)
- [ ] canonical confirmation dialog(s)
- [ ] canonical error dialog(s)
- [ ] canonical loading/progress state(s)
- [ ] empty/no-content state(s)
- [ ] transition states between top-level blades
- [ ] transition states into/out of full-screen children

Do not assume this inventory is complete. Expand it only from evidence.

---

# 25. Acceptance matrix for every state

Each major state must record:

```text
[ ] 6770 reference confirmed
[ ] reference confidence recorded
[ ] canvas/aspect verified
[ ] geometry measured
[ ] blade edges/separators verified
[ ] text baseline/size verified
[ ] colors/alpha verified
[ ] images/icons verified
[ ] initial focus verified
[ ] selected state verified
[ ] disabled state verified (if applicable)
[ ] A action verified
[ ] B action verified
[ ] other controller actions verified
[ ] transition-in verified
[ ] transition-out verified
[ ] animation timing verified
[ ] audio event timing verified (if applicable)
[ ] real/dynamic data binding complete (if applicable)
[ ] backend adapter complete (if applicable)
[ ] recreated capture generated
[ ] side-by-side reviewed
[ ] overlay/diff reviewed
[ ] F0 count = 0
[ ] F1 count = 0
[ ] F2 issues resolved or documented
[ ] regression target frozen
```

---

# 26. Failure conditions

The milestone is **not complete** if any of the following is true:

- UI is recognizably “inspired by” Blades but not matched to 6770;
- top-level geometry is guessed;
- major transitions use generic slides/fades;
- screen hierarchy differs for convenience;
- CCLOS UI appears in the recreation;
- Aurora is required at runtime;
- Marketplace uses a duplicate backend;
- major screens lack references;
- major screens lack comparison captures/reports;
- open F0 fidelity discrepancies remain;
- open F1 fidelity discrepancies remain;
- build instructions rely on undocumented local magic;
- original Microsoft binaries/resources are committed as project dependencies without redistribution rights.

---

# 27. Completion criteria

Milestone 001 is complete when:

1. A clean checkout plus the documented local Xbox 360 toolchain can build the standalone project.
2. The XEX boots independently of Aurora.
3. The canonical Retail 6770 top-level Blade interface is reproduced with approved fidelity.
4. Blade switching/navigation matches the original behavior.
5. Deeper full-screen transitions match the original hierarchy.
6. Games flow can discover and launch real local content through a canonical UI.
7. Marketplace flow uses existing ConsoleCrate/CCLOS infrastructure through an adapter while preserving the canonical frontend.
8. Major System/Media/Profile states targeted by this milestone are implemented from confirmed references.
9. Major dialogs/error/loading states used by implemented flows do not break visual fidelity.
10. Fidelity comparison tooling is operational.
11. Every implemented major state has a documented comparison result.
12. No F0/F1 visual issues remain in milestone-approved states.
13. Performance on target hardware does not visibly destroy reference animation/input behavior.
14. No Aurora runtime dependency remains.
15. No unauthorized proprietary Microsoft dashboard binary/resource dependency is shipped.
16. Documentation accurately reflects actual build, tooling, reference gaps, limitations, and service mappings.

---

# 28. Codex final instruction

Do not race to feature count.

Do not reinterpret missing information.

Do not call a screen complete because it resembles Blades.

Use Retail 6770 as the visual specification, reproduce it state by state, validate it state by state, and connect modern functionality behind that contract only after the visible behavior is correct.

**The goal is a replica first and a modern functional replacement underneath it second.**
