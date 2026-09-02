#include "platform/StorageAliasService.h"

#include "diagnostics/DebugLog.h"

#include <stdio.h>

namespace Blade
{
namespace Platform
{

namespace
{
typedef struct _BLADE_ANSI_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PCHAR Buffer;
} BLADE_ANSI_STRING, *PBLADE_ANSI_STRING;

extern "C"
{
    VOID RtlInitAnsiString(
        PBLADE_ANSI_STRING destination,
        PCHAR source );
    HRESULT ObDeleteSymbolicLink(
        PBLADE_ANSI_STRING symbolicLinkName );
    HRESULT ObCreateSymbolicLink(
        PBLADE_ANSI_STRING symbolicLinkName,
        PBLADE_ANSI_STRING deviceName );
}

struct StorageAlias
{
    const char* name;
    const char* target;
};

const StorageAlias StorageAliases[] =
{
    { "Hdd:", "\\Device\\Harddisk0\\Partition1" },
    { "Hdd1:", "\\Device\\Harddisk0\\Partition1" },
    { "Usb0:", "\\Device\\Mass0" },
    { "Usb1:", "\\Device\\Mass1" },
    { "Usb2:", "\\Device\\Mass2" }
};

BOOL IsDirectory( const char* path )
{
    const DWORD attributes = GetFileAttributesA( path );
    return attributes != static_cast< DWORD >( -1 ) &&
        ( attributes & FILE_ATTRIBUTE_DIRECTORY ) != 0;
}

HRESULT MountDriveAlias( const char* alias, const char* target )
{
    if( alias == NULL || target == NULL )
        return E_INVALIDARG;

    char linkPath[ 32 ];
    if( sprintf_s(
            linkPath,
            ARRAYSIZE( linkPath ),
            "\\??\\%s",
            alias ) <= 0 )
    {
        return E_INVALIDARG;
    }

    BLADE_ANSI_STRING linkName;
    BLADE_ANSI_STRING deviceName;
    RtlInitAnsiString( &linkName, linkPath );
    RtlInitAnsiString( &deviceName, const_cast< PCHAR >( target ) );
    ObDeleteSymbolicLink( &linkName );
    return ObCreateSymbolicLink( &linkName, &deviceName );
}
}

StorageAliasService::StorageAliasService()
    : m_started( FALSE ),
      m_availableAliasCount( 0 ),
      m_createdAliasCount( 0 )
{
}

HRESULT StorageAliasService::Start()
{
    if( m_started )
        return S_FALSE;

    m_availableAliasCount = 0;
    m_createdAliasCount = 0;

    for( DWORD index = 0; index < ARRAYSIZE( StorageAliases ); ++index )
    {
        const StorageAlias& alias = StorageAliases[ index ];
        char rootPath[ 16 ];
        sprintf_s(
            rootPath,
            ARRAYSIZE( rootPath ),
            "%s\\",
            alias.name );

        const BOOL existed = IsDirectory( rootPath );
        HRESULT mountResult = S_FALSE;
        if( !existed )
        {
            mountResult = MountDriveAlias( alias.name, alias.target );
            if( SUCCEEDED( mountResult ) )
                ++m_createdAliasCount;
        }

        const BOOL available = IsDirectory( rootPath );
        if( available )
            ++m_availableAliasCount;

        char message[ 256 ];
        sprintf_s(
            message,
            ARRAYSIZE( message ),
            "Storage alias: alias=%s target=%s existed=%u created=%u available=%u result=0x%08X.",
            alias.name,
            alias.target,
            existed ? 1u : 0u,
            !existed && SUCCEEDED( mountResult ) ? 1u : 0u,
            available ? 1u : 0u,
            static_cast< unsigned int >( mountResult ) );
        Diagnostics::Write( message );
    }

    m_started = TRUE;
    return S_OK;
}

void StorageAliasService::Stop()
{
    // Keep aliases alive through the post-XUI XLaunchNewImage dispatch. The
    // title process owns their remaining lifetime.
    m_started = FALSE;
}

DWORD StorageAliasService::AvailableAliasCount() const
{
    return m_availableAliasCount;
}

DWORD StorageAliasService::CreatedAliasCount() const
{
    return m_createdAliasCount;
}

} // namespace Platform
} // namespace Blade
