# Codex Execution Rules — Blade-Skin-Dashboard

## Purpose

These instructions exist to prevent assumption, scope drift, visual reinterpretation, premature implementation, and accidental coupling to Aurora or CCLOS UI code.

Codex must read this file together with `FIDELITY_DIRECTIVE.md` before making implementation changes.

---

# 1. Repository authority

Canonical implementation repository:

`https://github.com/CGameDev/Blade-Skin-Dashboard.git`

Default branch: `main`

All project source, XUI source, scripts, documentation, fidelity reports, test code, and release notes belong in this repository.

Do not create a second implementation repository.

Do not place the standalone implementation into the CCLOS repository.

Do not turn the existing Aurora Blade skin repository into the standalone product.

---

# 2. Read-before-write order

At the start of every Codex session that changes UI or architecture, read in this order:

1. `README.md`
2. `docs/FIDELITY_DIRECTIVE.md`
3. `docs/CODEX_EXECUTION_RULES.md`
4. `docs/MILESTONE_001_RETAIL_6770_EXACT_REPLICA.md`
5. `docs/REFERENCE_MATRIX.md`
6. existing checkpoint/fidelity reports relevant to the screen being changed

Do not begin by generating UI from the project name alone.

---

# 3. Canonical target is fixed

Target: **Xbox 360 Retail Blades build 2.0.6770**.

Do not switch to 1888, 5759, 5766, 5787, 6683, 6690, 6717, NXE, Metro, or any community recreation unless a specific documented comparison requires it.

Older builds are evidence only.

They are not alternate design options.

---

# 4. Mandatory first task: environment inventory

Before UI implementation, inspect the local development machine for the actual Xbox 360 build environment.

Document findings in `docs/BUILD_ENVIRONMENT.md`.

Find and record, without copying proprietary binaries into the repository:

- Xbox 360 XDK installation root;
- XDK version;
- `XuiTool.exe` location;
- Visual Studio/XDK integration present;
- C/C++ compiler and linker used for Xbox 360 target;
- XEX packaging/build tools;
- XUI include files;
- XUI libraries;
- XUI/XUR tooling;
- available sample projects that are legally present locally;
- environment variables;
- build scripts/toolchain files already available;
- known working Xbox 360 homebrew build path from the developer's environment if discoverable.

Do not assume paths.

Search the machine and record the detected paths.

Do not commit XDK files.

---

# 5. XuiTool handling

XuiTool is part of the local authoring workflow when available.

Codex may:

- locate it;
- launch it when local execution policy permits;
- create/edit XUI source files;
- generate companion source/bindings using supported tools;
- automate documented command-line build steps;
- verify generated output;
- document exact GUI-only steps when no supported automation exists.

Codex must not invent command-line flags for XuiTool.

If a required operation is only accessible through the GUI, add a deterministic manual checkpoint rather than pretending the operation was automated.

---

# 6. Reference acquisition before implementation

For each state:

1. add/confirm its entry in `REFERENCE_MATRIX.md`;
2. identify the source URL/file/footage and build number;
3. confirm it is Retail 6770 wherever possible;
4. record uncertainty explicitly;
5. do not use a nearby-build screenshot without labeling it;
6. do not use generated images as evidence of original appearance;
7. do not use the old Aurora Blade skin as the final authority.

When possible, maintain developer-local reference captures outside the public repo and record only metadata/path placeholders or legally redistributable reference images in Git.

---

# 7. Measurement discipline

Do not eyeball geometry once a measurable reference exists.

For each screen, create a state specification containing measured or derived values for:

- canvas/reference resolution;
- safe-area assumptions;
- blade boundaries;
- active blade bounds;
- inactive blade bounds;
- separators;
- menu origin;
- row spacing;
- text baselines;
- image bounds;
- controller legend bounds;
- dialog bounds;
- focus highlight bounds;
- color/alpha samples;
- animation start/end coordinates;
- timing estimates/measurements.

Prefer constants/data files with meaningful names over magic numbers scattered through C++.

---

# 8. No implementation by imagination

The following is prohibited:

> “This probably looked like…”

> “A modern equivalent would be…”

> “For usability I changed…”

> “I used a similar green…”

> “I simplified…”

> “I added…”

If the original state is unknown, mark a reference gap.

Do not fill visual gaps with a design generated from general Blades nostalgia.

---

# 9. Implementation layering

Required architectural separation:

```text
UI / XUI scenes
      |
Presentation/View Models
      |
Blade-compatible domain models
      |
Adapters
      |
Services / platform APIs / filesystem / launch APIs
```

A modern service must not leak its terminology or layout requirements into the UI.

UI code must not directly know CCLOS screen/widget implementations.

---

# 10. Marketplace rule

Reuse the existing ConsoleCrate/CCLOS Marketplace infrastructure.

Do not recreate its backend.

Create a `BladeMarketplaceAdapter` (or equivalent) that converts modern service data into the fields/states expected by the 6770-compatible frontend.

Where the modern backend has information the original UI had no visible place for, keep it out of the primary UI unless the owner later explicitly defines a faithful location.

