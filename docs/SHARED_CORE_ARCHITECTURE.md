# Shared Core Architecture — Blade Frontend + ConsoleCrate Services

## Status

**Mandatory architectural contract for the standalone Blade dashboard.**

This document defines how the Blade frontend may reuse proven CCLOS/ConsoleCrate infrastructure without coupling the Blade product to the CCLOS UI/application.

## Core design

The project SHALL use the approved `BladeDash(2005)` XUI/XUR implementation as the presentation layer and reuse proven CCLOS/ConsoleCrate backend/service logic behind compatibility facades and Blade-specific adapters.

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
        BladeDashboard.xex
```

The important boundary is that Blade depends on reusable services and platform abstractions, **not on CCLOS screens, view models, widgets, navigation classes, or the CCLOS application runtime**.

## Design principle

**BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

The same backend capability may support multiple frontends:

```text
                 Shared ConsoleCrate Core
                 /                      \
         CCLOS presentation        Blade presentation
```

A service improvement should be reusable by both products whenever technically appropriate without forcing either frontend to adopt the other's UI or navigation model.

## Required layering

### 1. Blade presentation

Use the supplied working resources wherever technically possible:

- `skin.xui`;
- existing `.xur` scenes;
- Blade geometry;
- timelines and animations;
- focus/navigation presentation;
- textures and DDS resources;
- XMA audio cues;
- fonts;
- meshes and shaders;
- dialogs and loading presentation.

Do not redraw these merely to make backend integration easier.

### 2. FSD compatibility layer

The working skin was authored for Freestyle 3/FSD and may expect host-facing objects, events, data sources, callbacks, scene factories, or commands.

Codex SHALL map and document those contracts instead of rewriting the corresponding UI.

Examples may include concepts such as:

- `GamesList`;
- `AchievementManager`;
- `ActiveTUList` / Title Update manager;
- profile/gamercard data;
- system information;
- path/file lists;
- CoverFlow;
- HTTP/server state;
- popup/dialog services;
- media/weather/avatar data where present.

Where practical, retain the semantic contract expected by the skin and provide a newly written compatible implementation behind it.

### 3. Blade adapters

Blade adapters translate between the working skin's presentation contract and shared backend services.

Preferred pattern:

```text
Blade XUI contract
      |
Blade-specific adapter
      |
shared service interface
```

Examples:

```text
GamesList
  -> BladeGameLibraryAdapter
  -> LibraryService

TitleUpdateManager
  -> BladeTitleUpdateAdapter
  -> TitleUpdateService

Blade Marketplace scene
  -> BladeMarketplaceAdapter
  -> MarketplaceService

Blade download state
  -> BladeDownloadAdapter
  -> DownloadService
```

The adapter is responsible for translating service/domain data into the exact fields and states expected by the Blade presentation.

## Shared services that SHOULD be reused

Codex should prefer proven reusable logic from CCLOS/ConsoleCrate for capabilities such as:

- installed-content/game discovery;
- TitleID/content detection;
- launch operations;
- Marketplace catalog access;
- download pipeline and queue management;
- segmented/single-download mechanics where already proven;
- caching;
- HTTP/network transport;
- Title Update checks/download/application logic;
- filesystem abstractions;
- storage enumeration;
- settings persistence;
- metadata parsing;
- background tasks;
- diagnostics/logging;
- profile/platform information where reusable.

Reuse implementation logic, interfaces, parsers, algorithms and service abstractions when appropriate.

Do not duplicate a backend simply because Blade is a separate frontend.

## Explicitly prohibited coupling

Blade code SHALL NOT call CCLOS presentation classes or depend on CCLOS being launched/running.

Forbidden patterns include equivalents of:

```cpp
CCLOSMarketplaceScreen->LoadGames();
CCLOSDownloadsPage->StartDownload();
CCLOSGameCard->Bind(...);
CCLOSNavigationManager->Open(...);
```

Preferred patterns are service-oriented:

```cpp
MarketplaceService->GetCatalog();
DownloadService->StartDownload();
LibraryService->EnumerateGames();
TitleUpdateService->CheckUpdates();
LaunchService->LaunchTitle();
```

The Blade frontend then consumes those services through Blade-specific adapters.

## Independence requirements

The final `BladeDashboard.xex` SHALL:

- launch independently;
- initialize its own XUI/runtime host;
- own its navigation lifecycle;
- own its presentation state;
- work without Aurora;
- work without Freestyle Dash;
- work without CCLOS running;
- not require CCLOS UI binaries/resources;
- use shared/backend code only through owned libraries, source modules, service interfaces or intentionally extracted reusable components.

## Shared-core evolution

Codex MAY initially reuse proven CCLOS service code in-place when that is the safest way to establish functionality.

However, when reusable code is clearly not presentation-specific, prefer progressively extracting it into a neutral reusable core such as `ConsoleCrateCore`, `CCLCore`, or equivalent.

Desired long-term model:

```text
                 ConsoleCrateCore
                 /              \
              CCLOS            Blade
          presentation      presentation
```

Do not perform a large speculative refactor before the first standalone Blade proof-of-architecture. Extract shared code incrementally as real reuse points are proven.

## First architectural proof

Before broad backend integration, Codex must prove:

1. standalone Xbox 360 XEX initializes XUI;
2. an existing BladeDash scene/resource renders without FSD/Aurora;
3. navigation/input can be owned by the standalone host;
4. at least one FSD-facing contract can be replaced by a newly written facade/adapter backed by a real service.

This proves both halves of the architecture before scaling it across the dashboard.

## Backend integration order

After the rendering proof, preferred sequence is:

1. main Blade shell/navigation;
2. installed game/content list;
3. launch service;
4. Marketplace adapter;
5. download service;
6. Title Update service;
7. profile/system/storage/network services;
8. remaining FSD-specific contracts;
9. performance and regression pass.

## UI fidelity rule

Backend limitations do not grant permission to redesign Blade.

When a modern/shared service exposes additional fields that the Blade frontend does not have a historical place to display, do not add modern UI by default. Keep the data behind the adapter until the project owner defines a fidelity-safe presentation.

## Final rule

**Reuse the CCLOS/ConsoleCrate brains, not the CCLOS face. Preserve the proven Blade face, replace its old FSD host, and keep the final Blade dashboard independently runnable.**
