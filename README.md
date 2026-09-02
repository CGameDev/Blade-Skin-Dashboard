# Blade-Skin-Dashboard

Standalone Xbox 360 **Blade Dashboard** project based on the developer-approved working **BladeDash(2005)** Freestyle 3/FSD XUI skin.

## Product authority

**`BladeDash(2005)` is the absolute visual and behavioral authority.**

When the approved package defines a screen, layout, animation, transition, focus state, navigation behavior, menu hierarchy, dialog, loading state, sound event, or presentation detail, that implementation is the product specification.

Retail Xbox 360 Blades build **2.0.6770 is supplemental historical reference only** and may fill only genuine states/details not adequately defined by BladeDash.

See `docs/AUTHORITY_HIERARCHY.md`.

## Owner-approved product scope

Explicit scope decisions are recorded in `docs/OWNER_DECISIONS.md` and must not be reinterpreted by Codex.

Key decisions:

- product name: **Blade Dashboard**;
- preserve the BladeDash frontend and keep it externally editable through the verified XUI/XuiTool resource workflow wherever technically possible;
- retain BladeDash features whenever ConsoleCrate/CCLOS Core or Xbox platform services can supply real standalone functionality underneath them;
- CopyDVD uses CCLOS Disc-to-GOD functionality behind the Blade CopyDVD UI;
- Achievements, Title Updates and Trainers use the corresponding CCLOS/Xbox backend functionality behind their existing Blade scenes;
- Marketplace uses ConsoleCrate/CCLOS services behind the existing Blade Marketplace presentation;
- Downloads use the proven CCLOS download architecture behind Blade progress/state presentation;
- **Watch TV is integrated into the existing Blade Media / Media Center experience; the Blade Media UI must not be visually redesigned or replaced with CCLOS Watch TV UI**;
- authoritative backend-reference source is `CGameDev/ConsoleCrateLive` branch `main`, with exact reused commit recorded during implementation;
- authoritative production service is `consolecratelive.online`;
- Blade owns its own local Config/Cache/Data/Logs/Skins state and does not require a CCLOS local installation;
- default deployment root is `Hdd1:\Apps\BladeDashboard\` with `default.xex` as the deployable entrypoint;
- no new CCLOS-style OOBE;
- v1 primary acceptance target is 16:9 HD / 720p;
- raw BladeDash assets remain developer/private-build material until redistribution is intentionally reviewed.

## Project goal

This is a **working-skin transposition / host replacement** project, not screenshot-driven recreation.

The approved package already contains the Blade presentation: XUI/XUR scenes, animations, geometry, textures, audio, configuration, fonts, meshes/shaders, dialogs, lists and navigation presentation.

The standalone project preserves that frontend and replaces the Freestyle Dash host/runtime underneath it with a standalone XEX plus Blade-specific adapters backed by reusable ConsoleCrate/CCLOS services and Xbox platform APIs.

The final result does **not** require Freestyle Dash, Aurora, or the CCLOS application at runtime.

## Canonical implementation seed

Developer-local package:

```text
references/local/BladeDash(2005).zip
```

Approved SHA-256:

```text
b3ac2dbd88f0cd4cdda7c9bc8b10e7dc17f14f43f3e89e3f509bf13b5de6174b
```

Expected extraction directory:

```text
references/local/BladeDash(2005)/
```

The raw package remains developer-local unless redistribution is intentionally approved.

## Codex/contributor read order

Read before implementation:

1. `AGENTS.md`
2. `docs/AUTHORITY_HIERARCHY.md`
3. `docs/OWNER_DECISIONS.md`
4. `docs/WORKING_SKIN_BASELINE.md`
5. `docs/MILESTONE_000_WORKING_SKIN_STANDALONE_TRANSPOSE.md`
6. `docs/SHARED_CORE_ARCHITECTURE.md`
7. `docs/FIDELITY_DIRECTIVE.md`
8. `docs/CODEX_EXECUTION_RULES.md`
9. `docs/REFERENCE_MATRIX.md`
10. relevant checkpoint/compatibility/provenance reports

`docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md` is retired legacy material only.

## Implementation model

```text
BladeDash(2005) XUI/XUR/resources
              |
Blade/FSD compatibility facade
              |
Blade presentation models
              |
Blade-specific adapters
              |
Shared ConsoleCrate/CCLOS-derived services
+ Xbox 360/XDK platform services
              |
