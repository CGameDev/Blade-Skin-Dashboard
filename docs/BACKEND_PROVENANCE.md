# Backend Provenance — ConsoleCrate/CCLOS Reuse

## Status

**Required implementation record.**

This file tracks the exact ConsoleCrate/CCLOS source used when backend logic is ported, adapted, or extracted for Blade Dashboard.

Authoritative source repository:

```text
CGameDev/ConsoleCrateLive
```

Authoritative branch:

```text
main
```

Codex must fill the current source commit before reusing backend code.

## Current approved source snapshot

```text
Repository: CGameDev/ConsoleCrateLive
Branch: main
Commit SHA: e8440b672c88ab07dab2e2a52bbcb55c809336d9
Recorded date: 2026-09-01
Recorded by: Codex
```

Verification method: read-only `git ls-remote` against
`https://github.com/CGameDev/ConsoleCrateLive.git`, resolving
`refs/heads/main`, followed by an ignored local checkout at the exact commit.
The checkout was clean when the Phase G library/launch contract was inspected.

Do not use `ConsoleCrateLive-PrivateBackup` or another backup/fork as implementation authority unless the project owner explicitly changes this rule.

## Service provenance table

Update this table whenever a new CCLOS/ConsoleCrate subsystem is reused.

| Blade service/adapter | CCLOS source subsystem/files | Source commit | Reuse method | Blade-owned destination | Notes/status |
|---|---|---|---|---|---|
| Library / game discovery | `ConsoleCrateNativeStore/StoreMain.cpp`: `FindLaunchableImage` lines 241-245; device probes lines 1192-1193 | `e8440b672c88ab07dab2e2a52bbcb55c809336d9` | Adapt bounded recursive loose-image discovery and local-device conventions; no CCLOS UI/catalog structure copied | `src/services/InstalledGameService.*`, consumed by `src/adapters/BladeGameLibraryAdapter.*` | Gate-3 subset: configurable scan roots, fixed-capacity presentation model, background enumeration; container discovery is intentionally not claimed |
| Launch service | `ConsoleCrateNativeStore/StoreMain.cpp`: selected-title loose-image launch lines 856, 880-881 | `e8440b672c88ab07dab2e2a52bbcb55c809336d9` | Preserve `XLaunchNewImage(..., XLAUNCH_FLAG_CLEAR_LAUNCH_DATA)` semantics behind clean Blade shutdown | `src/platform/LaunchService.*`, queued by `src/adapters/BladeGameLibraryAdapter.*` | Existing Blade launch service is retained; Phase G connects selected installed-game paths to it |
| Storage aliases | `ConsoleCrateNativeStore/main.cpp`: ANSI object-manager declarations lines 73-84, `MountDriveAlias` lines 87-96, and `ConsoleCrateMountInternalHdd` lines 99-116 | `e8440b672c88ab07dab2e2a52bbcb55c809336d9` | Adapt the Xbox object-manager alias boundary only; the complete standard alias-to-device set is corroborated by the approved local Freestyle `DrivesManager_000.cpp` lines 19 and 23-25 | `src/platform/StorageAliasService.*` | Phase G R2 hardware proved the standalone process inherited zero configured aliases. R3 maps `Hdd:`/`Hdd1:` to `\Device\Harddisk0\Partition1` and `Usb0:`-`Usb2:` to `\Device\Mass0`-`Mass2` before background discovery; no CCLOS UI/config dependency is introduced |
| Marketplace | TBD | TBD | port/adapt/extract | TBD | Not started |
| Download service | TBD | TBD | port/adapt/extract | TBD | Include high-throughput pipeline when available |
| Title Updates | TBD | TBD | port/adapt/extract | TBD | Not started |
| Achievements | TBD | TBD | port/adapt/extract | TBD | Not started |
| Trainers | TBD | TBD | port/adapt/extract | TBD | Not started |
| Disc-to-GOD / CopyDVD | TBD | TBD | port/adapt/extract | TBD | Blade `CopyDVD` frontend retained |
| Media / Watch TV | TBD | TBD | port/adapt/extract | TBD | Blade Media Center frontend retained unchanged |
| Storage / network helpers | Storage alias subset recorded above; network TBD | `e8440b672c88ab07dab2e2a52bbcb55c809336d9` | port/adapt/extract | `src/platform/StorageAliasService.*`; network TBD | Storage alias subset started for Phase G; network not started |
| Filesystem/path helpers | TBD | TBD | port/adapt/extract | TBD | Not started |
| Cache/metadata/artwork | TBD | TBD | port/adapt/extract | TBD | Not started |

## Reuse rules

- Record exact source commit before copying/adapting implementation details.
- Prefer service/core logic, not CCLOS presentation code.
- Do not make Blade depend on CCLOS running or on CCLOS-local configuration/cache folders.
- Do not casually modify the CCLOS repository during Blade work.
- If a neutral shared core is later extracted, document the extraction commit and consumer versions here.
- When old CCLOS code contains stale infrastructure endpoints, use the current production authority `consolecratelive.online` rather than restoring deprecated NAS/Cloudflare infrastructure.
- Never record credentials, passwords, tokens, FTP/SSH secrets, or API keys in this file.

## Final rule

**Every reused backend subsystem must be traceable to the exact authoritative CCLOS source snapshot from which it came.**
