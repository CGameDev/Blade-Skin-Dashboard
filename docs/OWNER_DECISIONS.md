# Owner Decisions — Blade Dashboard

## Status

**AUTHORITATIVE PRODUCT-SCOPE CONTRACT**

This document records explicit project-owner decisions for the standalone Blade Dashboard. Codex must not reinterpret these decisions or replace them with assumptions.

If a scope/product decision conflicts with older repository wording, this document and `AUTHORITY_HIERARCHY.md` win.

---

# 1. Product identity

Canonical product name:

**Blade Dashboard**

The approved `BladeDash(2005)` frontend remains the absolute visual and behavioral authority.

Application/host-identifying Freestyle Dash/FSD branding may be replaced with `Blade Dashboard` where needed to identify the standalone product, provided that:

- geometry is not changed;
- scene hierarchy is not changed;
- typography placement is not changed merely to accommodate branding;
- visual style is not modernized;
- generic Blade-era menu labels are not renamed unnecessarily;
- third-party authorship/credit is not falsely attributed to the new project.

This branding decision is an explicit owner-approved exception to the otherwise frozen BladeDash presentation contract.

---

# 2. Frontend remains externally editable

The Blade presentation must remain separable from the standalone runtime so future Codex sessions can edit, extend, or add features through XuiTool/XUI without rebuilding the entire backend whenever technically possible.

Preferred runtime resource strategy, in order:

1. external editable/repackable XZP/skin package if the verified XDK/XUI runtime supports it cleanly;
2. otherwise an external extracted BladeDash resource directory;
3. embed resources into the XEX only when a specific resource is proven impossible or unsafe to load externally.

Codex must verify the supported XuiTool/XUI workflow before choosing the final packaging mechanism.

The backend XEX and Blade presentation are separate architectural layers even if build tooling packages some generated resources for deployment.

---

# 3. Feature-retention policy

The default policy is:

> **If BladeDash already has a frontend feature and ConsoleCrate/CCLOS Core or an owned Xbox 360 platform service can provide the real functionality, retain the BladeDash feature and connect the replacement service underneath it.**

Do not delete a Blade feature merely because its original FSD implementation is unavailable.

Do not import CCLOS UI to make the feature work.

Use:

```text
Existing BladeDash feature
        |
FSD/Blade compatibility facade
        |
Blade adapter
        |
ConsoleCrate/CCLOS-derived service or owned Xbox platform service
```

### Explicit mappings

| BladeDash feature | Standalone implementation direction |
|---|---|
| Games / game list / game info | ConsoleCrate/CCLOS library discovery, metadata/cache and launch services behind Blade adapters |
| Marketplace | Existing ConsoleCrate/CCLOS Marketplace backend through `BladeMarketplaceAdapter` |
| Downloads | Proven CCLOS download/queue infrastructure, including the high-throughput pipeline when available, behind Blade progress/state adapters |
| Title Updates | CCLOS Title Update handling behind the existing Blade Title Update presentation |
| Achievements | CCLOS/Xbox achievement handling behind the existing Blade Achievements presentation |
| Trainers | CCLOS trainer/runtime handling behind the existing Blade Trainers presentation |
| CopyDVD | CCLOS Disc-to-GOD functionality behind the existing Blade `CopyDVD` presentation |
| Profiles / avatar | Available Xbox platform/profile services and reusable CCLOS logic behind the existing Blade presentation |
| File/path manager | Standalone filesystem services and reusable ConsoleCrate/CCLOS filesystem logic behind existing Blade scenes |
| Storage / system / network | Xbox platform APIs plus reusable service logic behind existing Blade system views |
| CoverFlow | Preserve existing BladeDash presentation and supply library/artwork data through adapters |
| Saved Games | Preserve existing Blade presentation and implement through available Xbox storage/content services where technically practical |

### Unsupported/obsolete services

For a BladeDash feature whose original external service is obsolete and for which no real replacement currently exists:

1. do not invent a fake backend;
2. do not redesign the surrounding Blade UI;
3. preserve the presentation where practical;
4. use an existing Blade-style disabled/unavailable state when one exists;
5. otherwise mark `OWNER_DECISION_REQUIRED` before creating a new visible behavior;
6. never leave a button silently calling a dead FSD-era service.

Examples that require service-by-service evaluation include Weather, legacy Xlink Kai/JQE functions, old plugin/update services, and other FSD-era network integrations.

---

# 4. Media + Watch TV decision

The existing BladeDash Media / Media Center presentation is retained and **must not be visually redesigned**.

ConsoleCrate/CCLOS Watch TV functionality is to be connected underneath the Blade Media experience.

Rules:

- use the current Blade media scenes, list controls, navigation style, geometry, transitions, fonts and artwork treatment;
- do not import the CCLOS Watch TV UI;
- do not replace the Blade Media Center with a CCLOS-style media screen;
- Watch TV data/actions may populate or extend the existing Blade media list/control patterns;
- if a visible `Watch TV` entry is required, it must use the existing Blade list/menu style and must not introduce new chrome or layout geometry;
- playback and media-service functionality may reuse proven CCLOS media/backend logic through a `BladeMediaAdapter`/equivalent;
- any new media capability must remain subordinate to the existing Blade Media UI contract.

