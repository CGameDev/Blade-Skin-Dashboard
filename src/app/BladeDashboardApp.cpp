#include "app/BladeDashboardApp.h"

#include "compatibility/MainSceneCompatibility.h"
#include "compatibility/ScnTabPresenter.h"
#include "diagnostics/DebugLog.h"

#include <stdio.h>

namespace Blade
{
namespace App
{

namespace
{
const char ApprovedSkinFilePath[] =
    "game:\\Skins\\BladeDash(2005)\\skin.xur";
const char ApprovedSceneFilePath[] =
    "game:\\Skins\\BladeDash(2005)\\main.xur";
const char ApprovedGameListFilePath[] =
    "game:\\Skins\\BladeDash(2005)\\gamelist.xur";
const char ApprovedGameControlsFilePath[] =
    "game:\\Skins\\BladeDash(2005)\\GameControls.xur";
const char ApprovedDefaultTypefaceFilePath[] =
    "game:\\Skins\\BladeDash(2005)\\Font\\arial.ttf";
const char MissingApprovedBootLogoPath[] =
    "game:\\Skins\\BladeDash(2005)\\img-Xbox360Logo_Stacked.png";
const char MissingApprovedWeatherIconPath[] =
    "game:\\Skins\\BladeDash(2005)\\Images\\Interface\\Weather\\Type\\25.png";

const WCHAR ApprovedSkinLocator[] =
    L"file://game:/Skins/BladeDash(2005)/skin.xur";
const WCHAR ApprovedSceneBase[] =
    L"file://game:/Skins/BladeDash(2005)/";
const WCHAR ApprovedSceneFile[] = L"main.xur";
const WCHAR ApprovedDefaultTypefaceName[] = L"Arial";
const WCHAR ConsoleTypefaceAliasName[] = L"ConsoleFont";
const WCHAR ApprovedDefaultTypefaceLocator[] =
    L"file://game:/Skins/BladeDash(2005)/Font/arial.ttf";
const float ApprovedCanvasWidth = 1280.0f;
const float ApprovedCanvasHeight = 720.0f;

struct EnglishTextReplacement
{
    LPCWSTR source;
    LPCWSTR replacement;
};

const EnglishTextReplacement EnglishTextReplacements[] =
{
    { L"Jogos", L"Games" },
    { L"Clima", L"Weather" },
    { L"Temas", L"Themes" },
    { L"Sistema", L"System" },
    { L"M\x00ED" L"dia", L"Media" },
    { L"Selecionar", L"Select" },
    { L"Configura\x00E7" L"\x00F5" L"es", L"Settings" },
    { L"Copiar DVD", L"Copy DVD" },
    { L"Gerenciador de Arquivos", L"File Manager" },
    { L"Informa\x00E7" L"\x00F5" L"es de sistema", L"System Information" },
    { L"Abrir/Fechar bandeja", L"Open/Close Tray" },
    { L"Abrir/Fechar Bandeja", L"Open/Close Tray" },
    { L"Hud esquerdo", L"Left HUD" },
    { L"Hud Esquerdo", L"Left HUD" },
    { L"Hud Direito", L"Right HUD" },
    { L"jogado recentemente", L"recently played" },
    { L"  Temperaturas", L"  Temperatures" },
    { L"  Memoria", L"  Memory" },
    { L"DATA", L"DATE" },
    { L"HORA", L"TIME" },
    { L"Player de v\x00ED" L"deo WMV ", L"WMV Video Player" },
    { L"Musica", L"Music" },
    { L"Emuladores", L"Emulators" },
    { L"Xbox Cl\x00E1" L"ssico", L"Xbox Classic" },
    { L"Voltar", L"Back" },
    { L"Op\x00E7" L"\x00F5" L"es", L"Options" },
    { L"Favoritos", L"Favorites" },
    { L"Jogar", L"Play" },
    { L"N\x00E3o Dispon\x00EDvel", L"Not Available" },
    { L"N\x00E3o Disponivel", L"Not Available" },
    { L"N/D", L"N/A" },
    { L"Avaliadores:", L"Raters:" },
    { L"Avalia\x00E7\x00E3o:", L"Rating:" },
    { L"Data de Lan\x00E7" L"amento:\r\n", L"Release Date:\r\n" },
    { L"Dire\x00E7\x00E3o", L"Direction" },
    { L"Tipo de classifica\x00E7\x00E3o", L"Sort Type" },
    { L"Alternar legenda", L"Toggle Subtitle" },
    { L"Alternar Favorito", L"Toggle Favorite" },
    { L"Classifica\x00E7\x00E3o Alta", L"Highest Rated" },
    { L"Classifica\x00E7\x00E3o baixa", L"Lowest Rated" },
    { L"Ordenar", L"Sort" },
    { L"Menu Favoritos", L"Favorites Menu" },
    { L"Controles do Jogo", L"Game Controls" },
    { L"Jogos de Xbox 360", L"Xbox 360 Games" },
    { L"Jogos de Xbox Classico", L"Xbox Classic Games" },
    { L"Gerenciar Atualiza\x00E7\x00F5" L"es", L"Manage Title Updates" },
    { L"Gerenciar Trainers", L"Manage Trainers" },
    { L"Atualizar Arte", L"Refresh Artwork" },
    { L"Mover Jogo", L"Move Game" },
    { L"Nome do jogo", L"Game Name" },
    { L"Sem sele\x00E7\x00E3o", L"No Selection" },
    { L"Deletar", L"Delete" },
    { L"Renomear", L"Rename" },
    { L"Condi\x00E7\x00F5" L"es atuais", L"Current Conditions" },
    { L"Previs\x00E3o", L"Forecast" },
    { L"Humidade : N/D", L"Humidity: N/A" },
    { L"Status Atual", L"Current Status" },
    { L"Carca\x00E7" L"a", L"CASE" },
    { L"Validar", L"Apply" },
    { L"Customizar Skin", L"Customize Skin" },
    { L"Vers\x00E3o", L"Version" },
    { L"Vers\x00E3o:", L"Version:" },
    { L"Autor", L"Author" },
    { L"Autor:", L"Author:" },
    { L"Nome da Skin", L"Skin Name" }
};

LPCWSTR FindEnglishReplacement( LPCWSTR source )
{
    if( source == NULL || source[ 0 ] == L'\0' )
        return NULL;

    for( DWORD index = 0; index < ARRAYSIZE( EnglishTextReplacements ); ++index )
    {
        if( wcscmp( source, EnglishTextReplacements[ index ].source ) == 0 )
            return EnglishTextReplacements[ index ].replacement;
    }
    return NULL;
}

HRESULT ApplyEnglishText( HXUIOBJ object, DWORD& replacementCount )
{
    if( object == NULL )
        return E_INVALIDARG;

    HRESULT firstFailure = S_OK;
    const HXUICLASS textClass = XuiFindClass( XUI_CLASS_TEXT );
    const HXUICLASS controlClass = XuiFindClass( XUI_CLASS_CONTROL );
    const HXUICLASS listClass = XuiFindClass( XUI_CLASS_LIST );

    if( textClass != NULL && XuiIsInstanceOf( object, textClass ) )
    {
        const LPCWSTR replacement = FindEnglishReplacement(
            XuiTextElementGetText( object ) );
        if( replacement != NULL )
        {
            const HRESULT result = XuiTextElementSetText( object, replacement );
            if( SUCCEEDED( result ) )
                ++replacementCount;
            else
                firstFailure = result;
        }
    }
    else if( controlClass != NULL && XuiIsInstanceOf( object, controlClass ) &&
        ( listClass == NULL || !XuiIsInstanceOf( object, listClass ) ) )
    {
        const LPCWSTR replacement = FindEnglishReplacement(
            XuiControlGetText( object ) );
        if( replacement != NULL )
        {
            const HRESULT result = XuiControlSetText( object, replacement );
            if( SUCCEEDED( result ) )
                ++replacementCount;
            else
                firstFailure = result;
        }
    }

    HXUIOBJ child = NULL;
    if( FAILED( XuiElementGetFirstChild( object, &child ) ) )
        return firstFailure;

    while( child != NULL )
    {
        const HRESULT childResult = ApplyEnglishText( child, replacementCount );
        if( FAILED( childResult ) && SUCCEEDED( firstFailure ) )
            firstFailure = childResult;

        HXUIOBJ next = NULL;
        if( FAILED( XuiElementGetNext( child, &next ) ) )
            break;
        child = next;
    }

    return firstFailure;
}

void LocalizeSceneToEnglish( HXUIOBJ scene, const char* sceneName )
{
    DWORD replacementCount = 0;
    const HRESULT result = ApplyEnglishText( scene, replacementCount );

    char message[ 192 ];
    sprintf_s(
        message,
        ARRAYSIZE( message ),
        "English text compatibility applied: scene=%s replacements=%u result=0x%08X.",
        sceneName != NULL ? sceneName : "<unknown>",
        static_cast< unsigned int >( replacementCount ),
        static_cast< unsigned int >( result ) );
    Diagnostics::Write( message );
}

HRESULT VerifyFile( const char* path )
{
    const DWORD attributes = GetFileAttributesA( path );
    if( attributes == static_cast< DWORD >( -1 ) )
        return HRESULT_FROM_WIN32( GetLastError() );
    if( ( attributes & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
        return E_INVALIDARG;
    return S_OK;
}

void LogElementTree( HXUIOBJ object, DWORD depth, DWORD& objectCount )
{
    if( object == NULL || depth > 4 || objectCount >= 32 )
        return;

    ++objectCount;

    LPCWSTR id = L"<none>";
    if( FAILED( XuiElementGetId( object, &id ) ) || id == NULL || id[ 0 ] == L'\0' )
        id = L"<none>";

    LPCWSTR className = L"<unknown>";
    const HXUICLASS objectClass = XuiGetObjectClass( object );
    if( objectClass != NULL )
    {
        XUIClass classInfo;
        ZeroMemory( &classInfo, sizeof( classInfo ) );
        classInfo.cbSize = sizeof( classInfo );
        if( SUCCEEDED( XuiGetClass( objectClass, &classInfo ) ) &&
            classInfo.szClassName != NULL )
        {
            className = classInfo.szClassName;
        }
    }

    float width = 0.0f;
    float height = 0.0f;
    float opacity = 0.0f;
    const HRESULT boundsResult = XuiElementGetBounds( object, &width, &height );
    const HRESULT opacityResult = XuiElementGetOpacity( object, &opacity );

    char message[ 320 ];
    sprintf_s(
        message,
        ARRAYSIZE( message ),
        "Scene node depth=%u class=%ls id=%ls shown=%u bounds=%s%.1fx%.1f opacity=%s%.3f.",
        static_cast< unsigned int >( depth ),
        className,
        id,
        XuiElementIsShown( object ) ? 1u : 0u,
        SUCCEEDED( boundsResult ) ? "" : "unavailable/",
        width,
        height,
        SUCCEEDED( opacityResult ) ? "" : "unavailable/",
        opacity );
    Diagnostics::Write( message );

    HXUIOBJ child = NULL;
    if( FAILED( XuiElementGetFirstChild( object, &child ) ) )
        return;

    while( child != NULL && objectCount < 32 )
    {
        LogElementTree( child, depth + 1, objectCount );

        HXUIOBJ next = NULL;
        if( FAILED( XuiElementGetNext( child, &next ) ) )
            break;
        child = next;
    }
}

void GetElementIdentity(
    HXUIOBJ object,
    LPCWSTR* id,
    LPCWSTR* className )
{
    *id = L"<none>";
    *className = L"<unknown>";

    if( object == NULL )
        return;

    LPCWSTR resolvedId = NULL;
    if( SUCCEEDED( XuiElementGetId( object, &resolvedId ) ) &&
        resolvedId != NULL && resolvedId[ 0 ] != L'\0' )
    {
        *id = resolvedId;
    }

    const HXUICLASS objectClass = XuiGetObjectClass( object );
    if( objectClass != NULL )
    {
        XUIClass classInfo;
        ZeroMemory( &classInfo, sizeof( classInfo ) );
        classInfo.cbSize = sizeof( classInfo );
        if( SUCCEEDED( XuiGetClass( objectClass, &classInfo ) ) &&
            classInfo.szClassName != NULL )
        {
            *className = classInfo.szClassName;
        }
    }
}

HRESULT SetApprovedCanvasView(
    HXUIDC deviceContext,
    float scaleX,
    float scaleY,
    D3DXMATRIX& originalView )
{
    HRESULT result = XuiRenderGetViewTransform( deviceContext, &originalView );
    if( FAILED( result ) )
        return result;

    D3DXMATRIX scaledView;
    D3DXMatrixScaling( &scaledView, scaleX, scaleY, 1.0f );
    return XuiRenderSetViewTransform( deviceContext, &scaledView );
}

LPCWSTR GetGameCategoryControlId( Models::GameCategory category )
{
    switch( category )
    {
        case Models::GameCategoryXbox360:
            return L"XBox360Games";
        case Models::GameCategoryXboxLiveArcade:
            return L"XBoxLiveArcade";
        case Models::GameCategoryXboxClassic:
            return L"XBox1Games";
        case Models::GameCategoryEmulators:
            return L"Emulators";
        case Models::GameCategoryHomebrew:
            return L"Homebrew";
        default:
            return L"<unknown>";
    }
}
}

BladeDashboardApp::BladeDashboardApp()
    : m_gameLibraryAdapter( m_installedGameService, m_launchService ),
      m_xuiInitialized( FALSE ),
      m_servicesStarted( FALSE ),
      m_gameScanReported( FALSE ),
      m_approvedScene( NULL ),
      m_activeGameListScene( NULL ),
      m_mainTabHost( NULL ),
      m_lastFocusedObject( NULL ),
      m_mainSceneClassRegistrationMask( 0 ),
      m_gameLibraryClassRegistrationMask( 0 ),
      m_lastMainTab( static_cast< UINT >( -1 ) ),
      m_navigationStateReported( FALSE ),
      m_preRenderFailureReported( FALSE ),
      m_renderFailureReported( FALSE ),
      m_firstFrameReported( FALSE ),
      m_categoryRequestReceivedThisFrame( FALSE ),
      m_lastVisibleGameSelection( static_cast< DWORD >( -1 ) ),
      m_lastGameCategoryRequestTick( 0 ),
      m_lastRequestedGameCategory( Models::GameCategoryCount ),
      m_pendingGameCategory( -1 ),
      m_backBufferWidth( 0 ),
      m_backBufferHeight( 0 ),
      m_viewScaleX( 1.0f ),
      m_viewScaleY( 1.0f )
{
}

BladeDashboardApp::~BladeDashboardApp()
{
    Shutdown();
}

HRESULT BladeDashboardApp::Initialize()
{
    HRESULT result = m_navigation.Reset( Navigation::SceneMainBladeShell );
    if( FAILED( result ) )
        return result;

    result = m_controllerInput.Start();
    if( FAILED( result ) )
        return result;

    result = m_storageAliasService.Start();
    if( FAILED( result ) )
    {
        m_controllerInput.Stop();
        return result;
    }

    result = m_backgroundQueue.Start();
    if( FAILED( result ) )
    {
        m_storageAliasService.Stop();
        m_controllerInput.Stop();
        return result;
    }
    m_servicesStarted = TRUE;

    m_installedGameService.Reset();
    result = m_backgroundQueue.Enqueue( ScanInstalledGames, this );
    if( FAILED( result ) )
        Diagnostics::WriteFailure( "Installed-game background scan enqueue", result );

    result = m_settingsStore.Load();
    if( FAILED( result ) )
        Diagnostics::WriteFailure( "Settings load", result );

    Platform::DashboardSettings& settings = m_settingsStore.Edit();
    ++settings.consoleTestBootCount;

    char bootCountMessage[ 128 ];
    sprintf_s(
        bootCountMessage,
        ARRAYSIZE( bootCountMessage ),
        "Milestone 000 console-test boot count: %u.",
        static_cast< unsigned int >( settings.consoleTestBootCount ) );
    Diagnostics::Write( bootCountMessage );

    result = VerifyApprovedResources();
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved BladeDash resource verification", result );
        Shutdown();
        return result;
    }

    Compatibility::SetGameLibraryRuntime( this );
    result = CXuiModule::Init( XuiD3DXTextureLoader );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "XUI initialization", result );
        Shutdown();
        return result;
    }
    m_xuiInitialized = TRUE;

