#include "platform/SettingsStore.h"

#include <stdio.h>

namespace Blade
{
namespace Platform
{

namespace
{
const DWORD SettingsMagic = 0x42445331;
const DWORD SettingsVersion = 3;

struct SettingsFile
{
    DWORD magic;
    DashboardSettings settings;
};
}

SettingsStore::SettingsStore()
    : m_dirty( FALSE )
{
    ResetToDefaults();
    m_dirty = FALSE;
}

HRESULT SettingsStore::Load()
{
    FILE* file = NULL;
    if( fopen_s( &file, DefaultPath(), "rb" ) != 0 || file == NULL )
    {
        ResetToDefaults();
        return S_FALSE;
    }

    SettingsFile stored;
    ZeroMemory( &stored, sizeof( stored ) );
    const size_t readCount = fread( &stored, sizeof( stored ), 1, file );
    fclose( file );

    if( readCount != 1 ||
        stored.magic != SettingsMagic ||
        stored.settings.version != SettingsVersion )
    {
        ResetToDefaults();
        return E_FAIL;
    }

    m_settings = stored.settings;
    m_dirty = FALSE;
    return S_OK;
}

HRESULT SettingsStore::Save()
{
    if( !m_dirty )
        return S_FALSE;

    if( !CreateDirectoryA( "game:\\Config", NULL ) && GetLastError() != ERROR_ALREADY_EXISTS )
        return HRESULT_FROM_WIN32( GetLastError() );

    FILE* file = NULL;
    if( fopen_s( &file, DefaultPath(), "wb" ) != 0 || file == NULL )
        return E_FAIL;

    SettingsFile stored;
    stored.magic = SettingsMagic;
    stored.settings = m_settings;
    const size_t writeCount = fwrite( &stored, sizeof( stored ), 1, file );
    const int closeResult = fclose( file );
    if( writeCount != 1 || closeResult != 0 )
        return E_FAIL;

    m_dirty = FALSE;
    return S_OK;
}

void SettingsStore::ResetToDefaults()
{
    m_settings.version = SettingsVersion;
    m_settings.diagnosticsEnabled = TRUE;
    m_settings.consoleTestBootCount = 0;
    m_dirty = TRUE;
}

const DashboardSettings& SettingsStore::Current() const
{
    return m_settings;
}

DashboardSettings& SettingsStore::Edit()
{
    m_dirty = TRUE;
    return m_settings;
}

const char* SettingsStore::DefaultPath()
{
    return "game:\\Config\\blade_dashboard.settings";
}

} // namespace Platform
} // namespace Blade
