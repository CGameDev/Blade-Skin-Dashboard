# Retail 6770 Reference Matrix

## Purpose

This file is the source-of-truth registry for evidence used to recreate each Blades state.

No production screen should be implemented without an entry here.

The presence of a state in this file does not mean its reference is complete. Confidence and gaps must be explicit.

---

# Reference confidence labels

- `CONFIRMED_6770` — source demonstrably shows Retail build 6770 or a 6770 state.
- `CONFIRMED_NEARBY_BUILD_UNCHANGED` — nearby Blades build used only after evidence that the relevant element is unchanged in 6770.
- `STRUCTURAL_REFERENCE_ONLY` — useful for hierarchy/behavior, not sufficient for pixel/color measurement.
- `REFERENCE_GAP` — no adequate evidence yet.
- `NOT_APPLICABLE` — state is not part of the selected milestone or target build.

---

# Canonical build archive

## Primary archive

Repository:

`https://github.com/thedev0ps/Xbox-360-Dashboard-Archive`

Canonical target path:

`Blades/Retail/6770`

URL:

`https://github.com/thedev0ps/Xbox-360-Dashboard-Archive/tree/main/Blades/Retail/6770`

Observed archive entries at this path include original Microsoft dashboard artifacts such as:

- `dash.xex`
- `shrdres.xzp`

**Boundary:** These establish the historical build identity and may support developer-local research. They must not be committed into this project, redistributed in this project's releases, copied into project source, or made required runtime dependencies.

Do not treat binary presence as permission to reuse proprietary code/resources.

---

# Structural reference

## Architecture of Consoles — Xbox 360

URL:

`https://github.com/flipacholas/Architecture-of-consoles/blob/master/articles/xbox-360.Rmd.md`

Useful documented Blades states include:

- Home
- Games
- Settings
- Storage
- Avatar
- Guide

Important structural findings documented by this source:

- top-level services are organized as overlapping blades;
- only one blade/category is focused/open at a time;
- neighboring blade edges communicate horizontal navigation at the top hierarchy;
- some deeper screens use a full-screen layout and remove the neighboring blade indicators to reclaim space;
- therefore, side blades must not be forced onto every child screen.

Confidence for exact 6770 pixel/color measurements: `STRUCTURAL_REFERENCE_ONLY` unless an included image is separately verified as 6770.

---

# State matrix

