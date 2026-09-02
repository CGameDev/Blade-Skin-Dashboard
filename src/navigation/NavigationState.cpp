#include "navigation/NavigationState.h"

namespace Blade
{
namespace Navigation
{

NavigationState::NavigationState()
    : m_depth( 0 )
{
    ZeroMemory( m_entries, sizeof( m_entries ) );
}

HRESULT NavigationState::Reset( SceneId rootScene )
{
    if( rootScene == SceneNone )
        return E_INVALIDARG;

    ZeroMemory( m_entries, sizeof( m_entries ) );
    m_entries[ 0 ].scene = rootScene;
    m_entries[ 0 ].focusToken = 0;
    m_depth = 1;
    return S_OK;
}

HRESULT NavigationState::Push( SceneId scene, DWORD focusToken )
{
    if( scene == SceneNone )
        return E_INVALIDARG;
    if( m_depth == 0 || m_depth >= MaximumDepth )
        return E_FAIL;

    m_entries[ m_depth ].scene = scene;
    m_entries[ m_depth ].focusToken = focusToken;
    ++m_depth;
    return S_OK;
}

HRESULT NavigationState::Pop( NavigationEntry* restoredEntry )
{
    if( m_depth <= 1 )
        return S_FALSE;

    --m_depth;
    ZeroMemory( &m_entries[ m_depth ], sizeof( NavigationEntry ) );
    if( restoredEntry != NULL )
        *restoredEntry = m_entries[ m_depth - 1 ];
    return S_OK;
}

const NavigationEntry* NavigationState::Current() const
{
    return m_depth == 0 ? NULL : &m_entries[ m_depth - 1 ];
}

DWORD NavigationState::Depth() const
{
    return m_depth;
}

} // namespace Navigation
} // namespace Blade
