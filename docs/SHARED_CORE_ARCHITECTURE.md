# Shared Core Architecture — Blade Frontend + ConsoleCrate Services

## Status

**Mandatory architectural contract for Blade Dashboard.**

This document defines how the approved BladeDash frontend reuses proven CCLOS/ConsoleCrate infrastructure without coupling Blade to the CCLOS UI/application.

Explicit product mappings are defined by `OWNER_DECISIONS.md`.

## Core design

```text
Approved BladeDash(2005) XUI/XUR frontend
                |
        FSD compatibility layer
                |
      Blade presentation models
                |
          Blade adapters
                |
     Shared ConsoleCrate services
                |
       Xbox 360 platform APIs
                |
Hdd1:\Apps\BladeDashboard\default.xex
```

Blade depends on reusable services/platform abstractions, **not CCLOS screens, view models, widgets, navigation classes, local installation state, or the CCLOS application runtime**.

Guiding principle:

**BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

---

# 1. Blade presentation layer

Use the supplied working resources wherever technically possible:

- `skin.xui`;
- existing `.xur` scenes;
- geometry;
- timelines/animations;
- focus/navigation presentation;
- textures/DDS;
- XMA audio;
- fonts;
- meshes/shaders;
- dialogs/loading presentation.

Do not redraw these merely to simplify backend integration.

Keep the presentation externally editable/repackable through the verified XUI/XuiTool workflow whenever technically possible.

---

# 2. FSD compatibility layer

The working skin expects FSD-facing objects/events/data sources/callbacks/commands.

Map/document those contracts instead of rewriting corresponding UI.

Examples:

- `GamesList`;
- `AchievementManager`;
- `ActiveTUList`;
- profile/gamercard data;
- system information;
- file/path lists;
- CoverFlow;
- popup/dialog services;
- media services;
- HTTP/server state where retained.

Where practical retain the semantic contract expected by the skin and provide a new compatible implementation behind it.

---

# 3. Blade adapters

Preferred pattern:

```text
Blade XUI contract
      |
Blade-specific adapter
      |
shared service interface
```

Owner-approved examples:

```text
GamesList
  -> BladeGameLibraryAdapter
  -> LibraryService

Blade game actions
  -> BladeLaunchAdapter
  -> LaunchService

TitleUpdateManager
  -> BladeTitleUpdateAdapter
  -> TitleUpdateService

Achievements
  -> BladeAchievementAdapter
  -> AchievementService

Trainers
  -> BladeTrainerAdapter
  -> TrainerService

CopyDVD
  -> BladeDiscCopyAdapter
  -> DiscCopyService (CCLOS Disc-to-GOD)

Blade Marketplace
  -> BladeMarketplaceAdapter
  -> MarketplaceService

Blade download state
  -> BladeDownloadAdapter
  -> DownloadService

Blade Media Center
  -> BladeMediaAdapter
  -> MediaService / CCLOS Watch TV capability
```

The adapter translates service/domain data into the exact fields/states expected by BladeDash.

---

# 4. Required reusable service surface

Prefer/derive neutral service interfaces such as:

- `LibraryService`
- `LaunchService`
- `MarketplaceService`
- `DownloadService`
- `TitleUpdateService`
- `AchievementService`
- `TrainerService`
- `DiscCopyService`
- `MediaService`
- `ProfileService`
- `StorageService`
- `NetworkService`
- `FileSystemService`
- `SettingsService`
- `CacheService`
- `MetadataService`
- `DiagnosticsService`

Names may differ in implementation, but boundaries must remain presentation-neutral.

---

# 5. Feature retention rule

When BladeDash has the frontend and a real standalone service can supply the function, **retain the Blade feature**.

Do not remove it because FSD used to own the backend.

Explicit retained mappings include:

- CopyDVD -> CCLOS Disc-to-GOD;
- Achievements -> CCLOS/Xbox achievements;
- Title Updates -> CCLOS TU handling;
- Trainers -> CCLOS trainer/runtime;
- Marketplace -> ConsoleCrate Marketplace;
- Downloads -> CCLOS download/queue/high-throughput pipeline;
- Media Center -> CCLOS Watch TV/media capability.

