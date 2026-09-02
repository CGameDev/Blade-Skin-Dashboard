# Legacy Attempt Audit — Retired From-Scratch Blade Work

## Decision

The pre-Milestone-000 implementation is not the product base. Its screenshot-led
Retail 6770 recreation and synthetic Blade XUI are retired and must not be
continued.

The complete dirty working state was quarantined reversibly before the repository
was advanced to the new Milestone 000 authority:

```text
Git stash: stash@{0}
Message: retired-from-scratch-audit-snapshot-20260901
Stash object: cdd652d2a958652b02d7aa62f9d98b1f773d68f2
Untracked-content parent: 2959f3470a70c4e5e1321913ed1321f617092ef3
Original base: ace61f1f357f1986246f580ee60d94252e6318d2
```

At the initial audit checkpoint no legacy code or UI was restored. Phase E later
selectively ported and reviewed only the runtime/build candidates listed below.
The stash remains an audit source, not an implementation branch, and was never
applied or popped wholesale.

## Reusable candidates

These items may be selectively recovered only after review against the approved
BladeDash host contract.

| Legacy item | Candidate value | Reuse condition |
|---|---|---|
| `BladeDashboard.sln`, `.vcxproj`, filters | Proven Xbox 360 project/build skeleton and XDK libraries | Remove synthetic-XUI inputs, rename/package as `default.xex`, and point resources only at the approved BladeDash presentation |
| `src/app/Main.cpp` | XEX entry point, clean shutdown and queued `XLaunchNewImage` dispatch | Remove GAME-001/diagnostic product assumptions and retain only host lifecycle behavior |
| `src/app/BladeDashboardApp.*` | Working `CXuiModule` initialization, render loop, resource URI loading and shutdown pattern | Replace the synthetic `blade_shell.xzp`, substitute-font registration and 1280x720 recreation transform with approved BladeDash resource and host requirements |
| `src/core/BackgroundQueue.*` | Bounded background worker foundation | Re-test lifetime, queue saturation and shutdown behavior before service work |
| `src/diagnostics/DebugLog.*` | Persistent console diagnostics | Redirect to Blade-owned `Logs/`; avoid stale package-local assumptions |
| `src/platform/ControllerInput.*` | XInput polling and pressed-button edge state | Map into Blade/FSD compatibility events; do not hard-code the old checkpoint exit behavior |
| `src/platform/LaunchService.*` | Deferred title/XEX launch helper | Validate paths, launch data and return behavior on the standalone dashboard host |
| `src/platform/SettingsStore.*` | Small atomic settings foundation | Replace the old diagnostic schema with Blade-owned Config/Data schemas and migration/version rules |
| `src/navigation/NavigationState.*` | Bounded navigation-state utility | Use only if it can track the approved Blade scene stack without competing with XUI navigation/timelines |
| `src/services/IRuntimeService.h` | Minimal service lifecycle interface | Align with `docs/SHARED_CORE_ARCHITECTURE.md` before adding service implementations |
| `tools/build/Build-Project.ps1` | XDK discovery/prerequisite checks and deterministic MSBuild entry | Remove GAME-001 outputs and validate against the new project/resource layout |
| `tools/fidelity/*` | Generic overlay/difference tooling | Retain only tool logic; replace Retail-6770-specific inputs with BladeDash migration captures |
| diagnostic test card | Known-visible XUI/XEX smoke fixture | Diagnostics only; never use as the production frontend or visual fallback |

The old `ShellScene` registration may contain lifecycle mechanics, but its class
contract was written for the synthetic shell. It is not approved for direct
reuse until the FSD compatibility façade identifies the real class/scene contract
expected by the supplied XURs.

## Quarantined presentation work

The following must not return to the production path:

- `ui/xui/reference/game_root_signed_in.xui` and its hard-coded Games Blade;
- screenshot-derived GAME-001 state specifications, precapture issues and V1/V2
  comparison artifacts;
- the generic colored-panel/diagnostic Blade shell as a product fallback;
- the Liberation Sans checkpoint font and project logic that treated it as the
  dashboard typeface;
- Retail 6770 screenshot/video/Xenia capture sets as frontend authority;
- docs and packaging copy that describe GAME-001 as the implementation target;
- build/package rules that compile `game_root_signed_in.xui` into
  `blade_shell.xzp`.

These artifacts may be retained locally as history. They are not evidence for a
BladeDash-defined state and are not to be shipped.

## Phase E selective recovery record

The following foundations were manually ported into the active tree and revised
for the working-skin host:

- Xbox 360 solution/project structure;
- `CXuiModule` lifecycle and XDK texture loader;
- background queue;
- persistent diagnostics;
- controller polling;
- launch handoff;
- versioned settings storage;
- bounded navigation-state utility;
- XDK discovery/build script.

Material changes during recovery:

- removed every custom-build reference to synthetic XUI and substitute
  Liberation font assets;
- changed the output contract to deployable `default.xex`;
- changed local ownership paths to `Logs/`, `Config/` and `Skins/`;
- removed the synthetic 1280x720 render transform and use the stock XUI render
  path;
- added the XDK-sample-supported `LoadSkin` call for supplied `skin.xur` before
  `LoadFirstScene`;
- first scene is supplied `SplashScreen.xur`, not a generated diagnostic card;
- no legacy `ShellScene` class or recreated Blade resource was recovered.

The selected code remains subject to hardware validation. Recovery does not make
the old UI or old Retail-6770 target current again.

## Existing local capture material

Some ignored/untracked capture folders from the retired effort remain in the
workspace outside the stash. They were not deleted, modified or added to the new
implementation. Any future migration comparison must use the approved
`BladeDash(2005)` working frontend as primary authority; Retail 6770 material can
only fill a documented `REFERENCE_GAP`.

## Recovery rule

Recover one reusable file or cohesive runtime unit at a time from the stash,
review it against the new architecture, remove retired UI assumptions, build it,
and document the resulting role. Do not apply or pop the complete stash over the
Milestone 000 tree.
