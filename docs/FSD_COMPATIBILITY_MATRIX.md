# BladeDash/FSD Compatibility Matrix

## Status

**Initial Milestone 000 inventory — incomplete.**

Source authority is the verified approved `BladeDash(2005)` extraction. This
matrix records observed configuration contracts and resource names without
inventing unverified fields or behavior. `UNKNOWN` means the supplied compiled
resource still needs control/event inspection; it is not permission to redesign
or replace that resource.

Compatibility façade and adapter names below are implementation directions, not
claims that those classes already exist.

## Host concepts observed in `skin.xml`

| Blade resource/scene | Control/instance identifier | Observed FSD contract and fields | Compatibility façade | Blade adapter | Underlying service direction | Provenance | Classification | Status/limitation |
|---|---|---|---|---|---|---|---|---|
| CoverFlow / `gamelist_coverflow.xur` | `CoverFlow` | `SHADERPATH`, `FULLCOVERMESH`, `FRONTCOVERMESH`, `TEXTUREPATH` | `BladeCoverFlowHost` | `BladeLibraryAdapter` | Library/artwork presentation models + XUI renderer | No backend code reused; CCLOS snapshot `e8440b6` reserved | `FSD_HOST_CONTRACT` | Configured shader, meshes and texture directory resolve; list/data/event contract is `UNKNOWN` |
| Video manager / media resources | `VideoManager` | `VIDEOICONPATH` | `BladeVideoManagerHost` | `BladeMediaAdapter` | Xbox media playback + approved CCLOS Watch TV/media services | No backend code reused | `FSD_HOST_CONTRACT` | Icon resolves; playback/events are `UNKNOWN` |
| `Achievements.xur` | `AchievementManager` | `MISSINGACHIEVEMENTPATH`, `SECRETACHIEVEMENTTEXT` | `BladeAchievementHost` | `BladeAchievementAdapter` | Xbox/CCLOS achievement service | No backend code reused | `FSD_HOST_CONTRACT` | Missing-art path resolves; list fields/events are `UNKNOWN` |
| HTTP/WebUI | `HTTPServer` | `ROOTPATH=wwwroot` | `BladeHttpServerHost` | `BladeHttpAdapter` | Optional Blade-owned HTTP service | No backend code reused | `FSD_HOST_CONTRACT` | Static root exists; retain only if a real standalone service is intentionally enabled |
| Main game view | `ScnGameView` / `Captions` | `DEFAULT`, `XBOX360`, `XBLA`, `XBOXCLASSIC`, `HOMEBREW`, `EMULATORS`, `HIDDEN`; `main.xur` category IDs all target absent `xbox360.xur`; supplied `GameListScene` is an `XuiTabScene` with `ScnGameView` override | `ScnGameView` tab-scene compatibility class + exact main-category interception and controller-edge fallback | `BladeGameLibraryAdapter` | Background library discovery/category presentation; standalone device aliases | CCLOS `StoreMain.cpp` loose-image discovery/launch semantics and `main.cpp` storage-mount boundary at `e8440b6`, adapted behind Blade-owned services | `FSD_HOST_CONTRACT` | R5 functionally proves exact-ID routing into supplied `gamelist.xur`, standard storage aliases, category filtering and return to the main shell. Missing `xbox360.xur` remains an explicit host redirect gap; supplied `gamelist.xur` is the target, not a recreated scene |
| Game lists / `gamelist*.xur` | `GamesList` / `GameList`; source IDs `ListBox_GamesList`, `ListBox_GamesList_Covers`, `ListBox_GamesList_Banners` | `GameList` default focus; title data association 0; `TextGameListCounter`; A `ButtonLaunchGame`; B `ButtonBack`; Y `ButtonShowOptions` -> `GameControls.xur`; missing/loading artwork and favorite/rating paths | `GamesList` + `ScnGameView` | `BladeGameLibraryAdapter` | `InstalledGameService`, metadata/cache/artwork later, `LaunchService` | CCLOS `StoreMain.cpp` lines 241-245 and 880 adapted for bounded loose `default.xex`/`default.xbe` discovery and launch | `FSD_HOST_CONTRACT` | R5 functional Gate 3 passed with five emulator and seven homebrew rows, selection/counters, B return, orderly shutdown and SNES launch. Six Portuguese command labels plus metadata, artwork, sort/favorites behavior and secondary layouts remain open |
| File list | `FilesList` / `FileList` | `STANDARDFILEPATH`, `STANDARDFOLDERPATH` | `BladeFilesListHost` | `BladeFileSystemAdapter` | Xbox filesystem service | No backend code reused | `FSD_HOST_CONTRACT` | Configured icons resolve; enumeration/event contract is `UNKNOWN` |
| Title Update list / `TitleUpdateManager.xur` | `ActiveTUList` | `ACTIVETUPATH`, `DISABLEDTUPATH` | `BladeTitleUpdateListHost` | `BladeTitleUpdateAdapter` | CCLOS Title Update service + Xbox content APIs | No backend code reused | `FSD_HOST_CONTRACT` | Both configured icons resolve; TU schema/actions are `UNKNOWN` |
| Dual-pane source file list | `SrcFilesList` / `SrcFileList` | standard and selected file/folder paths | `BladeSourceFilesListHost` | `BladeFileSystemAdapter` | Xbox filesystem service | No backend code reused | `FSD_HOST_CONTRACT` | All configured icons resolve; selection/copy events are `UNKNOWN` |
| Dual-pane destination file list | `DestFilesList` / `DestFileList` | standard and selected file/folder paths | `BladeDestinationFilesListHost` | `BladeFileSystemAdapter` | Xbox filesystem service | No backend code reused | `FSD_HOST_CONTRACT` | All configured icons resolve; destination/copy events are `UNKNOWN` |
| `PathManager.xur`, `pickpath.xur` | `PathList` | `STANDARDFOLDERPATH` | `BladePathListHost` | `BladeFileSystemAdapter` | Xbox filesystem/config service | No backend code reused | `FSD_HOST_CONTRACT` | Folder icon resolves; path CRUD/events are `UNKNOWN` |
| Profile/avatar resources | `ScnProfile`: `ProfileScene`, `GamerPic` | `GAMERPICDISPLAYER`, `MISSINGRECENT`, `PLAYERID`, `HIDEMODE` | `BladeProfileHost` | `BladeProfileAdapter` | Xbox profile/gamerpic APIs | No backend code reused | `PLATFORM_SERVICE` | Missing recent-game art resolves; binding/event behavior is `UNKNOWN` |
| Popup presentation | `ScnPopup`: `StatisticsPopup`, `WeatherPopup`, `CustomizeTabPopUp` | `POPUPID`, `HIDEMODE`, `INITSHOWN` | `BladePopupHost` | Feature-specific adapters | Presentation state + underlying feature service | No backend code reused | `FSD_HOST_CONTRACT` | Popup identity/visibility fields observed; transitions/events are `UNKNOWN` |
| System info | `ScnSysInfo` / `TopStatsBar` | temperature/storage override flags, unmounted behavior, percent/value/unit location | `BladeSystemInfoHost` | `BladeSystemAdapter` | Xbox thermal, storage and system APIs | No backend code reused | `PLATFORM_SERVICE` | Configuration observed; data update cadence and units are `UNKNOWN` |
| Custom tab presenter | `ScnTabPresenter`: `CustomMenuItem`, `CustomPreviewItem` | `PRESENTER=ACTIVE/PREVIEW`; exact class is the sole `ClassOverride` in source XUI (38 uses) | `ScnTabPresenter` minimal scene façade | Feature-specific adapters | Presentation models | No backend code reused | `FSD_HOST_CONTRACT` | Revision 1 `LoadSkin` failed with `XUI_ERR_CLASS_NOTREG`; exact class registration implemented in revision 2; item schema/focus transitions remain `UNKNOWN` |
| Splash host / `SplashScreen.xur` | `ScnSplashScreen`: `XuiScene1`; `XuiImage2`; `XuiImage1`; `LoadingStatus` | Root class override; 1280x720 scene; `fond.png` and `splash.dds`; `EnableEffects=true` on scene and both image layers; `stop` named frame at 120 | `ScnSplashScreen` minimal scene façade | Milestone 000 host diagnostics only | XUI effects pre-render, backbuffer view transform and resource loader | No backend code reused | `FSD_HOST_CONTRACT` | Gate E passed: revision 6 fills the complete 16:9 output and two logged runs prove resource loads, presentation, clean Back exit and boot persistence |
| Team/avatar scene | `ScnTeamFSD` / `Avatar` | resolution, walk-in, error visibility, player index, shadow, autorotate, animation index, rotation | `BladeAvatarHost` | `BladeProfileAdapter` | Xbox avatar/profile APIs | No backend code reused | `PLATFORM_SERVICE` | Configuration observed; avatar object/event contract is `UNKNOWN` |
| Weather | `ScnWeather` / `Weather` | `MOONBASEPATH`, `TYPEBASEPATH`, `FILETYPE` | `BladeWeatherHost` | `BladeWeatherAdapter` | No approved real replacement selected | No backend code reused | `DEFERRED` | Artwork roots resolve; obsolete-service replacement requires evaluation/owner decision |