| ID | Area | State | Required source status | Current status | Notes / next evidence required |
|---|---|---|---|---|---|
| ROOT-001 | Root | Dashboard initial/resting state | Confirmed 6770 still + motion | REFERENCE_GAP | Need verified 6770 capture with exact selected blade and sign-in state. |
| ROOT-002 | Root | Signed-out variant | Confirmed 6770 still | REFERENCE_GAP | Determine exact visible profile/status differences. |
| ROOT-003 | Root | Signed-in variant | Confirmed 6770 still | REFERENCE_GAP | Determine gamercard/profile placement and content. |
| BLADE-001 | Navigation | Left-to-right blade switch | Confirmed 6770 motion | REFERENCE_GAP | Need footage suitable for frame/timing analysis. |
| BLADE-002 | Navigation | Right-to-left blade switch | Confirmed 6770 motion | REFERENCE_GAP | Need footage suitable for frame/timing analysis. |
| BLADE-003 | Navigation | Inactive blade edge geometry | Confirmed 6770 still | REFERENCE_GAP | Measure exact visible widths/curves/separators. |
| BLADE-004 | Navigation | Active blade geometry | Confirmed 6770 still | REFERENCE_GAP | Measure canvas-relative bounds. |
| LIVE-001 | Xbox Live | Primary online/Xbox Live blade | Confirmed 6770 | REFERENCE_GAP | Identify exact final-6770 menu hierarchy. |
| GAME-001 | Games | Primary Games blade | Confirmed 6770 | REFERENCE_GAP | Need exact 6770 selected-state reference. |
| GAME-002 | Games | Full-screen games/library child | Confirmed 6770 | REFERENCE_GAP | Structural precedent exists; verify final 6770 layout. |
| GAME-003 | Games | Game action/launch state | Confirmed 6770 | REFERENCE_GAP | Identify actual canonical state before implementing details. |
| MARKET-001 | Marketplace | Primary Marketplace entry state | Confirmed 6770 | REFERENCE_GAP | Required because backend will map to ConsoleCrate services. |
| MARKET-002 | Marketplace | Browse/category state | Confirmed 6770 | REFERENCE_GAP | Need exact list/grid behavior, labels, geometry. |
| MARKET-003 | Marketplace | Item detail state | Confirmed 6770 | REFERENCE_GAP | Need exact action/menu placement. |
| MARKET-004 | Marketplace | Download/purchase/progress state | Confirmed 6770 | REFERENCE_GAP | Need canonical visual flow; map modern download operation behind it. |
| MEDIA-001 | Media | Primary Media blade | Confirmed 6770 | REFERENCE_GAP | Need exact final-6770 menu labels and selected state. |
| MEDIA-002 | Media | Media child view(s) | Confirmed 6770 | REFERENCE_GAP | Inventory only after evidence. |
| SYS-001 | System | Primary System blade | Confirmed 6770 | REFERENCE_GAP | Need exact selected-state reference. |
| SET-001 | Settings | Settings main view | Confirmed 6770 | REFERENCE_GAP | Historical structural reference exists; verify 6770. |
| STORE-001 | Storage | Storage main view | Confirmed 6770 | REFERENCE_GAP | Historical source shows full-screen behavior; verify 6770 presentation. |
| NET-001 | Network | Network settings/status view | Confirmed 6770 | REFERENCE_GAP | Need exact 6770 structure and supported actions. |
| PROF-001 | Profile | Gamercard/profile display | Confirmed 6770 | REFERENCE_GAP | Need signed-in canonical reference. |
| AVATAR-001 | Profile | Avatar selector/profile visual | Confirmed 6770 if still present | REFERENCE_GAP | Structural historical reference exists; verify final build applicability. |
| GUIDE-001 | Guide | Xbox Guide opening/resting view | Confirmed 6770 | REFERENCE_GAP | Treat as separate later runtime/overlay work if platform integration requires it. |
| DIALOG-001 | Dialogs | Confirmation dialog | Confirmed 6770 | REFERENCE_GAP | Catalog actual families used by implemented flows. |
| DIALOG-002 | Dialogs | Warning/error dialog | Confirmed 6770 | REFERENCE_GAP | Need exact text/control layout. |
| LOAD-001 | Loading | Canonical loading/progress state | Confirmed 6770 | REFERENCE_GAP | Do not invent spinner/progress chrome. |
| EMPTY-001 | Empty | No content/empty list state | Confirmed 6770 | REFERENCE_GAP | Needed for robust real-world library use. |

---

# Measurement record template

Duplicate this section into a checkpoint/state spec once adequate evidence exists.

```text
State ID:
Canonical build: 2.0.6770
Reference confidence:
Reference URL/file:
Reference frame/timecode:
Reference resolution:
Displayed aspect ratio:
Safe-area notes:

Active blade:
Left visible blade boundaries:
Right visible blade boundaries:
Separator bounds:
Main content bounds:
Header bounds/baseline:
Menu origin:
Row height:
Row gap:
Selected row bounds:
Secondary/info panel bounds:
Controller legend bounds:
Profile/status bounds:

Font observations:
Primary text size:
Secondary text size:
Weight:
Alignment:
Wrapping/truncation:

Color observations:
Blade base:
Gradient stops:
Separator:
Highlight:
Selected text:
Unselected text:
Disabled text:
Overlay alpha:

Initial focus:
D-pad up:
D-pad down:
D-pad left:
D-pad right:
A:
B:
X:
Y:
LB/RB:
LT/RT:
Guide:

Transition in:
Transition out:
Duration:
Easing:
Layer order:
Audio event(s):

Reference gaps:
Technical limitations:
Open fidelity issues:
Status:
```

---

# Evidence collection rules

1. Prefer direct Retail 6770 footage/captures.
2. Record build number whenever known.
3. Record video timecodes, not just video URLs.
4. Avoid screenshots that have been stretched, cropped, color-filtered, or composited when a cleaner source exists.
5. Never measure geometry from a thumbnail when the full-resolution source exists.
6. If multiple captures disagree because of 4:3 vs 16:9 behavior, document them as distinct output cases rather than averaging measurements.
7. Do not infer a 6770 state solely from 1888 footage.
8. Do not use generated mockups as original evidence.
9. The old Aurora Blade skin may provide clues but cannot close a 6770 reference gap by itself.
10. If a reference cannot legally be stored in this repository, record its developer-local path placeholder plus public source metadata rather than committing it.

---

# Required next research pass

Before production UI implementation, Codex should gather and register enough verified Retail 6770 evidence to close at minimum:

- ROOT-001
- BLADE-001
- BLADE-002
- BLADE-003
- BLADE-004
- GAME-001
- MARKET-001
- MEDIA-001
- SYS-001

Do not substitute older build screenshots silently just to unblock implementation.