    // The supplied main scene uses effect-enabled presentation layers.
    // CXuiModule's basic standalone initializer leaves its
    // helper-loop effects flag disabled, so opt the already initialized
    // renderer into the documented PreRender phase without replacing the
    // internally owned D3D device.
    m_bUsingEffects = TRUE;
    Diagnostics::Write(
        "XUI standalone renderer initialized; supplied-scene effects pre-render is enabled." );

    result = XuiRenderGetBackBufferSize(
        GetDC(),
        &m_backBufferWidth,
        &m_backBufferHeight );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "XUI backbuffer query", result );
        Shutdown();
        return result;
    }

    m_viewScaleX = static_cast< float >( m_backBufferWidth ) / ApprovedCanvasWidth;
    m_viewScaleY = static_cast< float >( m_backBufferHeight ) / ApprovedCanvasHeight;

    char displayMessage[ 192 ];
    sprintf_s(
        displayMessage,
        ARRAYSIZE( displayMessage ),
        "XUI backbuffer %ux%u; approved 1280x720 canvas view scale %.3fx%.3f.",
        static_cast< unsigned int >( m_backBufferWidth ),
        static_cast< unsigned int >( m_backBufferHeight ),
        m_viewScaleX,
        m_viewScaleY );
    Diagnostics::Write( displayMessage );

    result = RegisterDefaultTypeface(
        ApprovedDefaultTypefaceName,
        ApprovedDefaultTypefaceLocator );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved package Arial registration", result );
        Shutdown();
        return result;
    }
    result = RegisterTypeface(
        ConsoleTypefaceAliasName,
        ApprovedDefaultTypefaceLocator );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "ConsoleFont compatibility alias", result );
        Shutdown();
        return result;
    }
    Diagnostics::Write(
        "Registered supplied Arial as the default and ConsoleFont compatibility alias; global text rendering preserved." );

    result = LoadSkin( ApprovedSkinLocator );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved BladeDash skin.xur load", result );
        Shutdown();
        return result;
    }
    Diagnostics::Write( "Approved BladeDash skin.xur loaded." );

    result = LoadFirstScene(
        ApprovedSceneBase,
        ApprovedSceneFile,
        NULL,
        &m_approvedScene );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved BladeDash main.xur load", result );
        Shutdown();
        return result;
    }

    Diagnostics::Write(
        "Approved BladeDash main.xur initialized under the standalone host." );
    LocalizeSceneToEnglish( m_approvedScene, "main.xur" );

    result = XuiElementGetChildById( m_approvedScene, L"tab1", &m_mainTabHost );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved main.xur tab1 lookup", result );
        m_mainTabHost = NULL;
    }
    else
    {
        const UINT tabCount = XuiTabSceneGetCount( m_mainTabHost );
        const UINT currentTab = XuiTabSceneGetCurrentTab( m_mainTabHost, NULL );
        char tabMessage[ 160 ];
        sprintf_s(
            tabMessage,
            ARRAYSIZE( tabMessage ),
            "Approved main.xur tab host resolved: count=%u current=%u.",
            static_cast< unsigned int >( tabCount ),
            static_cast< unsigned int >( currentTab ) );
        Diagnostics::Write( tabMessage );
    }

    DWORD objectCount = 0;
    LogElementTree( m_approvedScene, 0, objectCount );
    return S_OK;
}

