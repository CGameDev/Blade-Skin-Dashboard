# Milestone 000 — Working Blade Skin to Standalone Dashboard Transposition

## Milestone status

**Mandatory first implementation milestone.**

This milestone supersedes the previous from-scratch UI construction strategy.

Codex must complete this milestone before any new Blade UI reconstruction work.

## Objective

Use the developer-approved `BladeDash(2005)` Freestyle 3/FSD skin as the **product frontend and absolute visual/behavioral authority** for the standalone Xbox 360 Blade dashboard.

Preserve its working XUI/XUR presentation and behavior wherever technically possible. Replace the FSD host/runtime dependencies with newly owned standalone runtime code plus Blade-specific adapters backed by proven ConsoleCrate/CCLOS services.

The desired result is the existing approved BladeDash implementation running on top of a new standalone dashboard host.

Retail Xbox 360 Blades build 2.0.6770 is supplemental historical reference only for states/behaviors not adequately defined by BladeDash.

---

# 0. Mandatory authority and source baseline

Read first:

1. `README.md`
2. `docs/AUTHORITY_HIERARCHY.md`
3. `docs/WORKING_SKIN_BASELINE.md`
4. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
5. `docs/SHARED_CORE_ARCHITECTURE.md`
6. `docs/FIDELITY_DIRECTIVE.md`
7. `docs/CODEX_EXECUTION_RULES.md`
8. `docs/REFERENCE_MATRIX.md`

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is legacy/supplemental scope material only and does not override this milestone.

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

- BladeDash-defined presentation and behavior are authoritative.
- Do not use Retail 6770 to override a working BladeDash-defined state.
- Stop/discard incomplete from-scratch Blade UI attempts unless they contain reusable runtime/backend/platform work.
- Do not delete reusable backend/platform code merely because its old UI shell was wrong.
- Do not use generic colored Blade panels as the production base.
- Do not redraw geometry already present in the working package.
- Do not recreate existing animations/timelines from screenshots.
- Do not replace working XMA audio cues or event timing with guesses.
- Do not replace existing scene resources until proven technically incompatible with the standalone host.
- Do not require Aurora, Freestyle Dash, or CCLOS at runtime.
- Do not copy CCLOS visual components into Blade.
- Do reuse ConsoleCrate/CCLOS backend/service logic behind clean Blade adapters.
- Preserve the approved original package untouched as a golden source.

---

# 2. Phase A — source acquisition and golden copy

## Tasks

- locate the ZIP in the developer-local repository workspace;
- calculate SHA-256 and compare to the approved fingerprint;
- extract into `references/local/BladeDash(2005)/` without flattening paths;
- create an immutable/golden copy or verified backup;
- generate a local manifest/hash inventory for important resources;
- record extraction status in `docs/CHECKPOINT_STATUS.md`;
- do not alter the approved ZIP.

## Gate A

Do not proceed if the hash differs unless the project owner intentionally supplied a newer baseline.

---

# 3. Phase B — XDK/XuiTool validation using the actual skin

Codex must test the real approved package, not a synthetic replacement UI.

## Tasks

- locate installed Xbox 360 XDK and `XuiTool.exe`;
- record versions/paths in `docs/BUILD_ENVIRONMENT.md`;
- open/test `skin.xui` using the verified local workflow;
- determine whether local tools can inspect/edit individual `.xur` files;
- determine supported compile/repack path from editable XUI to runtime resources;
- verify image, DDS, XMA, font, shader, and mesh resource resolution;
- document any resource that fails to load;
- never invent command-line flags.

## Gate B

Codex must demonstrate that it can open/edit or otherwise consume the existing approved presentation resources before generating replacement UI.

---

# 4. Phase C — BladeDash/FSD dependency and contract map

## Goal

Determine exactly what the approved frontend expects Freestyle Dash to provide.

Starting host concepts include:

- `CoverFlow`
- `VideoManager`
- `AchievementManager`
- `HTTPServer`
- `ScnGameView`
- `GamesList`
- `FilesList`
- `ActiveTUList`
- source/destination file lists
- `PathList`
- `ScnProfile`
- `ScnPopup`
- `ScnSysInfo`
- `ScnTabPresenter`
- `ScnTeamFSD`
- `ScnWeather`

## Tasks

For every relevant `.xur`, XML config, and `skin.xui` resource:

- identify scene/control IDs;
- identify expected data fields;
- identify event/button actions;
- identify scene transitions;
- identify list/data-source population points;
- identify service calls implied by the scene;
- identify presentation-only resources;
- identify FSD-runtime-coupled resources;
- classify dependencies.

Create/update:

```text
docs/FSD_COMPATIBILITY_MATRIX.md
```

Recommended classifications:

- `BLADEDASH_DEFINED`
- `PRESENTATION_ONLY`
- `FSD_HOST_CONTRACT`
- `PLATFORM_SERVICE`
- `CONSOLECRATE_REUSABLE_BACKEND`
- `DEFERRED`
- `UNKNOWN`

## Gate C

Do not replace a scene merely because its host contract is not yet implemented. Record and satisfy the contract where practical.

---

# 5. Phase D — standalone XEX host foundation

## Goal

Create the smallest standalone Xbox 360 application capable of initializing XUI and hosting an existing BladeDash resource.

## Required owned components

- application entry point;
- graphics/XUI initialization;
- root scene/resource loader;
- controller input routing;
- scene navigation host;
- logging;
- settings/filesystem path abstraction;
- background-task abstraction appropriate for Xbox 360;
- clean shutdown and game-launch handoff.

