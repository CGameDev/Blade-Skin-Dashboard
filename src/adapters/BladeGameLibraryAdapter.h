#pragma once

#include <xtl.h>

#include "models/InstalledGame.h"
#include "platform/LaunchService.h"
#include "services/InstalledGameService.h"

namespace Blade
{
namespace Adapters
{

class BladeGameLibraryAdapter
{
public:
    BladeGameLibraryAdapter(
        Services::InstalledGameService& library,
        Platform::LaunchService& launcher );

    HRESULT SelectCategory( Models::GameCategory category );
    Models::GameCategory SelectedCategory() const;
    DWORD VisibleGameCount() const;
    LPCWSTR VisibleGameTitle( DWORD visibleIndex ) const;
    const char* VisibleGameImagePath( DWORD visibleIndex ) const;
    HRESULT QueueVisibleGameLaunch( DWORD visibleIndex );

private:
    BladeGameLibraryAdapter( const BladeGameLibraryAdapter& );
    BladeGameLibraryAdapter& operator=( const BladeGameLibraryAdapter& );

    const Models::InstalledGame* ResolveVisibleGame( DWORD visibleIndex ) const;

    Services::InstalledGameService& m_library;
    Platform::LaunchService& m_launcher;
    DWORD m_visibleIndices[ Services::InstalledGameService::MaximumGames ];
    DWORD m_visibleCount;
    Models::GameCategory m_selectedCategory;
};

} // namespace Adapters
} // namespace Blade