void BladeDashboardApp::Shutdown()
{
    if( m_xuiInitialized )
    {
        Uninit();
        m_xuiInitialized = FALSE;
        m_approvedScene = NULL;
        m_activeGameListScene = NULL;
        m_mainTabHost = NULL;
        m_lastFocusedObject = NULL;
    }

    if( m_servicesStarted )
    {
        const HRESULT saveResult = m_settingsStore.Save();
        if( FAILED( saveResult ) )
            Diagnostics::WriteFailure( "Settings save", saveResult );
        m_backgroundQueue.Stop();
        m_storageAliasService.Stop();
        m_controllerInput.Stop();
        m_servicesStarted = FALSE;
    }

    Compatibility::SetGameLibraryRuntime( NULL );
}

HRESULT BladeDashboardApp::PreRender()
{
    HRESULT result = XuiPreRenderBegin( GetDC(), D3DCOLOR_ARGB( 255, 0, 0, 0 ) );
    if( FAILED( result ) )
    {
        if( !m_preRenderFailureReported )
        {
            Diagnostics::WriteFailure( "XUI pre-render begin", result );
            m_preRenderFailureReported = TRUE;
        }
        return result;
    }

    XUIMessage message;
    XUIMessageRender renderData;
    D3DXMATRIX originalView;
    result = SetApprovedCanvasView(
        GetDC(),
        m_viewScaleX,
        m_viewScaleY,
        originalView );
    if( SUCCEEDED( result ) )
    {
        XuiMessagePreRender(
            &message,
            &renderData,
            GetDC(),
            0xffffffff,
            XUI_BLEND_NORMAL );
        result = XuiSendMessage( GetRootObj(), &message );

        const HRESULT restoreResult =
            XuiRenderSetViewTransform( GetDC(), &originalView );
        if( SUCCEEDED( result ) )
            result = restoreResult;
    }

    const HRESULT endResult = XuiPreRenderEnd( GetDC() );
    if( SUCCEEDED( result ) )
        result = endResult;

    if( FAILED( result ) && !m_preRenderFailureReported )
    {
        Diagnostics::WriteFailure( "XUI effects pre-render", result );
        m_preRenderFailureReported = TRUE;
    }

    return result;
}

