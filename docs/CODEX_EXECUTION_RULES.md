# Codex Execution Rules — Blade-Skin-Dashboard

## Purpose

These rules prevent scope drift, screenshot-driven reimplementation, visual reinterpretation, accidental FSD/Aurora runtime dependency, and accidental coupling to CCLOS presentation code.

Codex must read this file together with `AUTHORITY_HIERARCHY.md`, `WORKING_SKIN_BASELINE.md`, and `FIDELITY_DIRECTIVE.md` before implementation changes.

---

# 1. Repository authority

Canonical repository:

`https://github.com/CGameDev/Blade-Skin-Dashboard.git`

Default branch: `main`

Do not create a second implementation repository or move the standalone dashboard implementation into the CCLOS repository.

---

# 2. Read-before-write order

At the start of every Codex session that changes UI, runtime architecture, XUI resources, or backend integration, read:

1. `README.md`
2. `docs/AUTHORITY_HIERARCHY.md`
3. `docs/WORKING_SKIN_BASELINE.md`
4. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
5. `docs/SHARED_CORE_ARCHITECTURE.md`
6. `docs/FIDELITY_DIRECTIVE.md`
7. `docs/CODEX_EXECUTION_RULES.md`
8. `docs/REFERENCE_MATRIX.md`
9. relevant checkpoint/compatibility reports

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is legacy/supplemental scope material only. Do not use it to override the authority hierarchy or restart from-scratch UI reconstruction.

---

# 3. Canonical frontend is fixed

Canonical visual/behavioral frontend:

**developer-approved `BladeDash(2005)`**

Approved package:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

When BladeDash defines a state or behavior, it wins.

Retail 2.0.6770 is supplemental historical reference only for genuine gaps not adequately defined by BladeDash.

Do not "correct" BladeDash to match Retail 6770.

---

# 4. Mandatory first implementation path

Begin with Milestone 000.

Before generating replacement UI:

- verify the approved ZIP hash;
- extract/preserve a golden copy;
- inspect the actual XDK/XUI environment;
- test the real `skin.xui`/XUR resources;
- audit previous work for reusable backend/platform code;
- map FSD host contracts;
- build the smallest standalone XEX capable of loading an existing BladeDash resource.

The first major proof is an existing BladeDash scene/resource rendering under the standalone host without FSD or Aurora.

---

# 5. XuiTool handling

Inspect the developer's actual Xbox 360 XDK/XUI environment.

Record:

- XDK root/version;
- `XuiTool.exe` path;
- Visual Studio/XDK integration;
- compiler/linker/XEX tools;
- XUI headers/libraries;
- supported XUI/XUR generation/repack workflow;
- known working local Xbox 360 build patterns.

Codex may use supported XuiTool workflows but must not invent command-line flags. Document deterministic GUI-only steps when necessary.

Do not commit proprietary XDK files.

---

# 6. Reuse-before-rebuild rule

For every required state:

1. determine whether BladeDash already defines it;
2. if yes, locate the XUI/XUR/resource and reuse it;
3. identify its FSD data/event/service contract;
4. implement the missing contract behind a compatibility facade;
5. bind to Blade adapters and standalone/shared services;
6. test under the standalone host;
7. compare to known-good BladeDash behavior;
8. rebuild only the portion proven technically unusable.

Do not require Retail 6770 evidence before reusing a BladeDash-defined state.

---

# 7. FSD compatibility matrix

Maintain `docs/FSD_COMPATIBILITY_MATRIX.md`.

For each scene/control/data source/event, record:

- BladeDash resource/scene;
- scene/control identifier;
- expected FSD contract;
- required fields/events;
- compatibility facade;
- Blade adapter;
- underlying service implementation;
- status;
- technical limitation if any.

Useful classifications:

- `PRESENTATION_ONLY`
- `FSD_HOST_CONTRACT`
- `PLATFORM_SERVICE`
- `CONSOLECRATE_REUSABLE_BACKEND`
- `BLADEDASH_DEFINED`
- `DEFERRED`
- `UNKNOWN`

Do not redesign a scene simply because its host contract is not yet implemented.

---

# 8. No implementation by imagination

Prohibited reasoning includes:

- "This probably looked like..."
- "Retail seems cleaner so I changed..."
- "A modern equivalent would be..."
- "I simplified..."
- "I replaced the skin with a closer 6770 layout..."

For BladeDash-defined presentation, use the approved implementation.

For a genuine BladeDash gap, consult the authority hierarchy and mark unresolved details explicitly.

---

# 9. Required layering

```text
BladeDash XUI/XUR UI
      |
FSD/Blade compatibility facade
      |
Blade presentation models
      |
Blade adapters
      |
Shared services / platform APIs
```

A modern service must not leak its terminology/layout into the UI.

Blade code must not directly call CCLOS screens, view models, widgets, or navigation classes.

---

# 10. Shared ConsoleCrate/CCLOS backend rule

Reuse proven backend/service logic where appropriate, including:

- library/content discovery;
- TitleID classification;
- game launching;
- Marketplace/catalog access;
- downloads;
- artwork/cache;
- Title Updates;
- storage/network helpers;
- settings/persistence;
- asynchronous/background task patterns.

Prefer neutral service interfaces such as:

- `LibraryService`
- `MarketplaceService`
- `DownloadService`
- `TitleUpdateService`
- `LaunchService`
- `StorageService`
- `NetworkService`

Do not require the CCLOS application to run.

Do not perform a large speculative shared-core refactor before Blade's standalone proof-of-architecture works.

---

# 11. Marketplace rule

Reuse the established ConsoleCrate/CCLOS Marketplace infrastructure.

Do not recreate the backend.

Use a `BladeMarketplaceAdapter` or equivalent to map backend data/actions to the existing BladeDash presentation contract.

Do not introduce CCLOS-style cards, modern download pages, badges, API terminology, server paths, or backend schemas into the Blade frontend.

---

# 12. Dynamic data vs presentation

Live data is expected. Presentation remains BladeDash.

Examples:

- installed games populate the existing game presentation;
- ConsoleCrate catalog data populates the Blade Marketplace presentation;
- profile data populates the existing profile/gamercard presentation;
- storage/network values populate existing system views.

When backend data has no place in the approved frontend, do not redesign the frontend automatically.

---

# 13. Standalone runtime rule

Produce an independent Xbox 360 dashboard XEX.

Do not require Freestyle Dash, Aurora, or CCLOS for boot, rendering, navigation, data, launching, Marketplace, settings, or system information.

Owned/linked standalone subsystems include:

- application lifecycle;
- XUI initialization/scene hosting;
- input routing;
- content discovery;
- launch operations;
- settings persistence;
- service requests;
- cache;
- filesystem/network operations;
- platform/profile/storage/system access where available.

---

# 14. Build discipline

Establish a repeatable canonical build workflow that:

- fails clearly on missing local XDK prerequisites;
- avoids user-specific committed paths;
- separates Debug/Release outputs;
- writes useful logs;
- records produced XEX/resource paths;
- excludes proprietary toolchain artifacts;
- works from a clean checkout plus the developer's installed tools and local approved BladeDash package.

---

# 15. Performance rule

Do not put network/catalog/scanning/download/filesystem work on the render/input thread.

Use background/asynchronous work for expensive operations while preserving BladeDash-defined loading/progress presentation.

Do not invent a modern loading UI because backend work is asynchronous.

---

# 16. Validation order

For BladeDash-defined states, validate in this order:

1. existing resource loads;
2. static geometry/surface treatment preserved;
3. focus states preserved;
4. controller navigation preserved;
5. transitions/animations preserved;
6. FSD host contract replaced;
7. dynamic data bound;
8. backend service connected;
9. performance pass;
10. known-good BladeDash migration comparison.

Retail 6770 comparison is supplemental only unless the state is a genuine BladeDash gap.

---

# 17. Capture/regression requirements

For important BladeDash-defined states, keep developer-local known-good captures/video where practical and compare to standalone output under equivalent conditions.

Suggested organization:

```text
FidelityCaptures/
  bladedash-original-host/
  standalone/
  comparisons/
```

When shared rendering/navigation code changes, re-check previously approved states.

---

# 18. Testing batching rule

Do not demand hardware testing after every tiny edit.

Batch target-console testing after cohesive checkpoints such as:

- existing BladeDash XUI resource on standalone host;
- main Blade shell/navigation;
- installed game list + launch;
- Marketplace/download group;
- profile/system/settings group;
- final migration regression pass.

Continue compile/static/resource validation between hardware gates.

---

# 19. Reference gaps

Use Retail 6770 only when BladeDash does not adequately define a required state/behavior.

A `REFERENCE_GAP` must not be created merely because there is no Retail 6770 screenshot for an existing BladeDash-defined state.

For unresolved gaps use:

- `BLADEDASH_GAP_RETAIL_6770`
- `REFERENCE_GAP`
- `TECHNICAL_LIMITATION`
- `OWNER_DECISION_REQUIRED`

Do not guess permanent UI solutions.

---

# 20. Documentation after each checkpoint

Record:

- BladeDash resources reused;
- FSD contracts identified/replaced;
- adapters/services connected;
- files changed;
- build status;
- console-test status;
- migration fidelity status;
- open F0/F1/F2/F3 issues;
- technical limitations;
- genuine reference gaps;
- next permitted checkpoint.

Do not leave critical decisions only in session/chat history.

---

# 21. Prohibited repository content

Do not commit:

- non-redistributable Xbox 360 XDK binaries/libraries;
- original Microsoft dashboard executables/resource packages;
- extracted Microsoft executable code;
- credentials/API secrets;
- private absolute local paths except documented placeholders;
- owner-supplied raw BladeDash package unless redistribution is intentionally approved;
- large local build outputs unless intentionally published.

---

# 22. Final rule

**Do not rebuild what already works. BladeDash(2005) is the frontend authority. Replace the FSD host underneath it, connect shared ConsoleCrate/CCLOS services through clean adapters, and use Retail 6770 only to fill genuine gaps.**
