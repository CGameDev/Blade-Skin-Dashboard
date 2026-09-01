# Milestone 000 — Working Blade Skin to Standalone Dashboard Transposition

## Milestone status

**Mandatory first implementation milestone.**

This milestone supersedes the previous from-scratch UI construction strategy.

Codex must complete this milestone before continuing any screenshot-driven Blade recreation work.

## Objective

Use the developer-verified `BladeDash(2005)` Freestyle 3/FSD skin package as the starting implementation for the standalone Xbox 360 Blade dashboard.

Preserve the working XUI/XUR presentation wherever possible and replace the FSD runtime dependencies with newly owned standalone runtime code plus Blade-specific adapters backed by proven CCLOS/ConsoleCrate services.

The desired result is not a new Blade recreation. It is the existing working Blade implementation running on top of a new standalone dashboard host.

---

# 0. Mandatory source baseline

Read first:

1. `README.md`
2. `docs/WORKING_SKIN_BASELINE.md`
3. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
4. `docs/FIDELITY_DIRECTIVE.md`
5. `docs/CODEX_EXECUTION_RULES.md`
6. `docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md`
7. `docs/REFERENCE_MATRIX.md`

Where implementation strategy conflicts, `WORKING_SKIN_BASELINE.md` and this milestone take precedence.

Expected local seed:

```text
references/local/BladeDash(2005).zip
```

Expected SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

Never silently substitute another skin/package.

---

# 1. Hard rules

- Stop and discard incomplete from-scratch Blade UI attempts unless they contain standalone runtime/backend code that can be reused safely.
- Do not delete reusable backend/platform work merely because its UI shell was wrong.
- Do not use generic colored Blade panels as the new production base.
- Do not redraw geometry already present in the working package.
- Do not recreate existing animations/timelines from screenshots.
- Do not replace working XMA audio cues with guesses.
- Do not replace existing scene resources until they are proven technically incompatible with the standalone host.
- Do not require Aurora or Freestyle Dash at runtime.
- Do not copy CCLOS visual components into the Blade UI.
- Do use CCLOS backend/service logic where it can provide the required data or operation behind an adapter.
- Preserve the original working package untouched as a golden source.

---

# 2. Phase A — source acquisition and golden copy

## Tasks

- locate the ZIP in the developer-local repository workspace;
- calculate SHA-256 and compare to the approved fingerprint;
- extract into `references/local/BladeDash(2005)/` without flattening paths;
- make a second immutable/golden copy or verified backup;
- generate a local file manifest with size/hash for important resources;
- record extraction status in `docs/CHECKPOINT_STATUS.md`;
- do not alter the approved ZIP.

## Gate A

Do not proceed if the hash differs unless the project owner intentionally supplied a newer baseline.

---

# 3. Phase B — XDK/XuiTool validation using the actual skin

The old workflow asked Codex to discover XUI tooling and then build a synthetic UI. That is no longer sufficient.

Codex must test the real working package.

## Tasks

- locate the installed Xbox 360 XDK and `XuiTool.exe`;
- record versions and actual paths in `docs/BUILD_ENVIRONMENT.md`;
- open/test `skin.xui` using the verified local XUI workflow;
- determine whether local tools can directly inspect/edit individual `.xur` files;
- determine the supported compile/repack path from editable XUI to runtime XUR/resources;
- verify image, DDS, XMA, font, shader and mesh resource resolution;
- document any resource that fails to load;
- never invent command-line flags.

## Gate B

Codex must demonstrate that it can open/edit or otherwise consume the existing presentation resources before generating replacement UI.

---

# 4. Phase C — dependency and contract map

## Goal

Determine exactly what the working skin expects Freestyle Dash to provide.

## Starting evidence

The supplied `skin.xml`/`skin.extract` expose host concepts such as:

- CoverFlow;
- VideoManager;
- AchievementManager;
- HTTPServer;
- ScnGameView;
- GamesList;
- FilesList;
- ActiveTUList;
- source/destination file lists;
- PathList;
- ScnProfile;
- ScnPopup;
- ScnSysInfo;
- ScnTabPresenter;
- ScnTeamFSD;
- ScnWeather.

## Tasks

For every `.xur`, XML config and relevant `skin.xui` resource:

- identify scene/control IDs;
- identify expected data fields;
- identify event/button actions;
- identify scene transitions;
- identify list/data-source population points;
- identify service calls implied by the scene;
- identify resources that are presentation-only;
- identify resources that are FSD-runtime coupled;
- classify each dependency as `PRESENTATION_ONLY`, `FSD_HOST_CONTRACT`, `PLATFORM_SERVICE`, `CCLOS_REUSABLE_BACKEND`, `DEFERRED`, or `UNKNOWN`.

Create:

```text
docs/FSD_COMPATIBILITY_MATRIX.md
```

## Gate C

Do not replace a scene merely because its host contract is not yet implemented. Record the contract and satisfy it where practical.

---

# 5. Phase D — standalone XEX host foundation

## Goal

Create the smallest standalone Xbox 360 application capable of initializing XUI and hosting an existing Blade resource.

## Required owned components

- application entry point;
- graphics/XUI initialization;
- root scene/resource loader;
- controller input routing;
- scene navigation host;
- logging;
- settings/filesystem path abstraction;
- async/background task abstraction appropriate for Xbox 360;
- clean shutdown and game launch handoff.

## First boot target

Do **not** build a replacement Blade menu.

The first rendering target should be an existing resource from the supplied package, preferably the simplest useful existing scene/visual that proves the package can be consumed by the new host.

Then progress to `main.xur`/the canonical shell.

## Gate D