HRESULT BladeDashboardApp::Render()
{
    HRESULT result = XuiRenderBegin( GetDC(), D3DCOLOR_ARGB( 255, 0, 0, 0 ) );
    if( FAILED( result ) )
    {
        if( !m_renderFailureReported )
        {
            Diagnostics::WriteFailure( "XUI render begin", result );
            m_renderFailureReported = TRUE;
        }
        return result;
    }

    XUIMessage message;
    XUIMessageRender renderData;
    D3DXMATRIX originalView;
    result = SetApprovedCanvasView(
        GetDC(),
        m_viewScaleX,
        m_viewScaleY,
        originalView );
    if( SUCCEEDED( result ) )
    {
        XuiMessageRender(
            &message,
            &renderData,
            GetDC(),
            0xffffffff,
            XUI_BLEND_NORMAL );
        result = XuiSendMessage( GetRootObj(), &message );

        const HRESULT restoreResult =
            XuiRenderSetViewTransform( GetDC(), &originalView );
        if( SUCCEEDED( result ) )
            result = restoreResult;
    }

    const HRESULT endResult = XuiRenderEnd( GetDC() );
    if( SUCCEEDED( result ) )
        result = endResult;

    if( SUCCEEDED( result ) )
        result = XuiRenderPresent( GetDC(), NULL, NULL, NULL );

    if( FAILED( result ) && !m_renderFailureReported )
    {
        Diagnostics::WriteFailure( "XUI render/present", result );
        m_renderFailureReported = TRUE;
    }
    else if( SUCCEEDED( result ) && !m_firstFrameReported )
    {
        Diagnostics::Write( "First XUI effects frame rendered and presented." );
        m_firstFrameReported = TRUE;
    }

    return result;
}

