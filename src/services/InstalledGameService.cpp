#include "services/InstalledGameService.h"

#include <stdio.h>

namespace Blade
{
namespace Services
{

namespace
{
const char LibraryRootsPath[] = "game:\\Config\\library_roots.txt";
const DWORD MaximumScanDepth = 4;

BOOL IsDirectory( const char* path )
{
    const DWORD attributes = GetFileAttributesA( path );
    return attributes != static_cast< DWORD >( -1 ) &&
        ( attributes & FILE_ATTRIBUTE_DIRECTORY ) != 0;
}

BOOL IsFile( const char* path )
{
    const DWORD attributes = GetFileAttributesA( path );
    return attributes != static_cast< DWORD >( -1 ) &&
        ( attributes & FILE_ATTRIBUTE_DIRECTORY ) == 0;
}

BOOL EqualsIgnoreCase( const char* left, const char* right )
{
    return left != NULL && right != NULL && _stricmp( left, right ) == 0;
}
}

InstalledGameService::InstalledGameService()
{
    Reset();
}

void InstalledGameService::Reset()
{
    ZeroMemory( m_roots, sizeof( m_roots ) );
    ZeroMemory( m_games, sizeof( m_games ) );
    m_rootCount = 0;
    m_existingRootCount = 0;
    m_gameCount = 0;
    m_capacityReached = FALSE;
    InterlockedExchange( &m_scanState, ScanNotStarted );
}

void InstalledGameService::Scan()
{
    if( InterlockedCompareExchange(
            &m_scanState,
            ScanRunning,
            ScanNotStarted ) != ScanNotStarted )
    {
        return;
    }

    if( !LoadConfiguredRoots() )
        AddDefaultRoots();

    if( m_rootCount == 0 )
    {
        InterlockedExchange( &m_scanState, ScanFailed );
        return;
    }

    for( DWORD index = 0; index < m_rootCount; ++index )
    {
        if( m_capacityReached )
            break;

        const ScanRoot& root = m_roots[ index ];
        if( !IsDirectory( root.path ) )
            continue;

        ++m_existingRootCount;
        ScanDirectory( root.category, root.path, 0 );
    }

    SortGames();
    InterlockedExchange( &m_scanState, ScanReady );
}

InstalledGameService::ScanState InstalledGameService::State() const
{
    return static_cast< ScanState >(
        InterlockedCompareExchange(
            const_cast< volatile LONG* >( &m_scanState ),
            0,
            0 ) );
}

DWORD InstalledGameService::GameCount() const
{
    return State() == ScanReady ? m_gameCount : 0;
}

const Models::InstalledGame* InstalledGameService::GameAt( DWORD index ) const
{
    if( State() != ScanReady || index >= m_gameCount )
        return NULL;
    return &m_games[ index ];
}

DWORD InstalledGameService::ConfiguredRootCount() const
{
    return m_rootCount;
}

DWORD InstalledGameService::ExistingRootCount() const
{
    return m_existingRootCount;
}

BOOL InstalledGameService::CapacityReached() const
{
    return m_capacityReached;
}

BOOL InstalledGameService::LoadConfiguredRoots()
{
    FILE* file = NULL;
    if( fopen_s( &file, LibraryRootsPath, "rb" ) != 0 || file == NULL )
        return FALSE;

    char line[ 512 ];
    while( fgets( line, ARRAYSIZE( line ), file ) != NULL )
    {
        Trim( line );
        if( line[ 0 ] == '\0' || line[ 0 ] == '#' || line[ 0 ] == ';' )
            continue;

        char* separator = strchr( line, '=' );
        if( separator == NULL )
            continue;

        *separator = '\0';
        char* path = separator + 1;
        Trim( line );
        Trim( path );

        Models::GameCategory category;
        if( !ParseCategory( line, &category ) )
            continue;
        AddRoot( category, path );
    }

    fclose( file );
    return m_rootCount != 0;
}

void InstalledGameService::AddDefaultRoots()
{
    const char* devices[] = { "Hdd1:", "Usb0:", "Usb1:", "Usb2:" };
    for( DWORD device = 0; device < ARRAYSIZE( devices ); ++device )
    {
        char path[ MAX_PATH ];

        sprintf_s( path, ARRAYSIZE( path ), "%s\\Games", devices[ device ] );
        AddRoot( Models::GameCategoryXbox360, path );
        AddRoot( Models::GameCategoryXboxClassic, path );

        sprintf_s( path, ARRAYSIZE( path ), "%s\\Xbox1", devices[ device ] );
        AddRoot( Models::GameCategoryXboxClassic, path );

        sprintf_s( path, ARRAYSIZE( path ), "%s\\Apps", devices[ device ] );
        AddRoot( Models::GameCategoryHomebrew, path );

        sprintf_s( path, ARRAYSIZE( path ), "%s\\Emulators", devices[ device ] );
        AddRoot( Models::GameCategoryEmulators, path );

        sprintf_s( path, ARRAYSIZE( path ), "%s\\Emulator", devices[ device ] );
        AddRoot( Models::GameCategoryEmulators, path );
    }
}

HRESULT InstalledGameService::AddRoot(
    Models::GameCategory category,
    const char* path )
{
    if( path == NULL || path[ 0 ] == '\0' || !IsApprovedLocalPath( path ) )
        return E_INVALIDARG;
    if( m_rootCount >= MaximumRoots )
        return E_OUTOFMEMORY;

    char normalized[ MAX_PATH ];
    if( strcpy_s( normalized, ARRAYSIZE( normalized ), path ) != 0 )
        return E_INVALIDARG;

    size_t length = strlen( normalized );
    while( length > 3 &&
        ( normalized[ length - 1 ] == '\\' || normalized[ length - 1 ] == '/' ) )
    {
        normalized[ --length ] = '\0';
    }

    for( DWORD index = 0; index < m_rootCount; ++index )
    {
        if( m_roots[ index ].category == category &&
            EqualsIgnoreCase( m_roots[ index ].path, normalized ) )
        {
            return S_FALSE;
        }
    }

    m_roots[ m_rootCount ].category = category;
    if( strcpy_s(
            m_roots[ m_rootCount ].path,
            ARRAYSIZE( m_roots[ m_rootCount ].path ),
            normalized ) != 0 )
    {
        return E_INVALIDARG;
    }

    ++m_rootCount;
    return S_OK;
}

void InstalledGameService::ScanDirectory(
    Models::GameCategory category,
    const char* directory,
    DWORD depth )
{
    if( directory == NULL || depth > MaximumScanDepth || m_capacityReached )
        return;

    const char* imageName = category == Models::GameCategoryXboxClassic
        ? "default.xbe"
        : "default.xex";

    char imagePath[ MAX_PATH ];
    if( sprintf_s(
            imagePath,
            ARRAYSIZE( imagePath ),
            "%s\\%s",
            directory,
            imageName ) > 0 &&
        IsFile( imagePath ) )
    {
        AddGame( category, directory, imagePath );
        return;
    }

    if( depth == MaximumScanDepth )
        return;

    char searchPath[ MAX_PATH ];
    if( sprintf_s(
            searchPath,
            ARRAYSIZE( searchPath ),
            "%s\\*",
            directory ) <= 0 )
    {
        return;
    }

    WIN32_FIND_DATAA data;
    ZeroMemory( &data, sizeof( data ) );
    HANDLE find = FindFirstFileA( searchPath, &data );
    if( find == INVALID_HANDLE_VALUE )
        return;

    do
    {
        if( m_capacityReached ||
            ( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0 ||
            EqualsIgnoreCase( data.cFileName, "." ) ||
            EqualsIgnoreCase( data.cFileName, ".." ) ||
            EqualsIgnoreCase( data.cFileName, "$SystemUpdate" ) )
        {
            continue;
        }

        char child[ MAX_PATH ];
        if( sprintf_s(
                child,
                ARRAYSIZE( child ),
                "%s\\%s",
                directory,
                data.cFileName ) <= 0 )
        {
            continue;
        }

        ScanDirectory( category, child, depth + 1 );
    }
    while( FindNextFileA( find, &data ) );

    FindClose( find );
}

BOOL InstalledGameService::AddGame(
    Models::GameCategory category,
    const char* directory,
    const char* imagePath )
{
    if( EqualsIgnoreCase( imagePath, "game:\\default.xex" ) )
        return FALSE;

    if( m_gameCount >= MaximumGames )
    {
        m_capacityReached = TRUE;
        return FALSE;
    }

    WCHAR displayName[ 128 ];
    ZeroMemory( displayName, sizeof( displayName ) );
    GetDirectoryDisplayName(
        directory,
        displayName,
        ARRAYSIZE( displayName ) );

    if( _wcsicmp( displayName, L"BladeDashboard" ) == 0 )
        return FALSE;

    for( DWORD index = 0; index < m_gameCount; ++index )
    {
        if( m_games[ index ].category == category &&
            EqualsIgnoreCase( m_games[ index ].imagePath, imagePath ) )
        {
            return FALSE;
        }
    }

    Models::InstalledGame& game = m_games[ m_gameCount ];
    game.category = category;
    if( wcscpy_s(
            game.displayName,
            ARRAYSIZE( game.displayName ),
            displayName ) != 0 ||
        strcpy_s(
            game.imagePath,
            ARRAYSIZE( game.imagePath ),
            imagePath ) != 0 )
    {
        ZeroMemory( &game, sizeof( game ) );
        return FALSE;
    }

    ++m_gameCount;
    return TRUE;
}

void InstalledGameService::SortGames()
{
    for( DWORD index = 1; index < m_gameCount; ++index )
    {
        Models::InstalledGame value = m_games[ index ];
        DWORD insertAt = index;
        while( insertAt > 0 )
        {
            const Models::InstalledGame& previous = m_games[ insertAt - 1 ];
            if( previous.category < value.category ||
                ( previous.category == value.category &&
                  _wcsicmp( previous.displayName, value.displayName ) <= 0 ) )
            {
                break;
            }

            m_games[ insertAt ] = previous;
            --insertAt;
        }
        m_games[ insertAt ] = value;
    }
}

BOOL InstalledGameService::ParseCategory(
    const char* value,
    Models::GameCategory* category )
{
    if( value == NULL || category == NULL )
        return FALSE;

    if( EqualsIgnoreCase( value, "XBOX360" ) )
        *category = Models::GameCategoryXbox360;
    else if( EqualsIgnoreCase( value, "XBLA" ) )
        *category = Models::GameCategoryXboxLiveArcade;
    else if( EqualsIgnoreCase( value, "XBOXCLASSIC" ) )
        *category = Models::GameCategoryXboxClassic;
    else if( EqualsIgnoreCase( value, "EMULATORS" ) )
        *category = Models::GameCategoryEmulators;
    else if( EqualsIgnoreCase( value, "HOMEBREW" ) )
        *category = Models::GameCategoryHomebrew;
    else
        return FALSE;

    return TRUE;
}

BOOL InstalledGameService::IsApprovedLocalPath( const char* path )
{
    const char* approvedPrefixes[] =
    {
        "Hdd:\\",
        "Hdd1:\\",
        "Usb0:\\",
        "Usb1:\\",
        "Usb2:\\",
        "game:\\"
    };

    for( DWORD index = 0; index < ARRAYSIZE( approvedPrefixes ); ++index )
    {
        const size_t prefixLength = strlen( approvedPrefixes[ index ] );
        if( _strnicmp( path, approvedPrefixes[ index ], prefixLength ) == 0 )
            return TRUE;
    }

    return FALSE;
}

void InstalledGameService::Trim( char* value )
{
    if( value == NULL )
        return;

    char* start = value;
    while( *start == ' ' || *start == '\t' || *start == '\r' || *start == '\n' )
        ++start;

    if( start != value )
        memmove( value, start, strlen( start ) + 1 );

    size_t length = strlen( value );
    while( length != 0 )
    {
        const char character = value[ length - 1 ];
        if( character != ' ' && character != '\t' &&
            character != '\r' && character != '\n' )
        {
            break;
        }
        value[ --length ] = '\0';
    }
}

void InstalledGameService::GetDirectoryDisplayName(
    const char* directory,
    WCHAR* destination,
    size_t destinationCount )
{
    if( destination == NULL || destinationCount == 0 )
        return;

    destination[ 0 ] = L'\0';
    if( directory == NULL )
        return;

    const char* name = strrchr( directory, '\\' );
    name = name != NULL ? name + 1 : directory;

    size_t index = 0;
    while( name[ index ] != '\0' && index + 1 < destinationCount )
    {
        destination[ index ] = static_cast< WCHAR >(
            static_cast< unsigned char >( name[ index ] ) );
        ++index;
    }
    destination[ index ] = L'\0';
}

} // namespace Services
} // namespace Blade
