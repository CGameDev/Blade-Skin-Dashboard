#include "compatibility/GameLibraryCompatibility.h"

#include "diagnostics/DebugLog.h"

#include <stdio.h>

namespace Blade
{
namespace Compatibility
{

namespace
{
IGameLibraryRuntime* g_runtime = NULL;
HXUIOBJ g_activeGamesList = NULL;
DWORD g_sourceTextReportCount = 0;

typedef HRESULT ( *ClassLifecycleFunction )();

struct ObservedClass
{
    ClassLifecycleFunction registerClass;
    ClassLifecycleFunction unregisterClass;
    DWORD bit;
};

const ObservedClass ObservedClasses[] =
{
    { ScnGameView::Register, ScnGameView::Unregister, 1u << 0 },
    { GamesList::Register, GamesList::Unregister, 1u << 1 },
    { ScnGameControls::Register, ScnGameControls::Unregister, 1u << 2 }
};

BOOL EqualsId( HXUIOBJ object, LPCWSTR expectedId )
{
    LPCWSTR id = NULL;
    return object != NULL && expectedId != NULL &&
        SUCCEEDED( XuiElementGetId( object, &id ) ) && id != NULL &&
        _wcsicmp( id, expectedId ) == 0;
}

BOOL IsObjectInActiveList( HXUIOBJ object )
{
    while( object != NULL )
    {
        if( object == g_activeGamesList )
            return TRUE;

        HXUIOBJ parent = NULL;
        if( FAILED( XuiElementGetParent( object, &parent ) ) )
            return FALSE;
        object = parent;
    }

    return FALSE;
}

int GetActiveSelection()
{
    return g_activeGamesList != NULL
        ? XuiListGetCurSel( g_activeGamesList, NULL )
        : -1;
}

void UpdateCounter()
{
    if( g_activeGamesList == NULL )
        return;

    HXUIOBJ parent = NULL;
    HXUIOBJ counter = NULL;
    if( FAILED( XuiElementGetParent( g_activeGamesList, &parent ) ) ||
        parent == NULL ||
        FAILED( XuiElementGetChildById(
            parent,
            L"TextGameListCounter",
            &counter ) ) ||
        counter == NULL )
    {
        return;
    }

    const DWORD count = g_runtime != NULL
        ? g_runtime->GetVisibleGameCount()
        : 0;
    const int selection = GetActiveSelection();

    WCHAR text[ 64 ];
    if( count == 0 )
        swprintf_s( text, ARRAYSIZE( text ), L"0 of 0" );
    else
        swprintf_s(
            text,
            ARRAYSIZE( text ),
            L"%u of %u",
            static_cast< unsigned int >( selection >= 0 ? selection + 1 : 1 ),
            static_cast< unsigned int >( count ) );

    XuiTextElementSetText( counter, text );
}

}

void SetGameLibraryRuntime( IGameLibraryRuntime* runtime )
{
    g_runtime = runtime;
    g_sourceTextReportCount = 0;
    if( runtime == NULL )
        g_activeGamesList = NULL;
}

BOOL TryResolveMainGameCategory(
    HXUIOBJ object,
    Models::GameCategory* category )
{
    if( category == NULL )
        return FALSE;

    if( EqualsId( object, L"XBox360Games" ) )
        *category = Models::GameCategoryXbox360;
    else if( EqualsId( object, L"XBoxLiveArcade" ) )
        *category = Models::GameCategoryXboxLiveArcade;
    else if( EqualsId( object, L"XBox1Games" ) )
        *category = Models::GameCategoryXboxClassic;
    else if( EqualsId( object, L"Emulators" ) )
        *category = Models::GameCategoryEmulators;
    else if( EqualsId( object, L"Homebrew" ) )
        *category = Models::GameCategoryHomebrew;
    else
        return FALSE;

    return TRUE;
}

BOOL TryHandleMainGameCategoryPress( HXUIOBJ pressedObject )
{
    Models::GameCategory category;
    if( !TryResolveMainGameCategory( pressedObject, &category ) )
        return FALSE;

    if( g_runtime != NULL )
        g_runtime->OpenGameCategory( category );
    return TRUE;
}

HRESULT ScnGameView::OnNotifyPress(
    HXUIOBJ pressedObject,
    BOOL& handled )
{
    if( EqualsId( pressedObject, L"ButtonBack" ) )
    {
        handled = TRUE;
        if( g_runtime != NULL )
            g_runtime->CloseGameList();
        return S_OK;
    }

    if( !EqualsId( pressedObject, L"ButtonLaunchGame" ) &&
        !IsObjectInActiveList( pressedObject ) )
    {
        return S_OK;
    }

    handled = TRUE;
    const int selection = GetActiveSelection();
    if( g_runtime != NULL && selection >= 0 )
        g_runtime->LaunchVisibleGame( static_cast< DWORD >( selection ) );
    return S_OK;
}

HRESULT ScnGameView::OnNotifySelectionChanged(
    HXUIOBJ sourceObject,
    XUINotifySelChanged* notification,
    BOOL& handled )
{
    (void)notification;
    (void)handled;
    if( sourceObject == g_activeGamesList )
    {
        UpdateCounter();
        const int selection = GetActiveSelection();
        if( g_runtime != NULL && selection >= 0 )
        {
            g_runtime->NotifyVisibleGameSelection(
                static_cast< DWORD >( selection ) );
        }
    }
    return S_OK;
}

HRESULT GamesList::OnInit( XUIMessageInit* initData, BOOL& handled )
{
    (void)initData;
    (void)handled;

    g_activeGamesList = m_hObj;
    g_sourceTextReportCount = 0;
    const DWORD count = g_runtime != NULL
        ? g_runtime->GetVisibleGameCount()
        : 0;
    if( count != 0 )
    {
        const HRESULT result = InsertItems( 0, static_cast< int >( count ) );
        if( FAILED( result ) )
            return result;
        SetCurSel( 0 );
    }

    UpdateCounter();
    if( count != 0 && g_runtime != NULL )
        g_runtime->NotifyVisibleGameSelection( 0 );
    return S_OK;
}

HRESULT GamesList::OnGetSourceText(
    XUIMessageGetSourceText* sourceText,
    BOOL& handled )
{
    if( sourceText == NULL )
        return E_POINTER;

    handled = TRUE;
    sourceText->szText = NULL;
    if( sourceText->iItem < 0 || sourceText->iData != 0 || g_runtime == NULL )
    {
        if( g_sourceTextReportCount < 4 )
        {
            char message[ 192 ];
            sprintf_s(
                message,
                ARRAYSIZE( message ),
                "GamesList title request ignored: item=%d data=%d item_data=%u runtime=%u.",
                sourceText->iItem,
                sourceText->iData,
                sourceText->bItemData ? 1u : 0u,
                g_runtime != NULL ? 1u : 0u );
            Diagnostics::Write( message );
            ++g_sourceTextReportCount;
        }
        return S_OK;
    }

    const DWORD index = static_cast< DWORD >( sourceText->iItem );
    const DWORD visibleCount = g_runtime->GetVisibleGameCount();
    if( index < visibleCount )
    {
        const LPCWSTR title = g_runtime->GetVisibleGameTitle( index );
        sourceText->szText = title;
        if( g_sourceTextReportCount < 4 )
        {
            char message[ 320 ];
            sprintf_s(
                message,
                ARRAYSIZE( message ),
                "GamesList title supplied: item=%u data=%d item_data=%u title=%ls.",
                static_cast< unsigned int >( index ),
                sourceText->iData,
                sourceText->bItemData ? 1u : 0u,
                title != NULL ? title : L"<null>" );
            Diagnostics::Write( message );
            ++g_sourceTextReportCount;
        }
    }
    else if( g_sourceTextReportCount < 4 )
    {
        char message[ 192 ];
        sprintf_s(
            message,
            ARRAYSIZE( message ),
            "GamesList title request outside visible range: item=%u count=%u data=%d item_data=%u.",
            static_cast< unsigned int >( index ),
            static_cast< unsigned int >( visibleCount ),
            sourceText->iData,
            sourceText->bItemData ? 1u : 0u );
        Diagnostics::Write( message );
        ++g_sourceTextReportCount;
    }
    return S_OK;
}

HRESULT GamesList::OnGetItemCountAll(
    XUIMessageGetItemCount* itemCount,
    BOOL& handled )
{
    if( itemCount == NULL )
        return E_POINTER;

    handled = TRUE;
    itemCount->cItems = g_runtime != NULL
        ? static_cast< int >( g_runtime->GetVisibleGameCount() )
        : 0;
    return S_OK;
}

HRESULT RegisterObservedGameLibraryClasses(
    DWORD* registeredMask,
    DWORD* resolvedCount )
{
    if( registeredMask == NULL || resolvedCount == NULL )
        return E_INVALIDARG;

    *registeredMask = 0;
    *resolvedCount = 0;

    for( DWORD index = 0; index < ARRAYSIZE( ObservedClasses ); ++index )
    {
        const ObservedClass& observedClass = ObservedClasses[ index ];
        const HRESULT result = observedClass.registerClass();
        if( FAILED( result ) )
        {
            UnregisterObservedGameLibraryClasses( *registeredMask );
            *registeredMask = 0;
            *resolvedCount = 0;
            return result;
        }

        *registeredMask |= observedClass.bit;
        ++( *resolvedCount );
    }

    return S_OK;
}

HRESULT UnregisterObservedGameLibraryClasses( DWORD registeredMask )
{
    HRESULT firstFailure = S_OK;
    for( int index = ARRAYSIZE( ObservedClasses ) - 1; index >= 0; --index )
    {
        const ObservedClass& observedClass = ObservedClasses[ index ];
        if( ( registeredMask & observedClass.bit ) == 0 )
            continue;

        const HRESULT result = observedClass.unregisterClass();
        if( FAILED( result ) && SUCCEEDED( firstFailure ) )
            firstFailure = result;
    }
    return firstFailure;
}

} // namespace Compatibility
} // namespace Blade