int BladeDashboardApp::RunUntilExit()
{
    return Run();
}

Platform::LaunchService& BladeDashboardApp::Launcher()
{
    return m_launchService;
}

HRESULT BladeDashboardApp::OpenGameCategory( Models::GameCategory category )
{
    m_categoryRequestReceivedThisFrame = TRUE;

    const DWORD requestTick = GetTickCount();
    if( m_lastRequestedGameCategory == category &&
        requestTick - m_lastGameCategoryRequestTick < 350 )
    {
        return S_FALSE;
    }
    m_lastRequestedGameCategory = category;
    m_lastGameCategoryRequestTick = requestTick;

    if( m_activeGameListScene != NULL )
        return S_FALSE;
    if( m_pendingGameCategory == static_cast< int >( category ) )
        return S_FALSE;

    const HRESULT selectResult = m_gameLibraryAdapter.SelectCategory( category );
    if( FAILED( selectResult ) )
    {
        if( selectResult == HRESULT_FROM_WIN32( ERROR_BUSY ) )
        {
            m_pendingGameCategory = static_cast< int >( category );
            char pendingMessage[ 192 ];
            sprintf_s(
                pendingMessage,
                ARRAYSIZE( pendingMessage ),
                "Game category request queued until the background scan completes: category=%s.",
                Models::GetGameCategoryLogName( category ) );
            Diagnostics::Write( pendingMessage );
            return S_OK;
        }

        Diagnostics::WriteFailure(
            "Game category selection",
            selectResult );
        return selectResult;
    }

    m_pendingGameCategory = -1;

    char categoryMessage[ 192 ];
    sprintf_s(
        categoryMessage,
        ARRAYSIZE( categoryMessage ),
        "Opening approved gamelist.xur category=%s items=%u.",
        Models::GetGameCategoryLogName( category ),
        static_cast< unsigned int >(
            m_gameLibraryAdapter.VisibleGameCount() ) );
    Diagnostics::Write( categoryMessage );
    m_lastVisibleGameSelection = static_cast< DWORD >( -1 );

    HXUIOBJ gameListScene = NULL;
    HRESULT result = XuiSceneCreate(
        ApprovedSceneBase,
        L"gamelist.xur",
        NULL,
        &gameListScene );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved gamelist.xur creation", result );
        return result;
    }

    result = XuiSceneNavigateForward(
        m_approvedScene,
        FALSE,
        gameListScene,
        XUSER_INDEX_FOCUS );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved gamelist.xur navigation", result );
        XuiDestroyObject( gameListScene );
        return result;
    }

    LocalizeSceneToEnglish( gameListScene, "gamelist.xur" );

    Diagnostics::Write(
        "Approved gamelist.xur initialized through the standalone library adapter." );
    m_activeGameListScene = gameListScene;
    return S_OK;
}