## Compiled-resource inventory and service direction

| Resource group | Supplied XURs | Expected role | Classification | Status/limitation |
|---|---|---|---|---|
| Core presentation | `skin.xur`, `main.xur`, `canvasconfig.xur`, `menuconfig.xur`, `options.xur`, `customizetab.xur` | Main scene graph, Blade navigation/configuration and common presentation | `BLADEDASH_DEFINED` | Root is `MainScene`; `tab1` is `ScnMain` with five tabs, authored default tab 3/default focus `Tab3`; Gate F hardware evidence proves presentation and navigation through zero-based runtime indices 0–4 |
| Game library | `gamelist.xur`, `gamelist_banners.xur`, `gamelist_cover.xur`, `gamelist_coverflow.xur`, `gamelist_icon.xur`, `gameinfo.xur`, `GameControls.xur`, `savedgames.xur`, `screenshots.xur` | Library views, details, controls, saved games and screenshots | `FSD_HOST_CONTRACT` | Gate-3 contract for `gamelist.xur` and the `GameControls.xur` class boundary is extracted in `PHASE_G_GAME_LIBRARY_CONTRACT.md`; other views/actions remain unbound |
| Achievements | `Achievements.xur` | Existing Blade achievements presentation | `FSD_HOST_CONTRACT` | Backend direction fixed; XUR contract not yet extracted |
| Title Updates | `TitleUpdateManager.xur` | Existing Blade TU presentation | `FSD_HOST_CONTRACT` | Backend direction fixed; XUR contract not yet extracted |
| Trainers | `Trainers.xur` | Existing Blade trainer presentation | `FSD_HOST_CONTRACT` | Backend direction fixed; XUR contract not yet extracted |
| Disc copy | `CopyDVD.xur` | Existing Blade CopyDVD presentation | `CONSOLECRATE_REUSABLE_BACKEND` | Must map to CCLOS Disc-to-GOD behind `BladeDiscCopyAdapter`; no code reused yet |
| Files/path operations | `DualPane.xur`, `filemanager.xur`, `filemanager2.xur`, `filemanager3.xur`, `filemanager4.xur`, `filemanager5.xur`, `fileop.xur`, `PathManager.xur`, `pickpath.xur` | File browser, operations and path selection | `PLATFORM_SERVICE` | Preserve scenes; control/data/action contracts not yet extracted |
| Profile/avatar | `avatar.xur` | Gamer profile/avatar presentation | `PLATFORM_SERVICE` | Xbox API feasibility and exact bindings not yet mapped |
| Media/music/video | `music.xur`, `main_music01.xur` through `main_music10.xur`, `WmvPlayer.xur` | Existing Blade Media Center/music/video presentation | `FSD_HOST_CONTRACT` | Preserve UI; CCLOS Watch TV may only enter through Blade media adapter; playback contracts not yet extracted |
| Settings | `Settings_Main.xur`, `Settings_Content.xur`, `Settings_General.xur`, `Settings_Plugin.xur`, `Settings_Plugin1.xur`, `Settings_System.xur`, `ChooseSkins.xur` | Existing settings/skin/plugin presentation | Mixed | Plugin-era actions require service-by-service classification; no dead calls may remain |
| Weather | `Weather.xur`, `WeatherScene.xur` | Existing weather presentation | `DEFERRED` | No fake backend; use existing unavailable state or obtain owner decision if no real service is approved |
| Legacy network/update | `GetCredentials.xur`, `LiNKVerify.xur`, `updater.xur` | FSD-era credentials, LiNK verification and updater flows | `DEFERRED` | Do not call obsolete JQE/FSD infrastructure; real replacement or existing unavailable state required |
| Utility/diagnostic presentation | `SplashScreen.xur`, `Wait.xur`, `utilities.xur`, `utilities_hud.xur`, `TeamFSD.xur` | Splash/wait/utility/about or team scenes | Mixed | Branding exception applies to visible author/skin credits; exact controls/actions need inspection |