Hdd1:\Apps\BladeDashboard\default.xex
```

Guiding principle:

> **BladeDash supplies the face. ConsoleCrate/CCLOS supplies proven infrastructure. The standalone Blade XEX owns the runtime.**

## Feature-retention model

Do not remove a Blade feature simply because FSD supplied its original implementation. If there is a real ConsoleCrate/CCLOS/Xbox replacement, keep the existing Blade UI and connect that service underneath it.

Examples:

```text
Blade CopyDVD        -> BladeDiscCopyAdapter    -> CCLOS Disc-to-GOD
Blade Achievements   -> BladeAchievementAdapter -> CCLOS/Xbox achievements
Blade Title Updates  -> BladeTitleUpdateAdapter -> CCLOS Title Updates
Blade Trainers       -> BladeTrainerAdapter     -> CCLOS trainer/runtime
Blade Marketplace    -> BladeMarketplaceAdapter -> ConsoleCrate Marketplace
Blade Media Center   -> BladeMediaAdapter       -> CCLOS Watch TV/media services
```

For obsolete services with no real replacement, do not fake them or leave dead calls. Preserve the Blade presentation and use an existing disabled/unavailable state or record `OWNER_DECISION_REQUIRED`.

## Shared backend rule

Reuse proven ConsoleCrate/CCLOS backend capability through clean service interfaces and Blade-specific adapters.

Do not reuse CCLOS screens, widgets, view models, navigation classes, or visual components.

## Repository boundary

Do not commit Xbox 360 XDK binaries, original Microsoft dashboard executables/extracted executable code, credentials, or third-party resources whose redistribution status has not been intentionally approved.

The project may commit newly written runtime code, adapters, manifests/hashes, compatibility/provenance documentation, tooling and approved redistributable resources.

## Status

**Canonical direction:** preserve the approved BladeDash frontend, keep its practical features, replace the FSD host beneath it, and connect proven ConsoleCrate/CCLOS services through clean adapters. Retail 6770 fills only genuine frontend gaps.

**Milestone 000:** started 2026-09-01. Gate A is complete; approved XUI/XUR
editability and source compilation are locally validated; the retired
from-scratch attempt is quarantined; CCLOS provenance is recorded; and the
initial FSD compatibility map is in progress. Console revision 3 proved the
approved skin and splash XURs load and stay active, but its basic XUI host
rendered black. Revision 4 then proved `InitEx` cannot be used without a caller-
supplied device. Revision 5 visibly rendered the approved splash and exposed a
1080p view-scaling defect. Revision 6 applies the installed XDK's documented
1280x720-to-backbuffer transform and renders the approved splash full-frame on
hardware. The revision 6 log and settings evidence prove two resource-complete
runs, effects presentation, clean Back exits and boot persistence. Gate E passed
on 2026-09-01. Phase F then extracted the approved `main.xur` root/tab/class
contract and produced the first private main-shell console-test package. Its
2026-09-02 hardware run loaded and presented the approved main scene, navigated
all five runtime tab indices (`0` through `4`), handled Back, and shut down
cleanly with no logged failure. Gate F is functionally passed. Matched per-Blade
captures and F0/F1 comparison work remain required before visual-fidelity
approval. Phase G has now extracted the supplied game-list/control contracts
and implemented background loose-title discovery plus clean selected-title
launch. Revision 2 hardware proved its evidence-scoped A-button fallback, then
identified `XUI_ERR_CAST_FAILED` at supplied `gamelist.xur` creation and zero
standalone storage aliases. Revision 3 corrects the observed `ScnGameView`
`XuiTabScene` base, mounts the standard Xbox HDD/USB aliases before scanning,
and was then proven on hardware: all five category menus opened, with one list
showing five selectable rows. Those row labels were blank because the supplied
presenters explicitly require the original Freestyle `ConsoleFont` host
registration. Revision 4 proved that using the system font as the standalone
global default removes all rendered text; its log nevertheless discovered 13
launchable entries, showed zero in the specifically opened Xbox 360 category,
and exposed an `item_data=0` source request. Revision 5 restores the proven
Arial default, aliases `ConsoleFont`, accepts that observed callback, applies
the owner-requested English runtime labels, and logs category totals plus
discovered paths. Its 2026-09-02 hardware run discovered 12 loose launchables,
rendered and navigated five emulator plus seven homebrew rows with correct
counters, returned to the main shell, and launched SNES after orderly Blade
shutdown. Gate 3 is functionally passed. Six game-list commands remain in
Portuguese (`Opções`, `Favoritos`, `Voltar`, `Jogar`, `Menu Favoritos`, and
`Ordenar`), and matched fidelity comparison remains open. See
`docs/MILESTONE_000_CHECKPOINT.md`, `docs/PHASE_G_GAME_LIBRARY_CONTRACT.md`, and
`docs/PHASE_G_CONSOLE_TEST_PLAN.md`.