HRESULT BladeDashboardApp::CloseGameList()
{
    if( m_activeGameListScene == NULL )
        return S_FALSE;

    HXUIOBJ backScene = XuiSceneGetBackScene( m_activeGameListScene );
    if( backScene == NULL )
    {
        Diagnostics::WriteFailure(
            "Approved gamelist.xur back-scene lookup",
            E_UNEXPECTED );
        return E_UNEXPECTED;
    }

    const HRESULT result = XuiSceneNavigateBack(
        m_activeGameListScene,
        backScene,
        XUSER_INDEX_FOCUS );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Approved gamelist.xur back navigation", result );
        return result;
    }

    Diagnostics::Write( "Approved gamelist.xur returned to the main shell." );
    m_activeGameListScene = NULL;
    return S_OK;
}

DWORD BladeDashboardApp::GetVisibleGameCount() const
{
    return m_gameLibraryAdapter.VisibleGameCount();
}

LPCWSTR BladeDashboardApp::GetVisibleGameTitle( DWORD visibleIndex ) const
{
    return m_gameLibraryAdapter.VisibleGameTitle( visibleIndex );
}

void BladeDashboardApp::NotifyVisibleGameSelection( DWORD visibleIndex )
{
    if( visibleIndex == m_lastVisibleGameSelection ||
        visibleIndex >= m_gameLibraryAdapter.VisibleGameCount() )
    {
        return;
    }

    char message[ 320 ];
    sprintf_s(
        message,
        ARRAYSIZE( message ),
        "Approved game-list selection: index=%u title=%ls.",
        static_cast< unsigned int >( visibleIndex ),
        m_gameLibraryAdapter.VisibleGameTitle( visibleIndex ) );
    Diagnostics::Write( message );
    m_lastVisibleGameSelection = visibleIndex;
}

HRESULT BladeDashboardApp::LaunchVisibleGame( DWORD visibleIndex )
{
    const LPCWSTR title = m_gameLibraryAdapter.VisibleGameTitle( visibleIndex );
    const char* imagePath =
        m_gameLibraryAdapter.VisibleGameImagePath( visibleIndex );

    if( imagePath == NULL )
    {
        Diagnostics::WriteFailure( "Selected installed-game lookup", E_INVALIDARG );
        return E_INVALIDARG;
    }

    char launchMessage[ 512 ];
    sprintf_s(
        launchMessage,
        ARRAYSIZE( launchMessage ),
        "Queueing installed-game launch index=%u title=%ls image=%s.",
        static_cast< unsigned int >( visibleIndex ),
        title,
        imagePath );
    Diagnostics::Write( launchMessage );

    const HRESULT result =
        m_gameLibraryAdapter.QueueVisibleGameLaunch( visibleIndex );
    if( FAILED( result ) )
    {
        Diagnostics::WriteFailure( "Installed-game launch queue", result );
        return result;
    }

    Diagnostics::Write(
        "Installed-game launch queued; requesting clean XUI shutdown." );
    Quit();
    return S_OK;
}

