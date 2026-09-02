#pragma once

#include <xtl.h>

namespace Blade
{
namespace Navigation
{

enum SceneId
{
    SceneNone = 0,
    SceneApprovedSplash,
    SceneMainBladeShell,
    SceneFullScreenChild,
    SceneDialog
};

struct NavigationEntry
{
    SceneId scene;
    DWORD focusToken;
};

class NavigationState
{
public:
    NavigationState();

    HRESULT Reset( SceneId rootScene );
    HRESULT Push( SceneId scene, DWORD focusToken );
    HRESULT Pop( NavigationEntry* restoredEntry );
    const NavigationEntry* Current() const;
    DWORD Depth() const;

private:
    static const DWORD MaximumDepth = 16;
    NavigationEntry m_entries[ MaximumDepth ];
    DWORD m_depth;
};

} // namespace Navigation
} // namespace Blade
