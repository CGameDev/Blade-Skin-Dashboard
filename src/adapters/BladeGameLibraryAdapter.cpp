#include "adapters/BladeGameLibraryAdapter.h"

namespace Blade
{
namespace Adapters
{

BladeGameLibraryAdapter::BladeGameLibraryAdapter(
    Services::InstalledGameService& library,
    Platform::LaunchService& launcher )
    : m_library( library ),
      m_launcher( launcher ),
      m_visibleCount( 0 ),
      m_selectedCategory( Models::GameCategoryXbox360 )
{
    ZeroMemory( m_visibleIndices, sizeof( m_visibleIndices ) );
}

HRESULT BladeGameLibraryAdapter::SelectCategory(
    Models::GameCategory category )
{
    if( category < Models::GameCategoryXbox360 ||
        category >= Models::GameCategoryCount )
    {
        return E_INVALIDARG;
    }
    if( m_library.State() != Services::InstalledGameService::ScanReady )
        return HRESULT_FROM_WIN32( ERROR_BUSY );

    m_selectedCategory = category;
    m_visibleCount = 0;
    ZeroMemory( m_visibleIndices, sizeof( m_visibleIndices ) );

    const DWORD totalCount = m_library.GameCount();
    for( DWORD index = 0;
         index < totalCount &&
             m_visibleCount < ARRAYSIZE( m_visibleIndices );
         ++index )
    {
        const Models::InstalledGame* game = m_library.GameAt( index );
        if( game == NULL || game->category != category )
            continue;

        m_visibleIndices[ m_visibleCount++ ] = index;
    }

    return S_OK;
}

Models::GameCategory BladeGameLibraryAdapter::SelectedCategory() const
{
    return m_selectedCategory;
}

DWORD BladeGameLibraryAdapter::VisibleGameCount() const
{
    return m_visibleCount;
}

LPCWSTR BladeGameLibraryAdapter::VisibleGameTitle( DWORD visibleIndex ) const
{
    const Models::InstalledGame* game = ResolveVisibleGame( visibleIndex );
    return game != NULL ? game->displayName : L"";
}

const char* BladeGameLibraryAdapter::VisibleGameImagePath(
    DWORD visibleIndex ) const
{
    const Models::InstalledGame* game = ResolveVisibleGame( visibleIndex );
    return game != NULL ? game->imagePath : NULL;
}

HRESULT BladeGameLibraryAdapter::QueueVisibleGameLaunch( DWORD visibleIndex )
{
    const char* imagePath = VisibleGameImagePath( visibleIndex );
    return imagePath != NULL ? m_launcher.QueueLaunch( imagePath ) : E_INVALIDARG;
}

const Models::InstalledGame* BladeGameLibraryAdapter::ResolveVisibleGame(
    DWORD visibleIndex ) const
{
    if( visibleIndex >= m_visibleCount )
        return NULL;
    return m_library.GameAt( m_visibleIndices[ visibleIndex ] );
}

} // namespace Adapters
} // namespace Blade