void BladeDashboardApp::RunFrame()
{
    m_controllerInput.Poll();

    BOOL categoryActivationPressed = FALSE;
    Models::GameCategory pressedCategory = Models::GameCategoryXbox360;
    for( DWORD userIndex = 0; userIndex < XUSER_MAX_COUNT; ++userIndex )
    {
        if( !m_controllerInput.IsConnected( userIndex ) ||
            ( m_controllerInput.PressedButtons( userIndex ) &
                XINPUT_GAMEPAD_A ) == 0 )
        {
            continue;
        }

        categoryActivationPressed =
            Compatibility::TryResolveMainGameCategory(
                XuiElementGetFocus(),
                &pressedCategory );
        break;
    }

    m_categoryRequestReceivedThisFrame = FALSE;
    CXuiModule::RunFrame();

    if( m_firstFrameReported )
        LogNavigationStateIfChanged();

    ReportInstalledGameScan();
    OpenPendingGameCategoryIfReady();
    HandleMainGameCategoryInput(
        categoryActivationPressed,
        pressedCategory );

    for( DWORD userIndex = 0; userIndex < XUSER_MAX_COUNT; ++userIndex )
    {
        if( m_controllerInput.IsConnected( userIndex ) &&
            ( m_controllerInput.PressedButtons( userIndex ) & XINPUT_GAMEPAD_BACK ) != 0 )
        {
            Diagnostics::Write( "Controller Back pressed; requesting clean exit." );
            Quit();
            break;
        }
    }
}

void BladeDashboardApp::OpenPendingGameCategoryIfReady()
{
    if( m_pendingGameCategory < 0 || m_activeGameListScene != NULL )
        return;

    const Services::InstalledGameService::ScanState state =
        m_installedGameService.State();
    if( state == Services::InstalledGameService::ScanFailed )
    {
        Diagnostics::Write(
            "Discarding queued game category because the background scan failed." );
        m_pendingGameCategory = -1;
        return;
    }
    if( state != Services::InstalledGameService::ScanReady )
        return;

    const Models::GameCategory category =
        static_cast< Models::GameCategory >( m_pendingGameCategory );
    m_pendingGameCategory = -1;
    Diagnostics::Write(
        "Background scan is ready; opening the queued game category." );
    OpenGameCategory( category );
}

void BladeDashboardApp::HandleMainGameCategoryInput(
    BOOL categoryActivationPressed,
    Models::GameCategory category )
{
    if( !categoryActivationPressed ||
        m_categoryRequestReceivedThisFrame ||
        m_activeGameListScene != NULL )
    {
        return;
    }

    char message[ 256 ];
    sprintf_s(
        message,
        ARRAYSIZE( message ),
        "Controller A fallback routed focused category: id=%ls category=%s.",
        GetGameCategoryControlId( category ),
        Models::GetGameCategoryLogName( category ) );
    Diagnostics::Write( message );
    OpenGameCategory( category );
}

HRESULT BladeDashboardApp::RegisterXuiClasses()
{
    HRESULT result = XuiSoundXAudioRegister();
    if( FAILED( result ) )
        return result;
    Diagnostics::Write( "Registered XDK XuiSoundXAudio class for supplied skin audio objects." );

    result = Compatibility::ScnTabPresenter::Register();
    if( FAILED( result ) )
    {
        XuiSoundXAudioUnregister();
        return result;
    }
    Diagnostics::Write( "Registered observed ScnTabPresenter compatibility class." );

    DWORD resolvedClassCount = 0;
    result = Compatibility::RegisterObservedMainSceneClasses(
        &m_mainSceneClassRegistrationMask,
        &resolvedClassCount );
    if( FAILED( result ) )
    {
        Compatibility::ScnTabPresenter::Unregister();
        XuiSoundXAudioUnregister();
        return result;
    }

    char classMessage[ 160 ];
    sprintf_s(
        classMessage,
        ARRAYSIZE( classMessage ),
        "Resolved %u observed main.xur compatibility classes without invented behavior.",
        static_cast< unsigned int >( resolvedClassCount ) );
    Diagnostics::Write( classMessage );

    DWORD gameClassCount = 0;
    result = Compatibility::RegisterObservedGameLibraryClasses(
        &m_gameLibraryClassRegistrationMask,
        &gameClassCount );
    if( FAILED( result ) )
    {
        Compatibility::UnregisterObservedMainSceneClasses(
            m_mainSceneClassRegistrationMask );
        m_mainSceneClassRegistrationMask = 0;
        Compatibility::ScnTabPresenter::Unregister();
        XuiSoundXAudioUnregister();
        return result;
    }

    sprintf_s(
        classMessage,
        ARRAYSIZE( classMessage ),
        "Registered %u observed gamelist/GameControls compatibility classes.",
        static_cast< unsigned int >( gameClassCount ) );
    Diagnostics::Write( classMessage );

    return S_OK;
}

HRESULT BladeDashboardApp::UnregisterXuiClasses()
{
    const HRESULT gameClassResult =
        Compatibility::UnregisterObservedGameLibraryClasses(
            m_gameLibraryClassRegistrationMask );
    m_gameLibraryClassRegistrationMask = 0;

    const HRESULT mainClassResult =
        Compatibility::UnregisterObservedMainSceneClasses(
            m_mainSceneClassRegistrationMask );
    m_mainSceneClassRegistrationMask = 0;
    Compatibility::ScnTabPresenter::Unregister();
    XuiSoundXAudioUnregister();
    return FAILED( gameClassResult ) ? gameClassResult : mainClassResult;
}