The extraction contains 58 root-level XUR files. No supplied XUR is to be removed
merely because its FSD contract is not implemented yet.

Phase E now has a console-validated standalone host for the supplied
`SplashScreen.xur`. Revision 6 capture, two-run log and settings evidence prove
full-frame presentation, clean Back exit and Blade-owned persistence. Gate E is
passed; this does not yet prove the main scene or remaining FSD contracts.

## Approved `main.xur` contract extracted for Phase F

XuiTool saved an ignored XML inspection copy without changing the approved XUR.
Observed root/navigation facts:

- 1280x720 canvas;
- root `XuiTabScene`: ID `MainScene`, override `MainScene`, default focus
  `tab1`;
- nested `XuiTabScene`: ID `tab1`, override `ScnMain`, `TabCount=5`,
  `DefaultTab=3`, default focus `Tab3`;
- 12 distinct class overrides: `MainScene`, `ScnMain`,
  `ScnCanvasPresenter`, `ScnPopup`, `ScnWeather`, `ScnSysInfo`,
  `ScnTabPresenter`, `ScnProfile`, `ScnAvatar`, `ScnChooseSkin`,
  `ScnKinectVoice`, and `KinectCommandList`;
- authored element bases establish three new tab-scene façades, seven new scene
  façades and one new list façade, plus the already proven scene-based
  `ScnTabPresenter`;