## First rendering target

Do **not** build a replacement Blade menu.

Render an existing resource from the approved package first, then progress to `main.xur`/the main shell.

## Gate D

A standalone XEX launches and renders an existing BladeDash resource without FSD or Aurora running underneath it.

This is the most important early proof-of-architecture gate.

---

# 6. Phase E — FSD compatibility/presentation bridge

## Goal

Allow the existing approved UI to request data/actions without knowing FSD has been replaced.

```text
Existing BladeDash scene
      |
Blade/FSD compatibility facade
      |
Blade presentation model
      |
Blade adapter
      |
Standalone/shared service
```

Preserve scene-facing names/semantics where practical rather than rewriting scenes to CCLOS terminology.

## Initial bridge targets

- scene lifecycle;
- tab/blade navigation;
- focus events;
- menu text/state;
- system/status values;
- profile/gamercard data/placeholders;
- controller legends;
- sound/transition triggers.

## Gate E

Main Blade navigation runs on the standalone host with no FSD/Aurora dependency and without changing the approved geometry/animations/behavior.

---

# 7. Phase F — installed games and launch

## Goal

Connect the approved Games UI to the standalone library/content layer.

Reuse/adapt proven ConsoleCrate/CCLOS backend code for:

- scan paths;
- TitleID/content classification;
- installed game discovery;
- artwork/cache lookup where compatible;
- launch-path resolution;
- title launch handoff.

Map data to the fields expected by the BladeDash game presentation. Do not import CCLOS game-card UI.

## Gate F

At least one real installed title appears in the existing BladeDash presentation and launches successfully.

---

# 8. Phase G — ConsoleCrate Marketplace integration

## Goal

Connect ConsoleCrate services behind the approved Blade presentation.

Create a `BladeMarketplaceAdapter` or equivalent.

Reuse proven backend logic for:

- production server/API access;
- catalog retrieval;
- artwork retrieval/cache;
- download queue;
- high-throughput download pipeline where available;
- segmented/single-file semantics;
- install/extract flow where applicable;
- status/error reporting.

Do not change the Blade frontend to resemble CCLOS.

If a required Marketplace state is genuinely absent from BladeDash, document the gap and consult Retail 6770 only for that missing state.

## Gate G

A Marketplace item can be displayed, selected, and downloaded from ConsoleCrate infrastructure through the Blade presentation contract.

---

# 9. Phase H — remaining host services

Implement in batches:

- achievements;
- profile/gamercard;
- storage/system info;
- file/path manager;
- Title Updates;
- saved games;
- media/video/music retained by scope;
- weather if retained/functional;
- trainer scene if retained;
- HTTP/WebUI if intentionally retained;
- updater/settings flows.

For each service, retain the existing scene when technically usable and satisfy its host contract.

Only create replacement presentation for a documented BladeDash gap or technical incompatibility.

---

# 10. Reuse of previous from-scratch work

Audit existing attempts before deletion.

Keep reusable work such as:

- XEX project/build foundation;
- XDK discovery/build scripts;
- HTTP/client services;
- filesystem utilities;
- launch helpers;
- ConsoleCrate adapters;
- parsing/cache logic;
- tests;
- diagnostics;
- performance/background-task infrastructure.

Discard/quarantine UI that competes with the approved BladeDash presentation unless it solves a proven missing state.

Document in:

```text
docs/LEGACY_ATTEMPT_AUDIT.md
```

---

# 11. Fidelity validation

For BladeDash-defined states, the primary migration comparison is:

```text
Developer-tested BladeDash(2005) under its known-good host
                         vs
Standalone BladeDashboard.xex using the migrated presentation
```

The standalone host must not alter:

- geometry;
- colors/effects;
- typography placement;
- animations;
- focus behavior;
- navigation;
- transition timing;
- audio-event timing;
- visible menu hierarchy except intentional dynamic data.

Retail 6770 is supplemental only for genuine BladeDash gaps and cannot overrule an approved BladeDash-defined state.

---

# 12. Performance

Do not put network/catalog/filesystem/download work on the render/input thread.

Use background/asynchronous architecture while preserving BladeDash loading/progress presentation.

Reuse proven ConsoleCrate/CCLOS patterns for buffered downloads, catalog/artwork processing, library scans, events, and cached presentation models.

---

# 13. Testing cadence

Batch target-console testing at meaningful gates:

1. existing BladeDash resource rendered by standalone host;
2. main Blade shell/navigation;
3. installed-game list + launch;
4. Marketplace catalog + download;
5. system/profile/settings service group;
6. final migration regression/fidelity pass.

Continue compile/static/resource validation between hardware gates.

---

# 14. Definition of milestone complete

Milestone 000 is complete when:

- exact approved ZIP verified/preserved;
- package proven usable in local XUI workflow;
- FSD dependencies documented in a compatibility matrix;
- standalone XEX loads the approved Blade presentation without FSD/Aurora;
- main Blade navigation works using supplied resources;
- at least one installed title is populated and launchable;
- ConsoleCrate backend integration is demonstrated through Blade presentation or exact blocker documented;
- incorrect from-scratch UI is removed/quarantined while reusable backend work is preserved;
- migration comparison shows the new host did not visually or behaviorally reinvent BladeDash.

## Final Codex instruction

**BladeDash(2005) is the frontend authority. Do not rebuild it. Transpose it onto a standalone host, replace the missing FSD runtime with clean adapters/services, and use Retail 6770 only to fill genuine gaps.**
