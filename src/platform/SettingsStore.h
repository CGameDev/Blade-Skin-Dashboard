#pragma once

#include <xtl.h>

namespace Blade
{
namespace Platform
{

struct DashboardSettings
{
    DWORD version;
    BOOL diagnosticsEnabled;
    DWORD consoleTestBootCount;
};

class SettingsStore
{
public:
    SettingsStore();

    HRESULT Load();
    HRESULT Save();
    void ResetToDefaults();

    const DashboardSettings& Current() const;
    DashboardSettings& Edit();

    static const char* DefaultPath();

private:
    DashboardSettings m_settings;
    BOOL m_dirty;
};

} // namespace Platform
} // namespace Blade
