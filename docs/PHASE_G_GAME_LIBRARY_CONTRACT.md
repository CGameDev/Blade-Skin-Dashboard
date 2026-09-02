# Phase G Game Library Contract

## Scope

This checkpoint prepares testing-cadence gate 3: an installed loose-title is
shown by the approved BladeDash game-list presentation and launches through a
Blade-owned standalone service. It does not approve the remaining game views,
metadata, artwork, favorites, sorting, Game Controls actions, or visual
fidelity.

The approved frontend remains unmodified.

## Inspected resources

XuiTool was used only to save ignored XML inspection copies of the approved
compiled resources:

```text
Approved source: references/local/BladeDash(2005)/gamelist.xur
Inspection copy: build/milestone000/xui-inspection/gamelist-approved-inspected.xui
Inspection bytes: 102812
Inspection SHA-256: 7ec08e8784745c79195a3e213e956883d783cf475b9db8ee92212625cd4f0450

Approved source: references/local/BladeDash(2005)/GameControls.xur
Inspection copy: build/milestone000/xui-inspection/GameControls-approved-inspected.xui
Inspection bytes: 41120
Inspection SHA-256: 92e290fb0b8b11d287b24da991774e028da00e4b2c5d18eb1e1bf9c5320beb93
```

No approved XUR was edited or recompiled.

## Main-scene entry contract

The five approved `main.xur` category controls are:

| Control ID | Visible text | Authored action |
|---|---|---|
| `XBox360Games` | `Xbox 360` | A / `PressPath=xbox360.xur` |
| `XBoxLiveArcade` | `Xbox Live Arcade` | A / `PressPath=xbox360.xur` |
| `XBox1Games` | `Xbox Clássico` | A / `PressPath=xbox360.xur` |
| `Emulators` | `Emuladores` | A / `PressPath=xbox360.xur` |
| `Homebrew` | `Homebrew` | A / `PressPath=xbox360.xur` |

`xbox360.xur` is absent from the approved package. This is an observed
`FSD_HOST_CONTRACT`/`REFERENCE_GAP`: the original executable selected a game
category and supplied or redirected the game-list view. The standalone host
must intercept those exact controls and navigate to the supplied
`gamelist.xur`; it must not fabricate a replacement `xbox360.xur`.

## `gamelist.xur` contract used by this checkpoint

- 1280x720 canvas; root ID `Main Scene`.
- Root default focus: `GameListScene\Tab2\GameList`.
- `GameListScene` is a five-tab `XuiTabScene` with authored default tab 2 and
  class override `ScnGameView`. This outermost use requires the standalone
  compatibility class to derive from/register as `XuiTabScene`; revision 2's
  plain-scene registration was rejected on hardware with
  `XUI_ERR_CAST_FAILED` (`0x80300016`).
- `Tab2` has default focus `GameList` and class override `ScnGameView`.
- `GameList` is an `XuiList` with class override `GamesList` and visual
  `ListBox_GamesList`.
- `TextGameListCounter` has authored text `1 de 1`.
- `ButtonLaunchGame` is the unfocused-input A action with text `Jogar`.
- `ButtonBack` is the B action with text `Voltar`.
- `ButtonShowOptions` is the Y action with text `Opções`, stays visible, and
  targets supplied `GameControls.xur`.
- `ScnCanvasPresenter`, `ScnGameView`, and `GamesList` are the only class
  overrides used by this resource.

For gate 3, data association 0 of `GamesList` is bound to the installed-title
display name. Other text/image associations remain empty rather than receiving
invented metadata or artwork.

### Title typeface host contract

The approved `ListBox_GamesList` visual uses `Button_GameList`; its main-title
and subtitle presenters explicitly request `ConsoleFont`. There are 188
explicit `<Font>ConsoleFont</Font>` references in the approved `skin.xui`.

Matching original Freestyle source confirms both sides of this contract:

- `Application/FreestyleUIApp.cpp` registers the default typeface under the
  exact name `ConsoleFont` from `file://flash:\xenonjklatin.xtt`;
- `Tools/GameContent/GameContentTypes.h` defines `FSDTEXT_MAINTITLE` as 0;
- `Scenes/GameView/GameList/GamesList.cpp` returns a main title only for
  item-data requests with association 0.

Revision 3 proved a populated five-item list through its `1 de 5` counter, but
the row titles were blank because the standalone host had only registered an
Arial default. Revision 4 then proved that making the original system
`ConsoleFont` the standalone global default removes every rendered text glyph,
despite successful descriptor registration. It also captured the actual
standalone source request as association 0 with `item_data=0`; copying the
original FSD item-data guard rejected that valid request.

Revision 5 restores the R3-proven Arial global default and registers
`ConsoleFont` as a non-default alias to that same supplied font. Association 0
is served for an in-range list index regardless of the item-data flag, and the
flag remains in diagnostics. This is an evidence-scoped compatibility
difference from FSD, not a guessed field. No approved XUR or typeface asset is
modified.

At the owner's explicit direction, an English runtime-localization pass updates
known text properties on the instantiated approved `main.xur` and
`gamelist.xur` object trees. It does not edit/recompile either resource; the
package validator still requires all 1,139 approved file hashes to match.

## `GameControls.xur` boundary

The supplied scene has root default focus
`GameControls\GameControls\GameScreenshots`. Its only class override is
`ScnGameControls`; the scene contains the existing screenshots, achievements,
saves, title-update, trainer, artwork, move, delete, and rename controls.

This checkpoint registers the exact class façade so the supplied scene can be
loaded later, but does not bind those actions. They remain gated by their own
contract/provenance work and must not call dead FSD services.

## Standalone service boundary

```text
approved main/gamelist XUI
        |
FSD compatibility classes (ScnMain, ScnGameView, GamesList)
        |
BladeGameLibraryAdapter
        |
InstalledGameService + LaunchService
        |
Xbox filesystem + XLaunchNewImage
```

Filesystem enumeration runs on the existing background queue, never the
render/input thread. The service accepts developer-editable scan roots from
`Config/library_roots.txt`. If that file is absent or has no valid entries,
conservative local-device defaults are used. A directory is a launchable entry
only when a loose `default.xex` or, for Xbox Classic, `default.xbe` is present.

Container-only XBLA content is not claimed as launchable. It remains a
technical/service gap until an approved title-launcher/content API is mapped.

## Console gate

Revision 5 satisfied the functional acceptance conditions on 2026-09-02:

1. the approved main shell still renders and all five Blades still navigate;
2. selecting `Xbox 360` opens the supplied `gamelist.xur`;
3. at least one configured loose title appears by folder/display name;
4. list navigation changes selection and the counter follows it;
5. A / `Jogar` queues the selected path, shuts the Blade host down cleanly,
   and dispatches `XLaunchNewImage`;
6. B returns from the list to the main shell;
7. the persistent log contains scan, category, scene, selection, and launch
   evidence with no failed HRESULT.

Matched game-list captures and the original known-good FSD behavior are still
required before visual/interaction fidelity can be approved. English
localization is also incomplete: six game-list command labels remain in
Portuguese even though list headings, item titles, counters and metadata
placeholders are English.