void BladeDashboardApp::LogNavigationStateIfChanged()
{
    const HXUIOBJ focusedObject = XuiElementGetFocus();
    const UINT currentTab = m_mainTabHost == NULL
        ? static_cast< UINT >( -1 )
        : XuiTabSceneGetCurrentTab( m_mainTabHost, NULL );

    if( m_navigationStateReported &&
        focusedObject == m_lastFocusedObject &&
        currentTab == m_lastMainTab )
    {
        return;
    }

    LPCWSTR focusId = L"<none>";
    LPCWSTR focusClass = L"<unknown>";
    GetElementIdentity( focusedObject, &focusId, &focusClass );

    char message[ 240 ];
    sprintf_s(
        message,
        ARRAYSIZE( message ),
        "Approved main navigation state: tab=%u focus=%ls class=%ls.",
        static_cast< unsigned int >( currentTab ),
        focusId,
        focusClass );
    Diagnostics::Write( message );

    m_lastFocusedObject = focusedObject;
    m_lastMainTab = currentTab;
    m_navigationStateReported = TRUE;
}

void BladeDashboardApp::ReportInstalledGameScan()
{
    if( m_gameScanReported )
        return;

    const Services::InstalledGameService::ScanState state =
        m_installedGameService.State();
    if( state != Services::InstalledGameService::ScanReady &&
        state != Services::InstalledGameService::ScanFailed )
    {
        return;
    }

    char message[ 256 ];
    sprintf_s(
        message,
        ARRAYSIZE( message ),
        "Installed-game background scan %s: configured_roots=%u existing_roots=%u games=%u capacity_reached=%u.",
        state == Services::InstalledGameService::ScanReady ? "completed" : "failed",
        static_cast< unsigned int >(
            m_installedGameService.ConfiguredRootCount() ),
        static_cast< unsigned int >(
            m_installedGameService.ExistingRootCount() ),
        static_cast< unsigned int >( m_installedGameService.GameCount() ),
        m_installedGameService.CapacityReached() ? 1u : 0u );
    Diagnostics::Write( message );

    if( state == Services::InstalledGameService::ScanReady )
    {
        DWORD categoryCounts[ Models::GameCategoryCount ];
        ZeroMemory( categoryCounts, sizeof( categoryCounts ) );

        const DWORD gameCount = m_installedGameService.GameCount();
        for( DWORD index = 0; index < gameCount; ++index )
        {
            const Models::InstalledGame* game =
                m_installedGameService.GameAt( index );
            if( game != NULL && game->category >= Models::GameCategoryXbox360 &&
                game->category < Models::GameCategoryCount )
            {
                ++categoryCounts[ game->category ];
            }
        }

        for( DWORD category = 0;
             category < Models::GameCategoryCount;
             ++category )
        {
            char categoryMessage[ 160 ];
            sprintf_s(
                categoryMessage,
                ARRAYSIZE( categoryMessage ),
                "Installed-game category total: category=%s games=%u.",
                Models::GetGameCategoryLogName(
                    static_cast< Models::GameCategory >( category ) ),
                static_cast< unsigned int >( categoryCounts[ category ] ) );
            Diagnostics::Write( categoryMessage );
        }

        for( DWORD index = 0; index < gameCount; ++index )
        {
            const Models::InstalledGame* game =
                m_installedGameService.GameAt( index );
            if( game == NULL )
                continue;

            char gameMessage[ 640 ];
            sprintf_s(
                gameMessage,
                ARRAYSIZE( gameMessage ),
                "Discovered launchable entry: index=%u category=%s title=%ls image=%s.",
                static_cast< unsigned int >( index ),
                Models::GetGameCategoryLogName( game->category ),
                game->displayName,
                game->imagePath );
            Diagnostics::Write( gameMessage );
        }
    }
    m_gameScanReported = TRUE;
}

void BladeDashboardApp::ScanInstalledGames( void* context )
{
    BladeDashboardApp* application = static_cast< BladeDashboardApp* >( context );
    if( application != NULL )
        application->m_installedGameService.Scan();
}

HRESULT BladeDashboardApp::VerifyApprovedResources() const
{
    const char* requiredFiles[] =
    {
        ApprovedSkinFilePath,
        ApprovedSceneFilePath,
        ApprovedGameListFilePath,
        ApprovedGameControlsFilePath,
        ApprovedDefaultTypefaceFilePath
    };

    for( DWORD index = 0; index < ARRAYSIZE( requiredFiles ); ++index )
    {
        const HRESULT result = VerifyFile( requiredFiles[ index ] );
        if( FAILED( result ) )
        {
            Diagnostics::Write( requiredFiles[ index ] );
            return result;
        }
    }

    if( FAILED( VerifyFile( MissingApprovedBootLogoPath ) ) )
        Diagnostics::Write(
            "REFERENCE_GAP: approved main.xur references absent img-Xbox360Logo_Stacked.png; no substitute was introduced." );
    if( FAILED( VerifyFile( MissingApprovedWeatherIconPath ) ) )
        Diagnostics::Write(
            "REFERENCE_GAP: approved main.xur references absent Weather Type/25.png; no substitute was introduced." );

    return S_OK;
}

} // namespace App
} // namespace Blade
