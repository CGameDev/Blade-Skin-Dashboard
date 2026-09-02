#include "diagnostics/DebugLog.h"

#include <stdio.h>

namespace Blade
{
namespace Diagnostics
{

namespace
{
FILE* g_logFile = NULL;
const char LogDirectory[] = "game:\\Logs";
const char LogPath[] = "game:\\Logs\\blade_dashboard.log";
}

HRESULT Initialize()
{
    if( g_logFile != NULL )
        return S_FALSE;

    if( !CreateDirectoryA( LogDirectory, NULL ) && GetLastError() != ERROR_ALREADY_EXISTS )
        return HRESULT_FROM_WIN32( GetLastError() );

    if( fopen_s( &g_logFile, LogPath, "a" ) != 0 || g_logFile == NULL )
        return E_FAIL;

    return S_OK;
}

void Shutdown()
{
    if( g_logFile != NULL )
    {
        fflush( g_logFile );
        fclose( g_logFile );
        g_logFile = NULL;
    }
}

void Write( const char* message )
{
    const char* safeMessage = message != NULL ? message : "<null>";
    OutputDebugStringA( "[BladeDashboard] " );
    OutputDebugStringA( safeMessage );
    OutputDebugStringA( "\n" );

    if( g_logFile != NULL )
    {
        fprintf( g_logFile, "[BladeDashboard] %s\n", safeMessage );
        fflush( g_logFile );
    }
}

void WriteFailure( const char* operation, HRESULT result )
{
    char buffer[ 256 ];
    sprintf_s(
        buffer,
        ARRAYSIZE( buffer ),
        "%s failed (HRESULT=0x%08X)",
        operation != NULL ? operation : "Operation",
        static_cast< unsigned int >( result ) );
    Write( buffer );
}

} // namespace Diagnostics
} // namespace Blade