A standalone XEX must launch and render an existing resource from `BladeDash(2005)` without FSD or Aurora running underneath it.

This is the most important early proof-of-concept gate.

---

# 6. Phase E — FSD compatibility/presentation bridge

## Goal

Implement a narrow bridge that lets the old working UI ask for data/actions without knowing that FSD has been replaced.

Suggested architecture:

```text
Existing Blade scene
      |
Blade/FSD compatibility facade
      |
Blade presentation model
      |
Blade adapter
      |
Owned standalone service or reused CCLOS backend
```

Prefer preserving the scene-facing names/semantics where practical rather than rewriting every scene to new CCLOS terminology.

## Initial bridge targets

Prioritize what is required to make the main Blade shell behave correctly:

- scene lifecycle;
- tab/blade navigation;
- focus events;
- menu text/state;
- system/status values;
- profile/gamercard placeholders or real data where immediately available;
- controller legends;
- sound/transition triggers.

## Gate E

Main Blade navigation runs on the standalone host with no FSD/Aurora dependency and without replacing the working Blade geometry/animations.

---

# 7. Phase F — installed games and launch

## Goal

Connect the working Games UI to the standalone content/library layer.

Reuse/adapt proven CCLOS backend code for:

- scan paths;
- TitleID/content classification;
- installed game discovery;
- artwork/cache lookup where compatible;
- launch path resolution;
- title launch handoff.

Map the data to the fields expected by the working FSD-style game list instead of importing CCLOS game-card UI.

## Gate F

At least one real installed title appears in the existing Blade game presentation and launches successfully.

---

# 8. Phase G — ConsoleCrate Marketplace integration

## Goal

Connect ConsoleCrate services behind the existing Blade presentation.

Build a `BladeMarketplaceAdapter` or equivalent that maps the existing server/catalog/download infrastructure to the old presentation contract.

Reuse proven CCLOS logic for:

- production server/API access;
- catalog retrieval;
- artwork retrieval/cache;
- download queue;
- high-throughput download pipeline when available;
- segmented/single-file download semantics;
- install/extract flow where applicable;
- status/error reporting.

Do not change the Blade UI to resemble CCLOS.

## Gate G

A Marketplace item can be displayed, selected and downloaded from ConsoleCrate infrastructure through the Blade presentation contract.

---

# 9. Phase H — remaining host services

Implement in batches rather than forcing hardware testing after every small edit.

Candidates:

- achievements;
- profile/gamercard;
- storage/system info;
- file manager/path manager;
- Title Updates;
- saved games;
- media/video/music functions retained by project scope;
- weather only if still desired/functional;
- trainer scene integration only if part of the final standalone scope;
- HTTP/WebUI only if intentionally retained;
- update/settings flows.

For each service, first determine whether the existing scene is worth retaining. If yes, satisfy its host contract. If not, document why before creating replacement UI.

---

# 10. Reuse of previous from-scratch work

Codex must audit any existing implementation attempts before deletion.

Keep work that is independent of the incorrect recreated UI, such as:

- XEX project/build foundation;
- XDK discovery/build scripts;
- HTTP/client services;
- filesystem utilities;
- launch helpers;
- ConsoleCrate adapters;
- parsing/cache logic;
- tests;
- diagnostics;
- performance/background task infrastructure.

Discard or quarantine UI work that competes with the approved `BladeDash(2005)` presentation unless it solves a proven missing state.

Document the audit in:

```text
docs/LEGACY_ATTEMPT_AUDIT.md
```

---

# 11. Fidelity validation

The working package is the implementation seed, not permission to stop validating fidelity.

Use three-way comparison where helpful:

```text
Retail 6770 historical reference
            vs
Developer-tested BladeDash(2005) running under FSD
            vs
Standalone BladeDashboard.xex using the same presentation resources
```

The primary migration fidelity requirement is that the standalone host must not alter the approved skin's:

- geometry;
- colors;
- typography placement;
- animations;
- focus behavior;
- transition timing;
- audio event timing;
- visible menu hierarchy except where intentionally connected to live data.

---

# 12. Performance

Do not put network/catalog/filesystem work on the render/input thread.

The UI should remain as responsive as the known-good working skin.

Use CCLOS backend architecture ideas where helpful:

- dedicated/background network work;
- buffered downloads;
- asynchronous catalog/artwork processing;
- batched filesystem scans;
- event-driven UI updates;
- cached presentation models.

Preserve the Blade visual loading states while the new backend works asynchronously.

---

# 13. Testing cadence

Batch target-console testing at meaningful gates:

1. existing XUI resource rendered by standalone host;
2. main Blade shell/navigation working;
3. installed-game list + launch;
4. Marketplace catalog + download;
5. system/profile/settings service group;
6. full regression/fidelity pass.

Continue compile/static/resource validation between hardware gates.

---

# 14. Definition of milestone complete

Milestone 000 is complete when:

- the exact approved ZIP has been verified and preserved;
- the package is proven usable in the developer's XUI workflow;
- FSD dependencies have a documented compatibility matrix;
- the standalone XEX can load the approved Blade presentation without FSD/Aurora;
- main Blade navigation works using the supplied UI resources;
- at least one real installed title is populated and launchable;
- ConsoleCrate backend integration is demonstrated through the Blade presentation path or its exact next blocker is documented;
- incorrect from-scratch UI attempts are removed/quarantined while reusable backend work is preserved;
- fidelity comparison shows the host migration did not visually reinvent the dashboard.

## Final Codex instruction

**Do not rebuild what already works. Transpose the working Blade skin onto a new standalone host, then use CCLOS/ConsoleCrate backend services to replace the missing Freestyle Dash runtime behind it.**
