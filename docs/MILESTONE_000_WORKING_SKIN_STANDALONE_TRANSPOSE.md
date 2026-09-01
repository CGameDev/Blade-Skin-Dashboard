# Milestone 000 — Working Blade Skin to Standalone Dashboard Transposition

## Milestone status

**Mandatory first implementation milestone.**

This milestone supersedes the previous from-scratch UI construction strategy.

Codex must complete this milestone before any new Blade UI reconstruction work.

## Objective

Use the developer-approved `BladeDash(2005)` Freestyle 3/FSD skin as the **product frontend and absolute visual/behavioral authority** for the standalone Xbox 360 **Blade Dashboard**.

Preserve its working XUI/XUR presentation and behavior wherever technically possible. Replace FSD host/runtime dependencies with newly owned standalone runtime code plus Blade-specific adapters backed by proven ConsoleCrate/CCLOS services and Xbox 360 platform APIs.

The desired result is the existing approved BladeDash implementation running on top of a new standalone dashboard host.

Retail Xbox 360 Blades build 2.0.6770 is supplemental historical reference only for states/behaviors not adequately defined by BladeDash.

---

# 0. Mandatory authority and owner decisions

Read first:

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

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is retired legacy material and must not be executed.

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

# 1. Non-negotiable rules

- BladeDash-defined presentation and behavior are authoritative.
- Do not use Retail 6770 to override a working BladeDash-defined state.
- Stop/discard incomplete from-scratch Blade UI attempts unless they contain reusable runtime/backend/platform work.
- Do not delete reusable backend/platform code merely because its old UI shell was wrong.
- Do not use generic colored Blade panels as the production base.
- Do not redraw geometry already present in the working package.
- Do not recreate existing animations/timelines from screenshots.
- Do not replace working XMA audio cues/event timing with guesses.
- Do not replace existing scene resources until proven technically incompatible with the standalone host.
- Do not require Aurora, Freestyle Dash, or CCLOS at runtime.
- Do not copy CCLOS visual components into Blade.
- Do reuse ConsoleCrate/CCLOS backend/service logic behind clean Blade adapters.
- Preserve the approved original package untouched as a golden source.
- Keep the frontend externally editable/repackable through the verified XUI/XuiTool resource workflow wherever technically possible.
- Do not leave dead FSD-era service calls in production.

---

# 2. Owner-approved product identity and deployment

Product name:

**Blade Dashboard**

Application-identifying FSD/Freestyle Dash branding may be replaced with `Blade Dashboard` without changing layout, geometry, navigation or styling.

Default deployment root:

```text
Hdd1:\Apps\BladeDashboard\
```

Deployable entrypoint:

```text
Hdd1:\Apps\BladeDashboard\default.xex
```

Blade-owned state is stored independently of CCLOS beneath the application root, conceptually:

```text
Config\
Cache\
Data\
Logs\
Skins\
```

No new CCLOS-style OOBE is to be created. First launch initializes required local state and enters the approved BladeDash presentation.

Do not automatically edit `launch.ini`; document DashLaunch setup instead unless the owner later changes this rule.

Primary v1 acceptance display mode: **16:9 HD / 720p**.

---

# 3. Phase A — source acquisition and golden copy

## Tasks

- locate the approved ZIP;
- calculate SHA-256 and verify the approved fingerprint;
- extract into `references/local/BladeDash(2005)/` without flattening paths;
- create an immutable/golden copy or verified backup;
- generate a local manifest/hash inventory;
- record extraction status;
- do not alter the approved ZIP.

## Gate A

Do not proceed if the hash differs unless the owner intentionally supplied a newer baseline.

---

# 4. Phase B — XDK/XuiTool and external-resource validation

Codex must test the real approved package, not a synthetic replacement UI.

## Tasks

- locate installed Xbox 360 XDK and `XuiTool.exe`;
- record versions/paths in `docs/BUILD_ENVIRONMENT.md`;
- open/test `skin.xui` using the verified local workflow;
- determine whether local tools can inspect/edit individual `.xur` files;
- determine supported compile/repack path from editable XUI to runtime resources;
- verify image, DDS, XMA, font, shader and mesh resource resolution;
- document any resource that fails to load;
- determine the best externally editable runtime packaging strategy.

Preferred resource strategy:

1. external editable/repackable XZP/skin package if supported cleanly;
2. otherwise external extracted resource directory;
3. embed only resources proven impossible/unsafe to load externally.

Do not invent XuiTool command-line flags.

