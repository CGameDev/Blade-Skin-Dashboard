#pragma once

#include <xtl.h>
#include <xui.h>
#include <xuiapp.h>

#include "models/InstalledGame.h"

namespace Blade
{
namespace Compatibility
{

class IGameLibraryRuntime
{
public:
    virtual HRESULT OpenGameCategory( Models::GameCategory category ) = 0;
    virtual HRESULT CloseGameList() = 0;
    virtual DWORD GetVisibleGameCount() const = 0;
    virtual LPCWSTR GetVisibleGameTitle( DWORD visibleIndex ) const = 0;
    virtual void NotifyVisibleGameSelection( DWORD visibleIndex ) = 0;
    virtual HRESULT LaunchVisibleGame( DWORD visibleIndex ) = 0;

protected:
    virtual ~IGameLibraryRuntime()
    {
    }
};

void SetGameLibraryRuntime( IGameLibraryRuntime* runtime );
BOOL TryResolveMainGameCategory(
    HXUIOBJ object,
    Models::GameCategory* category );
BOOL TryHandleMainGameCategoryPress( HXUIOBJ pressedObject );

class ScnGameView : public CXuiTabSceneImpl
{
protected:
    XUI_BEGIN_MSG_MAP()
        XUI_ON_XM_NOTIFY_PRESS( OnNotifyPress )
        XUI_ON_XM_NOTIFY_SELCHANGED( OnNotifySelectionChanged )
    XUI_END_MSG_MAP()

    HRESULT OnNotifyPress( HXUIOBJ pressedObject, BOOL& handled );
    HRESULT OnNotifySelectionChanged(
        HXUIOBJ sourceObject,
        XUINotifySelChanged* notification,
        BOOL& handled );

public:
    XUI_IMPLEMENT_CLASS( ScnGameView, L"ScnGameView", XUI_CLASS_TABSCENE )
};

class GamesList : public CXuiListImpl
{
protected:
    XUI_BEGIN_MSG_MAP()
        XUI_ON_XM_INIT( OnInit )
        XUI_ON_XM_GET_SOURCE_TEXT( OnGetSourceText )
        XUI_ON_XM_GET_ITEMCOUNT_ALL( OnGetItemCountAll )
    XUI_END_MSG_MAP()

    HRESULT OnInit( XUIMessageInit* initData, BOOL& handled );
    HRESULT OnGetSourceText(
        XUIMessageGetSourceText* sourceText,
        BOOL& handled );
    HRESULT OnGetItemCountAll(
        XUIMessageGetItemCount* itemCount,
        BOOL& handled );

public:
    XUI_IMPLEMENT_CLASS( GamesList, L"GamesList", XUI_CLASS_LIST )
};

class ScnGameControls : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS(
        ScnGameControls,
        L"ScnGameControls",
        XUI_CLASS_SCENE )
};

const DWORD ObservedGameLibraryClassCount = 3;

HRESULT RegisterObservedGameLibraryClasses(
    DWORD* registeredMask,
    DWORD* resolvedCount );
HRESULT UnregisterObservedGameLibraryClasses( DWORD registeredMask );

} // namespace Compatibility
} // namespace Blade