The goal is **CCLOS Watch TV capability with the Blade Media Center face**.

---

# 5. Marketplace placement and naming

Use the existing BladeDash Marketplace-facing presentation/hierarchy wherever it exists.

Visible product-facing name:

**Marketplace**

Do not create a new top-level Blade solely for ConsoleCrate.

ConsoleCrate/CCLOS backend terminology, REST/API concepts, server paths and CCLOS UI labels must remain behind the adapter layer.

---

# 6. Authoritative CCLOS source

Authoritative backend-reference repository:

`CGameDev/ConsoleCrateLive`

Canonical branch:

`main`

At the beginning of backend reuse work, Codex must record the exact source commit SHA in a provenance/checkpoint document before porting or extracting code.

Rules:

- use `CGameDev/ConsoleCrateLive` as the authoritative source for reusable CCLOS/ConsoleCrate backend logic;
- do not use backup repositories as implementation authority unless the owner explicitly directs it;
- initially treat the CCLOS repository as a source/reference for proven services, not as a place to casually modify while building Blade;
- do not couple Blade to CCLOS presentation classes;
- perform shared-core extraction incrementally only after the Blade standalone proof-of-architecture succeeds.

---

# 7. Production service authority

Authoritative production service/domain:

`consolecratelive.online`

This is the permanent ConsoleCrate production service authority for Blade Dashboard integrations.

Rules:

- do not resurrect deprecated NAS-hosted CCLOS infrastructure;
- do not restore deprecated Cloudflare-based CCLOS infrastructure merely because old code references it;
- do not create a duplicate Blade-specific Marketplace/backend service when ConsoleCrate already provides the capability;
- migrate/replace stale endpoints discovered in reused code with the current ConsoleCrate production service contract;
- credentials/secrets must never be committed.

---

# 8. Blade-owned local data

Blade Dashboard must not require a CCLOS installation directory or CCLOS-local cache/config files.

Default installation root:

```text
Hdd1:\Apps\BladeDashboard\
```

Blade-owned runtime directories should be rooted beneath the application directory, conceptually:

```text
Hdd1:\Apps\BladeDashboard\Config\
Hdd1:\Apps\BladeDashboard\Cache\
Hdd1:\Apps\BladeDashboard\Data\
Hdd1:\Apps\BladeDashboard\Logs\
Hdd1:\Apps\BladeDashboard\Skins\
```

Codex may refine exact subfolder names only for a documented technical reason, while preserving the principle that Blade owns its local state independently of CCLOS.

Normal Xbox content/game/storage locations remain normal platform locations and are not duplicated into the Blade application directory.

---

# 9. Boot, install and first-run behavior

Blade Dashboard does **not** receive a new CCLOS-style OOBE.

First launch should:

- initialize required local folders/config/cache;
- validate/load the approved Blade frontend resources;
- enter the approved BladeDash presentation;
- expose configuration through Blade-style settings and existing Blade presentation patterns.

Default deployment:

```text
Hdd1:\Apps\BladeDashboard\default.xex
```

Project/build target name may remain `BladeDashboard`, but the deployable dashboard entrypoint is `default.xex` for a conventional Xbox 360 application/dashboard layout.

DashLaunch documentation may show how to point the default dashboard path to this XEX, but the application/build process must **not automatically edit `launch.ini`** unless the owner explicitly requests that behavior later.

---

# 10. Initial display target

Version 1 acceptance target is the approved BladeDash presentation in **16:9 HD**, with 720p as the primary target-console validation mode.

Rules:

- preserve the working skin's existing scaling/layout behavior;
- do not delay the standalone architecture to perfect every historical output mode before the primary 16:9 HD path works;
- additional 4:3/SD/output-mode compatibility may be validated later unless the existing resources already support it without additional redesign;
- do not alter the approved 16:9 presentation to normalize other modes.

---

# 11. Release and redistribution policy

Until redistribution rights for all supplied BladeDash resources are intentionally reviewed/approved, the project is treated as a **developer/private-build runtime project** with respect to the raw BladeDash asset package.

Public GitHub may contain:

- newly written runtime/source code;
- adapters/services;
- build scripts that do not redistribute proprietary SDK content;
- documentation;
- manifests/hashes;
- compatibility matrices;
- approved redistributable resources.

Do not automatically publish or package the owner-supplied raw BladeDash ZIP, fonts, audio, textures or other third-party/historical assets whose redistribution status has not been established.

The runtime should support the developer-local approved skin package/resource tree during development.

A future explicit redistribution review may change this release policy.

---

# 12. Owner-decision precedence

For product scope:

1. `AUTHORITY_HIERARCHY.md` determines source authority;
2. this `OWNER_DECISIONS.md` determines explicit product/scope choices;
3. Milestone 000 determines implementation sequence;
4. shared-core and execution documents determine architecture/engineering rules;
5. Retail 6770 fills only genuine BladeDash gaps.

Codex must not convert an explicit owner decision into `REFERENCE_GAP` or silently choose a different product behavior.

## Final rule

**Preserve the approved Blade face. Connect every practical Blade feature to real ConsoleCrate/CCLOS Core or Xbox platform functionality. Keep the frontend externally editable. Use the Blade Media Center for Watch TV. Keep Blade standalone and independent of the CCLOS application.**
