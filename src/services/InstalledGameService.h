#pragma once

#include <xtl.h>

#include "models/InstalledGame.h"

namespace Blade
{
namespace Services
{

class InstalledGameService
{
public:
    enum ScanState
    {
        ScanNotStarted = 0,
        ScanRunning,
        ScanReady,
        ScanFailed
    };

    static const DWORD MaximumGames = 64;
    static const DWORD MaximumRoots = 32;

    InstalledGameService();

    void Reset();
    void Scan();

    ScanState State() const;
    DWORD GameCount() const;
    const Models::InstalledGame* GameAt( DWORD index ) const;
    DWORD ConfiguredRootCount() const;
    DWORD ExistingRootCount() const;
    BOOL CapacityReached() const;

private:
    struct ScanRoot
    {
        Models::GameCategory category;
        char path[ MAX_PATH ];
    };

    BOOL LoadConfiguredRoots();
    void AddDefaultRoots();
    HRESULT AddRoot( Models::GameCategory category, const char* path );
    void ScanDirectory(
        Models::GameCategory category,
        const char* directory,
        DWORD depth );
    BOOL AddGame(
        Models::GameCategory category,
        const char* directory,
        const char* imagePath );
    void SortGames();

    static BOOL ParseCategory(
        const char* value,
        Models::GameCategory* category );
    static BOOL IsApprovedLocalPath( const char* path );
    static void Trim( char* value );
    static void GetDirectoryDisplayName(
        const char* directory,
        WCHAR* destination,
        size_t destinationCount );

    ScanRoot m_roots[ MaximumRoots ];
    Models::InstalledGame m_games[ MaximumGames ];
    DWORD m_rootCount;
    DWORD m_existingRootCount;
    DWORD m_gameCount;
    volatile LONG m_scanState;
    BOOL m_capacityReached;
};

} // namespace Services
} // namespace Blade
