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
Commit SHA: UNRECORDED — fill before first backend reuse
Recorded date: UNRECORDED
Recorded by: Codex/developer
```

Do not use `ConsoleCrateLive-PrivateBackup` or another backup/fork as implementation authority unless the project owner explicitly changes this rule.

## Service provenance table

Update this table whenever a new CCLOS/ConsoleCrate subsystem is reused.

| Blade service/adapter | CCLOS source subsystem/files | Source commit | Reuse method | Blade-owned destination | Notes/status |
|---|---|---|---|---|---|
| Library / game discovery | TBD | TBD | port/adapt/extract | TBD | Not started |
| Launch service | TBD | TBD | port/adapt/extract | TBD | Not started |
| Marketplace | TBD | TBD | port/adapt/extract | TBD | Not started |
| Download service | TBD | TBD | port/adapt/extract | TBD | Include high-throughput pipeline when available |
| Title Updates | TBD | TBD | port/adapt/extract | TBD | Not started |
| Achievements | TBD | TBD | port/adapt/extract | TBD | Not started |
| Trainers | TBD | TBD | port/adapt/extract | TBD | Not started |
| Disc-to-GOD / CopyDVD | TBD | TBD | port/adapt/extract | TBD | Blade `CopyDVD` frontend retained |
| Media / Watch TV | TBD | TBD | port/adapt/extract | TBD | Blade Media Center frontend retained unchanged |
| Storage / network helpers | TBD | TBD | port/adapt/extract | TBD | Not started |
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
