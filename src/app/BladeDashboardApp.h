#pragma once

#include <xtl.h>
#include <xui.h>
#include <xuiapp.h>

#include "adapters/BladeGameLibraryAdapter.h"
#include "compatibility/GameLibraryCompatibility.h"
#include "core/BackgroundQueue.h"
#include "navigation/NavigationState.h"
#include "platform/ControllerInput.h"
#include "platform/LaunchService.h"
#include "platform/SettingsStore.h"
#include "platform/StorageAliasService.h"
#include "services/InstalledGameService.h"

namespace Blade
{
namespace App
{

class BladeDashboardApp :
    public CXuiModule,
    public Compatibility::IGameLibraryRuntime
{
public:
    BladeDashboardApp();
    virtual ~BladeDashboardApp();

    HRESULT Initialize();
    void Shutdown();
    int RunUntilExit();

    Platform::LaunchService& Launcher();

    virtual HRESULT OpenGameCategory( Models::GameCategory category );
    virtual HRESULT CloseGameList();
    virtual DWORD GetVisibleGameCount() const;
    virtual LPCWSTR GetVisibleGameTitle( DWORD visibleIndex ) const;
    virtual void NotifyVisibleGameSelection( DWORD visibleIndex );
    virtual HRESULT LaunchVisibleGame( DWORD visibleIndex );

    virtual void RunFrame();
    virtual HRESULT PreRender();
    virtual HRESULT Render();

protected:
    virtual HRESULT RegisterXuiClasses();
    virtual HRESULT UnregisterXuiClasses();

private:
    BladeDashboardApp( const BladeDashboardApp& );
    BladeDashboardApp& operator=( const BladeDashboardApp& );

    static void ScanInstalledGames( void* context );
    HRESULT VerifyApprovedResources() const;
    void LogNavigationStateIfChanged();
    void ReportInstalledGameScan();
    void OpenPendingGameCategoryIfReady();
    void HandleMainGameCategoryInput(
        BOOL categoryActivationPressed,
        Models::GameCategory category );

    Core::BackgroundQueue m_backgroundQueue;
    Services::InstalledGameService m_installedGameService;
    Navigation::NavigationState m_navigation;
    Platform::ControllerInput m_controllerInput;
    Platform::StorageAliasService m_storageAliasService;
    Platform::LaunchService m_launchService;
    Adapters::BladeGameLibraryAdapter m_gameLibraryAdapter;
    Platform::SettingsStore m_settingsStore;
    BOOL m_xuiInitialized;
    BOOL m_servicesStarted;
    BOOL m_gameScanReported;
    HXUIOBJ m_approvedScene;
    HXUIOBJ m_activeGameListScene;
    HXUIOBJ m_mainTabHost;
    HXUIOBJ m_lastFocusedObject;
    DWORD m_mainSceneClassRegistrationMask;
    DWORD m_gameLibraryClassRegistrationMask;
    UINT m_lastMainTab;
    BOOL m_navigationStateReported;
    BOOL m_preRenderFailureReported;
    BOOL m_renderFailureReported;
    BOOL m_firstFrameReported;
    BOOL m_categoryRequestReceivedThisFrame;
    DWORD m_lastVisibleGameSelection;
    DWORD m_lastGameCategoryRequestTick;
    Models::GameCategory m_lastRequestedGameCategory;
    int m_pendingGameCategory;
    UINT m_backBufferWidth;
    UINT m_backBufferHeight;
    float m_viewScaleX;
    float m_viewScaleY;
};

} // namespace App
} // namespace Blade
