# Codex Execution Rules — Blade-Skin-Dashboard

## Purpose

These rules prevent scope drift, screenshot-driven reimplementation, visual reinterpretation, accidental FSD/Aurora runtime dependency, dead FSD-era integrations, and accidental coupling to CCLOS presentation code.

Codex must read `AUTHORITY_HIERARCHY.md`, `OWNER_DECISIONS.md`, `WORKING_SKIN_BASELINE.md`, and `FIDELITY_DIRECTIVE.md` before implementation changes.

---

# 1. Repository authority

Canonical repository:

`https://github.com/CGameDev/Blade-Skin-Dashboard.git`

Default branch: `main`

Do not create a second implementation repository or move the standalone dashboard implementation into the CCLOS repository.

---

# 2. Read-before-write order

At the start of every Codex session that changes UI, runtime architecture, XUI resources, media behavior, or backend integration, read:

1. `README.md`
2. `AGENTS.md`
3. `docs/AUTHORITY_HIERARCHY.md`
4. `docs/OWNER_DECISIONS.md`
5. `docs/WORKING_SKIN_BASELINE.md`
6. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
7. `docs/SHARED_CORE_ARCHITECTURE.md`
8. `docs/FIDELITY_DIRECTIVE.md`
9. `docs/CODEX_EXECUTION_RULES.md`
10. `docs/REFERENCE_MATRIX.md`
11. relevant `FSD_COMPATIBILITY_MATRIX`, `BACKEND_PROVENANCE`, build and checkpoint reports

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is retired legacy material. Do not use it to restart from-scratch UI reconstruction.

---

# 3. Canonical frontend and owner scope are fixed

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

When BladeDash defines a state/behavior, it wins.

When `OWNER_DECISIONS.md` defines a scope/product choice, it wins.

Retail 2.0.6770 is supplemental historical reference only for genuine gaps not defined by BladeDash or owner decisions.

---

# 4. Mandatory first implementation path

Begin with Milestone 000.

Before generating replacement UI:

- verify approved ZIP hash;
- preserve a golden copy;
- inspect actual XDK/XUI environment;
- test real `skin.xui`/XUR resources;
- determine externally editable/repackable presentation workflow;
- audit previous work for reusable backend/platform code;
- record authoritative CCLOS source commit in `BACKEND_PROVENANCE.md` before backend reuse;
- map FSD host contracts;
- build smallest standalone `default.xex` capable of loading an existing BladeDash resource.

First proof: an existing BladeDash scene/resource renders under the standalone host without FSD or Aurora.

---

# 5. XuiTool and frontend packaging

Inspect the developer's actual Xbox 360 XDK/XUI environment.

Record actual XDK/XuiTool/compiler/linker/XEX/resource workflow details.

Preferred presentation packaging:

1. external editable/repackable XZP/skin package if verified supported;
2. otherwise external extracted resource directory;
3. embed only resources proven impossible/unsafe to externalize.

Do not invent XuiTool CLI flags.

Do not commit proprietary XDK files.

---

# 6. Reuse-before-rebuild rule

For every required state:

1. determine whether BladeDash defines it;
2. if yes, locate/reuse the XUI/XUR/resource;
3. identify FSD data/event/service contract;
4. implement missing contract behind a compatibility facade;
5. bind to Blade adapters and standalone/shared services;
6. test under standalone host;
7. compare to known-good BladeDash behavior;
8. rebuild only the portion proven technically unusable.

Do not require Retail 6770 evidence before reusing a BladeDash-defined state.

---

# 7. Feature-retention rule

Do not ask whether the following owner-approved mappings should be retained; they are already decided:

```text
Blade Games            -> CCLOS/ConsoleCrate library + launch services
Blade Marketplace      -> ConsoleCrate Marketplace
Blade Downloads        -> CCLOS queue/download pipeline
Blade Achievements     -> CCLOS/Xbox achievement service
Blade Title Updates    -> CCLOS Title Update service
Blade Trainers         -> CCLOS trainer/runtime service
Blade CopyDVD          -> CCLOS Disc-to-GOD service
Blade Media Center     -> CCLOS Watch TV/media services
```

The UI side of these mappings remains BladeDash.

For File Manager, Saved Games, Profile/Avatar, Storage/System/Network and CoverFlow, use owned Xbox platform services and reusable ConsoleCrate/CCLOS logic as documented in `OWNER_DECISIONS.md` and `REFERENCE_MATRIX.md`.

If an FSD-era external service is obsolete and no real replacement exists, do not fake it or leave a dead call. Preserve the Blade presentation and use an existing unavailable/disabled state when possible; otherwise record `OWNER_DECISION_REQUIRED`.

---

# 8. Media Center / Watch TV hard rule

The current Blade Media / Media Center UI is **frozen presentation**.

Watch TV functionality is added underneath it through a Blade media adapter.

Do not:

- import CCLOS Watch TV UI;
- replace Blade media scenes;
- introduce modern media cards/chrome;
- change Blade Media geometry, transitions, fonts or navigation style to fit backend data.

A visible `Watch TV` action may use the existing Blade menu/list control pattern only.