Do not “improve” Marketplace with CCLOS-style cards, modern download pages, or extra badges.

---

# 11. Data behavior vs visual behavior

Dynamic data is allowed and required, but it must fit the original visual contract.

Examples:

- real installed games may populate a classic list;
- ConsoleCrate catalog data may populate Marketplace entries;
- real profile data may populate the gamercard;
- real storage values may populate storage screens;
- real network state may populate the original-style network screen.

The data is modern/live.

The presentation remains 6770.

---

# 12. Standalone runtime rule

Produce an independent Xbox 360 dashboard XEX.

Do not require Aurora to launch, draw, navigate, provide data, or execute games.

Implement owned subsystems for:

- application lifecycle;
- scene management;
- input routing;
- game/content discovery;
- launch operations;
- settings persistence;
- service requests;
- local cache;
- profile-facing data where technically available;
- storage/network display where technically available.

---

# 13. Build discipline

Establish one documented canonical build command or build workflow.

The workflow must:

- fail clearly on missing local XDK prerequisites;
- avoid hard-coding one username in committed scripts;
- keep generated intermediates out of source directories where practical;
- separate Debug and Release outputs;
- write build logs;
- record the produced XEX/resource paths;
- avoid committing proprietary SDK artifacts;
- be repeatable from a clean checkout plus the developer's installed toolchain.

---

# 14. Performance rule

Fidelity does not permit sluggishness that the original dashboard did not exhibit.

Do not perform blocking network/catalog scans on the UI thread.

Use background operations for:

- Marketplace refresh;
- artwork acquisition;
- library scanning;
- metadata lookup;
- Title Update checks;
- filesystem enumeration that may stall.

However, do not invent modern loading animations when the original has a known loading state.

Reproduce the original loading presentation while work happens asynchronously behind it.

---

# 15. Fidelity checkpoint order

A major screen must pass checkpoints in this order:

1. **Static geometry**
2. **Typography/surface treatment**
3. **Focus states**
4. **Controller navigation**
5. **Transitions/animation**
6. **Dynamic data binding**
7. **Backend service connection**
8. **Performance pass**
9. **Side-by-side fidelity pass**

Do not connect a complex backend and then treat visual fidelity as final polish.

---

# 16. Screenshot/capture requirements

For every fidelity checkpoint, save a recreated capture and a comparison report.

Recommended developer-local organization:

```text
FidelityCaptures/
  6770/
    <screen>/<state>/original.*
  recreated/
    <screen>/<state>/recreated.*
  comparisons/
    <screen>/<state>/overlay.*
    <screen>/<state>/diff.*
    <screen>/<state>/report.md
```

If original captures cannot legally be committed, keep them outside Git and commit only comparison metadata that does not redistribute the original material.

---

# 17. No premature “done” claims

Codex must not call a screen complete because:

- it compiles;
- it renders;
- it resembles a screenshot;
- navigation works;
- backend data loads.

Only mark a screen complete when the `FIDELITY_DIRECTIVE.md` definition of done is satisfied.

---

# 18. Testing batching rule

Do not interrupt implementation for trivial manual hardware testing after every tiny source change.

Batch substantial related work into meaningful checkpoints.

Run desktop/static/resource/build validations continuously where possible.

Use console hardware testing after cohesive units such as:

- base Blade renderer + navigation;
- one complete canonical blade;
- full-screen transition group;
- Marketplace integration group;
- game launch/content group;
- final fidelity hardening group.

Do not postpone compile/build validation.

---

# 19. Regression rule

Every fidelity-approved screen becomes a regression target.

When shared navigation/rendering code changes:

- rebuild existing states;
- re-run visual comparisons where practical;
- verify previously approved geometry did not move;
- verify focus/navigation did not change;
- verify animation timing did not regress.

---

# 20. Documentation after each checkpoint

At the end of a checkpoint, update project documentation with:

- what was implemented;
- exact source files changed;
- reference states used;
- build status;
- console-test status;
- fidelity comparison status;
- open F0/F1/F2/F3 differences;
- technical limitations;
- reference gaps;
- next permitted checkpoint.

Do not leave critical decisions only in Codex chat history.

---

# 21. Prohibited repository content

Do not commit:

- Xbox 360 XDK binaries/libraries not licensed for redistribution;
- original Microsoft dashboard executables;
- original Microsoft proprietary dashboard resource packages;
- extracted original Microsoft executable code;
- developer credentials;
- FTP/SSH passwords;
- private API keys;
- personal local absolute paths unless they are examples/placeholders;
- large local build outputs unless intentionally published as permitted release artifacts.

---

# 22. When blocked

If blocked by a technical uncertainty:

1. document the exact uncertainty;
2. inspect local/tool/reference evidence;
3. choose the least visually invasive temporary implementation;
4. mark it as temporary;
5. do not invent a permanent UI solution.

If blocked only on a non-critical manual visual check, continue with other independent milestone tasks rather than redesigning around the missing check.

---

# 23. Final rule

**Never optimize for originality. Optimize for evidence-backed Retail 6770 fidelity.**