Other Blade features should use reusable CCLOS or Xbox platform services where technically practical.

For obsolete external services with no real replacement, do not fake functionality or leave dead calls. Preserve UI and use an existing unavailable state, or record `OWNER_DECISION_REQUIRED`.

---

# 6. Media Center hard boundary

The existing Blade Media / Media Center presentation is frozen.

```text
Existing Blade Media XUI
        |
BladeMediaAdapter
        |
MediaService
        |
CCLOS Watch TV/media backend logic
```

Do not import the CCLOS Watch TV UI.

Do not change Blade media geometry, scene chrome, fonts, transitions or navigation model to fit the backend.

A Watch TV menu/list action may be inserted only through existing Blade list/control patterns.

---

# 7. Explicitly prohibited coupling

Forbidden equivalents:

```cpp
CCLOSMarketplaceScreen->LoadGames();
CCLOSDownloadsPage->StartDownload();
CCLOSGameCard->Bind(...);
CCLOSNavigationManager->Open(...);
CCLOSWatchTVScreen->Open(...);
```

Preferred service-oriented equivalents:

```cpp
MarketplaceService->GetCatalog();
DownloadService->StartDownload();
LibraryService->EnumerateGames();
TitleUpdateService->CheckUpdates();
LaunchService->LaunchTitle();
DiscCopyService->StartDiscToGod();
MediaService->OpenStream(...);
```

Blade presentation consumes those services through Blade-specific adapters.

---

# 8. CCLOS source and provenance

Authoritative source:

```text
CGameDev/ConsoleCrateLive
branch: main
```

Before backend reuse, record exact source commit in `BACKEND_PROVENANCE.md`.

Do not use backup repositories as authority without owner direction.

Do not casually modify CCLOS while building Blade.

---

# 9. Production infrastructure

Authoritative production service:

```text
consolecratelive.online
```

Do not revive deprecated NAS/Cloudflare CCLOS infrastructure because stale reused code references it.

Do not duplicate an existing ConsoleCrate backend for Blade.

---

# 10. Standalone independence

`BladeDashboard/default.xex` must:

- launch independently;
- initialize its own XUI/runtime host;
- own navigation lifecycle;
- own presentation state;
- work without Aurora/FSD/CCLOS running;
- not require CCLOS UI binaries/resources;
- own local Config/Cache/Data/Logs/Skins state;
- use shared/backend code only through owned libraries/source modules/service interfaces/reusable extracted components.

---

# 11. Shared-core evolution

Codex may initially port/adapt proven CCLOS service code to establish functionality.

When code is clearly presentation-neutral, progressively extract it into a neutral reusable core (`ConsoleCrateCore`, `CCLCore`, or equivalent).

Desired long-term model:

```text
                 ConsoleCrateCore
                 /              \
              CCLOS            Blade
          presentation      presentation
```

Do not perform a large speculative refactor before the first standalone Blade proof succeeds.

---

# 12. First architectural proof

Before broad backend integration, prove:

1. standalone `default.xex` initializes XUI;
2. existing BladeDash scene/resource renders without FSD/Aurora;
3. navigation/input is owned by standalone host;
4. one FSD-facing contract is replaced by a facade/adapter backed by a real service;
5. external/editable frontend packaging strategy is documented.

---

# 13. Preferred integration order

After rendering proof:

1. main Blade shell/navigation;
2. installed game/content list;
3. launch service;
4. CopyDVD -> Disc-to-GOD;
5. Achievements/Title Updates/Trainers;
6. Marketplace + downloads;
7. Media Center + Watch TV;
8. profile/system/storage/network/filesystem;
9. remaining FSD-specific contracts;
10. performance/regression pass.

## Final rule

**Reuse the CCLOS/ConsoleCrate brains, not the CCLOS face. Preserve every practical Blade feature, including its existing Media Center presentation, and replace FSD services underneath with real standalone services.**
