#pragma once

#include <xtl.h>
#include <xui.h>
#include <xuiapp.h>

namespace Blade
{
namespace Compatibility
{

class MainSceneHost : public CXuiTabSceneImpl
{
protected:
    XUI_BEGIN_MSG_MAP()
        XUI_ON_XM_NOTIFY_PRESS( OnNotifyPress )
    XUI_END_MSG_MAP()

    HRESULT OnNotifyPress( HXUIOBJ pressedObject, BOOL& handled );

public:
    XUI_IMPLEMENT_CLASS( MainSceneHost, L"MainScene", XUI_CLASS_TABSCENE )
};

class ScnMain : public CXuiTabSceneImpl
{
protected:
    XUI_BEGIN_MSG_MAP()
        XUI_ON_XM_NOTIFY_PRESS( OnNotifyPress )
    XUI_END_MSG_MAP()

    HRESULT OnNotifyPress( HXUIOBJ pressedObject, BOOL& handled );

public:
    XUI_IMPLEMENT_CLASS( ScnMain, L"ScnMain", XUI_CLASS_TABSCENE )
};

class ScnCanvasPresenter : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnCanvasPresenter, L"ScnCanvasPresenter", XUI_CLASS_SCENE )
};

class ScnPopup : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnPopup, L"ScnPopup", XUI_CLASS_SCENE )
};

class ScnWeather : public CXuiTabSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnWeather, L"ScnWeather", XUI_CLASS_TABSCENE )
};

class ScnSysInfo : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnSysInfo, L"ScnSysInfo", XUI_CLASS_SCENE )
};

class ScnProfile : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnProfile, L"ScnProfile", XUI_CLASS_SCENE )
};

class ScnAvatar : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnAvatar, L"ScnAvatar", XUI_CLASS_SCENE )
};

class ScnChooseSkin : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnChooseSkin, L"ScnChooseSkin", XUI_CLASS_SCENE )
};

class ScnKinectVoice : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnKinectVoice, L"ScnKinectVoice", XUI_CLASS_SCENE )
};

class KinectCommandList : public CXuiListImpl
{
public:
    XUI_IMPLEMENT_CLASS( KinectCommandList, L"KinectCommandList", XUI_CLASS_LIST )
};

const DWORD ObservedMainSceneClassCount = 11;

HRESULT RegisterObservedMainSceneClasses(
    DWORD* registeredMask,
    DWORD* resolvedCount );
HRESULT UnregisterObservedMainSceneClasses( DWORD registeredMask );

} // namespace Compatibility
} // namespace Blade