## Gate B

Codex demonstrates that the existing presentation can be consumed and kept externally maintainable before generating replacement UI.

---

# 5. Phase C — previous-work audit and CCLOS provenance

## Previous-work audit

Keep reusable work such as:

- XEX/build foundation;
- XDK build scripts;
- HTTP/network services;
- filesystem utilities;
- launch helpers;
- ConsoleCrate adapters;
- parsing/cache logic;
- tests;
- diagnostics;
- background/performance infrastructure.

Discard/quarantine UI that competes with the approved BladeDash presentation unless it solves a proven missing state.

Create/update:

```text
docs/LEGACY_ATTEMPT_AUDIT.md
```

## Authoritative CCLOS source

Use:

```text
CGameDev/ConsoleCrateLive
branch: main
```

Before reusing/porting backend code, record the exact source commit SHA in:

```text
docs/BACKEND_PROVENANCE.md
```

Do not use backup repositories as implementation authority unless explicitly directed.

Treat the CCLOS repository as a source/reference for proven services; do not casually modify it while building Blade.

---

# 6. Phase D — BladeDash/FSD dependency and contract map

## Goal

Determine exactly what the approved frontend expects FSD to provide.

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

For every relevant `.xur`, XML config and `skin.xui` resource:

- identify scene/control IDs;
- identify expected data fields;
- identify event/button actions;
- identify transitions;
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

Do not replace a scene merely because its host contract is not yet implemented.

---

# 7. Phase E — standalone XEX proof of architecture

## Goal

Create the smallest standalone Xbox 360 application capable of initializing XUI and hosting an existing BladeDash resource.

Required owned components:

- application entry point;
- graphics/XUI initialization;
- root scene/resource loader;
- controller input routing;
- scene navigation host;
- logging;
- settings/filesystem path abstraction;
- background-task abstraction;
- clean shutdown/game-launch handoff.

Do **not** build a replacement Blade menu.

First render an existing approved BladeDash resource; then progress to `main.xur`/the main shell.

## Gate E

`default.xex` launches and renders an existing BladeDash resource without FSD or Aurora underneath it.

This is the most important early proof-of-architecture gate.

---

# 8. Phase F — FSD compatibility/presentation bridge

Allow the existing UI to request data/actions without knowing FSD has been replaced.

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

Initial targets:

- scene lifecycle;
- tab/blade navigation;
- focus events;
- menu text/state;
- system/status values;
- profile/gamercard data/placeholders;
- controller legends;
- sound/transition triggers.

## Gate F

Main Blade navigation runs on the standalone host with no FSD/Aurora dependency and without changing approved geometry/animations/behavior.

---

# 9. Phase G — owner-approved feature mapping

## General policy

If BladeDash has a frontend feature and ConsoleCrate/CCLOS Core or an owned Xbox platform service can provide real functionality, **retain the Blade feature and replace the old FSD service underneath it**.

### Required mappings

| BladeDash frontend | Required backend direction |
|---|---|
| Games / game info / controls | ConsoleCrate/CCLOS library, cache/metadata and launch services |
| Marketplace | ConsoleCrate/CCLOS Marketplace services |
| Downloads | CCLOS download/queue infrastructure and high-throughput pipeline when available |
| Title Update Manager | CCLOS Title Update service |
| Achievements | CCLOS/Xbox achievement service |
| Trainers | CCLOS trainer/runtime service |
| CopyDVD | CCLOS Disc-to-GOD service |
| Profiles/avatar | Xbox platform/profile services + reusable CCLOS logic |
| File/path manager | Standalone filesystem + reusable ConsoleCrate logic |
| Storage/system/network | Xbox platform APIs + reusable service logic |
| CoverFlow | Existing Blade presentation + library/artwork adapters |
| Saved Games | Existing Blade presentation + Xbox storage/content services where practical |

### Unsupported/obsolete services

If an original external FSD-era service is obsolete and no real replacement exists:

- do not fake a backend;
- do not redesign surrounding UI;
- preserve presentation where practical;
- use an existing Blade disabled/unavailable state when available;
- otherwise record `OWNER_DECISION_REQUIRED` before creating new visible behavior;
- never leave a dead service call.

---

# 10. Phase H — Media Center + Watch TV

## Owner decision

The existing BladeDash Media / Media Center presentation is retained and **must not be visually redesigned**.

CCLOS Watch TV/media functionality is connected underneath it.

Canonical path:

```text
Existing Blade Media Center XUI
        |
BladeMediaAdapter
        |
Shared/ported CCLOS Watch TV and media services
```

Rules:

- preserve existing Blade media scenes, geometry, list controls, transitions, fonts and navigation style;
- do not import the CCLOS Watch TV UI;
- do not replace the Blade Media Center with a modern media screen;
- Watch TV data/actions may populate/extend existing Blade media list/control patterns;
- if a visible `Watch TV` entry is needed, use the existing Blade menu/list style without new chrome/layout geometry;
- backend/playback capability may evolve independently behind the adapter.

## Gate H

At least one Watch TV/media flow works through the existing Blade Media presentation without visible CCLOS UI leakage.

---

# 11. Phase I — Marketplace, downloads and production service

Authoritative production domain:

```text
consolecratelive.online
```

Do not resurrect deprecated NAS-hosted or Cloudflare-based CCLOS infrastructure because old source contains stale endpoints.

Create a `BladeMarketplaceAdapter` and related download adapters.

Reuse proven backend logic for:

- catalog retrieval;
- artwork retrieval/cache;
- queue management;
- high-throughput download pipeline;
- segmented/single-file semantics;
- install/extract flows where applicable;
- Blade-style status/error mapping.

Visible name remains **Marketplace**.

Do not create a new ConsoleCrate top-level Blade or expose API/server terminology.

## Gate I

A Marketplace item can be displayed, selected and downloaded through the Blade presentation contract using ConsoleCrate production infrastructure.

---

# 12. Phase J — remaining host services

Continue mapping retained Blade features to real services in batches.

Candidates include:

- profiles/avatar;
- storage/system/network;
- file/path manager;
- saved games;
- HTTP/WebUI where a real standalone service is intentionally retained;
- weather only if a real replacement is available/approved;
- legacy Xlink Kai/JQE/plugin/update functions only if a real replacement is available/approved.

Do not interpret a missing obsolete service as permission to delete/redesign unrelated Blade presentation.

---

# 13. Performance

Do not put network/catalog/scanning/download/filesystem work on the render/input thread.

Use background/asynchronous architecture while preserving BladeDash loading/progress presentation.

Reuse proven ConsoleCrate/CCLOS patterns for buffered downloads, catalog/artwork processing, library scans, events and cached presentation models.

---

# 14. Testing cadence

Batch target-console testing at meaningful gates:

1. existing BladeDash resource rendered by standalone host;
2. main Blade shell/navigation;
3. installed-game list + launch;
4. Disc-to-GOD/CopyDVD path;
5. Achievements/TU/Trainers service group;
6. Marketplace catalog + downloads;
7. Media Center + Watch TV;
8. system/profile/settings group;
9. final migration regression/fidelity pass.

Continue compile/static/resource validation between hardware gates.

---

# 15. Release/redistribution boundary

Until asset redistribution is explicitly reviewed, raw BladeDash assets are developer/private-build material.

Do not automatically publish the owner-supplied ZIP, fonts, audio, textures or other third-party/historical resources whose redistribution status is not established.

Public Git may contain newly written runtime code, adapters, build scripts, documentation, manifests/hashes, compatibility/provenance records and approved redistributable resources.

---

# 16. Definition of milestone complete

Milestone 000 is complete when:

- exact approved ZIP verified/preserved;
- package proven usable in local XUI workflow;
- external/editable presentation packaging strategy documented;
- previous attempt audited;
- exact CCLOS source commit provenance recorded;
- FSD dependencies documented in a compatibility matrix;
- standalone `default.xex` loads the approved Blade presentation without FSD/Aurora;
- main Blade navigation works using supplied resources;
- at least one installed title appears and launches;
- at least one owner-approved feature is proven through a CCLOS-backed adapter (for example CopyDVD -> Disc-to-GOD, TU, Achievements or Trainers);
- ConsoleCrate Marketplace/download integration is demonstrated or exact blocker documented;
- Watch TV/media capability is demonstrated through the existing Blade Media UI or exact blocker documented;
- incorrect from-scratch UI is removed/quarantined while reusable backend work is preserved;
- migration comparison shows the new host did not visually or behaviorally reinvent BladeDash.

## Final Codex instruction

**BladeDash(2005) is the frontend authority. Preserve it. Keep every practical Blade feature by replacing its FSD backend with real ConsoleCrate/CCLOS Core or Xbox functionality. Keep the existing Blade Media Center UI intact while adding Watch TV underneath it. Use Retail 6770 only to fill genuine gaps.**