- `main.xur` directly references 34 unique image/audio paths; 32 resolve and
  two are absent from the approved package.

The initial implementation supplies registration/base-class compatibility only.
The 2026-09-02 Gate F hardware run proved scene initialization, first-frame
presentation, the five-tab host, focus reporting and navigation through all
runtime tab indices. It logged an initial `current=2`, showing that authored
`DefaultTab=3` is exposed through a zero-based runtime index. Observed focus IDs
included `XBox360Games`, `Button2`, `Settings`, `legend_a`,
`control_ListItem`, and `ProfileSignIn`. Back produced orderly shutdown and no
failure marker was present. Original FSD data/action messages and exact
input/transition decisions remain `UNKNOWN`; a matched visual-capture set also
remains required for fidelity grading.

## Resource-host dependencies already exposed

- Four source references use `sharedres://` (`btn_Focus.xma`,
  `btn_InactiveSelect.xma`, `btn_Select.xma`, `ico_64x_Console.png`). The
  standalone host must provide compatible shared-resource resolution or map these
  references without changing visible behavior.
- `skin.xml` declares `Font/ERASBD.TTF`, which is absent from the approved ZIP.
  The working FSD environment may have supplied a fallback/shared font. This is an
  `UNKNOWN` host contract, not authorization to substitute a font.
- Independently, the approved `skin.xui` explicitly requests `ConsoleFont` in
  188 presenters. Matching original Freestyle source proves it is the host's
  default typeface name and uses the Xbox system `xenonjklatin.xtt`. Revision 4
  hardware proved that locator yields no visible glyphs when made global in
  this standalone host. Revision 5 restores the renderable supplied Arial
  default and registers `ConsoleFont` as an alias. This functional bridge is
  not font-fidelity approval and does not resolve the separate missing
  `ConsoleFonts`/ERASBD skin-extension contract.
- Source XUI contains 28 other missing local paths and one path to a former
  developer desktop. They require reachability/use analysis before any repair.
- The configured CoverFlow shader, meshes, mesh-texture directory and configured
  DDS/image placeholders all resolve in the approved extraction.
- Approved `skin.xui` contains 181 `XuiSoundXAudio` objects. Revision 2 proved
  that `ScnTabPresenter` registration alone was insufficient; revision 3 now
  uses the XDK-provided `XuiSoundXAudioRegister()`/unregister lifecycle required
  by XDK sample skins with this element type.
- Approved `SplashScreen.xur` declares `ScnSplashScreen` and enables effects on
  its scene plus both full-screen image layers. A basic `CXuiModule::Init` host
  does not activate `m_bUsingEffects`; revision 5 explicitly enables that
  inherited helper-loop flag after successful standalone initialization so the
  standard XUI run loop performs `PreRender`.

## Current game-library gate

The approved `main.xur` console probe is complete for functional Gate F, and
the `gamelist.xur`/`GameControls.xur` contracts have been extracted for the
Gate-3 subset. Phase G revision 2 proved the exact-ID controller fallback, then
failed at the now-decoded `ScnGameView` tab-scene cast and exposed absent
standalone storage aliases. Revision 3 corrects both observed contracts. Any
value not observed in the approved source or working runtime remains `UNKNOWN`
or `REFERENCE_GAP`. Revision 3 hardware then proved all five category scenes
and a populated five-row list, but titles were blank. Revision 4 removed global
text and exposed the standalone `item_data=0` callback while discovering 13
launchables. Revision 5 restores visible list text, serves that request and
adds exact category/path diagnostics. Its hardware run proves populated list
binding/navigation and clean selected-image launch. Six command labels remain
Portuguese; this is a localization gap rather than a failed library contract.