---

# 9. FSD compatibility matrix

Maintain `docs/FSD_COMPATIBILITY_MATRIX.md`.

For each scene/control/data source/event, record:

- BladeDash resource/scene;
- control identifier;
- expected FSD contract;
- required fields/events;
- compatibility facade;
- Blade adapter;
- underlying service;
- provenance entry;
- status/limitation.

Do not redesign a scene merely because its host contract is not yet implemented.

---

# 10. Shared ConsoleCrate/CCLOS backend rule

Authoritative backend-reference repository:

```text
CGameDev/ConsoleCrateLive
branch: main
```

Record exact source commit before reuse in `docs/BACKEND_PROVENANCE.md`.

Reuse proven backend/service logic, not CCLOS presentation code.

Prefer neutral service interfaces such as:

- `LibraryService`
- `MarketplaceService`
- `DownloadService`
- `TitleUpdateService`
- `AchievementService`
- `TrainerService`
- `DiscCopyService`
- `MediaService`
- `LaunchService`
- `StorageService`
- `NetworkService`

Do not require the CCLOS application to run.

Do not perform a large speculative shared-core refactor before Blade's standalone proof-of-architecture works.

---

# 11. Production service rule

Authoritative production domain:

```text
consolecratelive.online
```

Do not restore deprecated NAS/Cloudflare CCLOS infrastructure because old code references it.

Do not create a duplicate Blade-specific Marketplace/backend server where ConsoleCrate already supplies the capability.

Never commit credentials/secrets.

---

# 12. Dynamic data vs presentation

Live data is expected. Presentation remains BladeDash.

When backend data has no place in the approved frontend, do not redesign the frontend automatically.

The backend adapts to BladeDash.

---

# 13. Standalone runtime and storage rule

Produce independent Xbox 360 dashboard deployment:

```text
Hdd1:\Apps\BladeDashboard\default.xex
```

Blade owns local runtime state under its application root (`Config`, `Cache`, `Data`, `Logs`, `Skins` or documented technical equivalents).

Do not depend on CCLOS-local configuration/cache folders.

Do not require Freestyle Dash, Aurora or CCLOS for boot/render/navigation/data/launching/Marketplace/media/settings/system information.

Do not automatically edit `launch.ini`.

No new CCLOS-style OOBE.

---

# 14. Build discipline

Establish repeatable canonical build workflow that:

- fails clearly on missing XDK prerequisites;
- avoids user-specific committed paths;
- separates Debug/Release outputs;
- writes useful logs;
- records XEX/resource paths;
- excludes proprietary toolchain artifacts;
- works from clean checkout plus installed tools and developer-local approved BladeDash package.

---

# 15. Performance rule

Do not put network/catalog/scanning/download/filesystem/media-service work on render/input thread.

Use background/asynchronous work while preserving BladeDash-defined loading/progress presentation.

---

# 16. Validation order

For BladeDash-defined states:

1. existing resource loads;
2. geometry/surface preserved;
3. focus states preserved;
4. controller navigation preserved;
5. transitions/animations/audio preserved;
6. FSD host contract replaced;
7. dynamic data bound;
8. backend service connected;
9. performance pass;
10. known-good BladeDash migration comparison.

Primary v1 display acceptance: **16:9 HD / 720p**.

Retail 6770 comparison is supplemental only for genuine BladeDash gaps.

---

# 17. Testing batching rule

Batch target-console testing after cohesive checkpoints:

- existing BladeDash resource on standalone host;
- main Blade shell/navigation;
- installed game list + launch;
- CopyDVD/Disc-to-GOD;
- Achievements/TU/Trainers;
- Marketplace/downloads;
- Media Center/Watch TV;
- profile/system/settings;
- final migration regression pass.

Continue compile/static/resource validation between hardware gates.

---

# 18. Backend provenance

Maintain `docs/BACKEND_PROVENANCE.md` for every reused CCLOS subsystem.

Do not copy backend code from an unrecorded branch/backup/snapshot.

---

# 19. Redistribution boundary

Until explicitly reviewed, raw BladeDash assets are developer/private-build material.

Do not publish/package owner-supplied raw ZIP, fonts, audio, textures or other third-party/historical assets whose redistribution status is not established.

Public Git may contain newly written code, adapters, docs, hashes/manifests, provenance/compatibility records and approved redistributable resources.

---

# 20. Documentation after each checkpoint

Record:

- BladeDash resources reused;
- FSD contracts replaced;
- adapters/services connected;
- exact CCLOS source commit/provenance;
- files changed;
- build/console-test status;
- migration fidelity status;
- open issues/technical limitations;
- genuine reference gaps;
- next permitted checkpoint.

Do not leave critical decisions only in chat history.

---

# 21. Final rule

**Do not rebuild what already works. BladeDash(2005) is the frontend authority; OWNER_DECISIONS.md fixes product scope. Replace FSD services with real ConsoleCrate/CCLOS Core or Xbox functionality, keep the Blade Media Center UI intact while adding Watch TV underneath it, and use Retail 6770 only for genuine gaps.**
