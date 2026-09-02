#include "compatibility/MainSceneCompatibility.h"

#include "compatibility/GameLibraryCompatibility.h"

namespace Blade
{
namespace Compatibility
{

HRESULT MainSceneHost::OnNotifyPress( HXUIOBJ pressedObject, BOOL& handled )
{
    if( TryHandleMainGameCategoryPress( pressedObject ) )
        handled = TRUE;
    return S_OK;
}

HRESULT ScnMain::OnNotifyPress( HXUIOBJ pressedObject, BOOL& handled )
{
    if( TryHandleMainGameCategoryPress( pressedObject ) )
        handled = TRUE;
    return S_OK;
}

namespace
{
typedef HRESULT ( *ClassLifecycleFunction )();

struct ObservedClass
{
    LPCWSTR name;
    ClassLifecycleFunction registerClass;
    ClassLifecycleFunction unregisterClass;
    DWORD bit;
};

const ObservedClass ObservedClasses[] =
{
    { L"MainScene", MainSceneHost::Register, MainSceneHost::Unregister, 1u << 0 },
    { L"ScnMain", ScnMain::Register, ScnMain::Unregister, 1u << 1 },
    { L"ScnCanvasPresenter", ScnCanvasPresenter::Register, ScnCanvasPresenter::Unregister, 1u << 2 },
    { L"ScnPopup", ScnPopup::Register, ScnPopup::Unregister, 1u << 3 },
    { L"ScnWeather", ScnWeather::Register, ScnWeather::Unregister, 1u << 4 },
    { L"ScnSysInfo", ScnSysInfo::Register, ScnSysInfo::Unregister, 1u << 5 },
    { L"ScnProfile", ScnProfile::Register, ScnProfile::Unregister, 1u << 6 },
    { L"ScnAvatar", ScnAvatar::Register, ScnAvatar::Unregister, 1u << 7 },
    { L"ScnChooseSkin", ScnChooseSkin::Register, ScnChooseSkin::Unregister, 1u << 8 },
    { L"ScnKinectVoice", ScnKinectVoice::Register, ScnKinectVoice::Unregister, 1u << 9 },
    { L"KinectCommandList", KinectCommandList::Register, KinectCommandList::Unregister, 1u << 10 }
};
}

HRESULT RegisterObservedMainSceneClasses(
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
        if( XuiFindClass( observedClass.name ) == NULL )
        {
            const HRESULT result = observedClass.registerClass();
            if( FAILED( result ) )
            {
                UnregisterObservedMainSceneClasses( *registeredMask );
                *registeredMask = 0;
                *resolvedCount = 0;
                return result;
            }
            *registeredMask |= observedClass.bit;
        }

        ++( *resolvedCount );
    }

    return S_OK;
}

HRESULT UnregisterObservedMainSceneClasses( DWORD registeredMask )
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
