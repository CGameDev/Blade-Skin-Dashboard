#pragma once

#include <xtl.h>

#include "services/IRuntimeService.h"

namespace Blade
{
namespace Platform
{

class ControllerInput : public Services::IRuntimeService
{
public:
    ControllerInput();

    virtual HRESULT Start();
    virtual void Stop();

    void Poll();
    BOOL IsConnected( DWORD userIndex ) const;
    WORD PressedButtons( DWORD userIndex ) const;

private:
    XINPUT_STATE m_previous[ XUSER_MAX_COUNT ];
    XINPUT_STATE m_current[ XUSER_MAX_COUNT ];
    BOOL m_connected[ XUSER_MAX_COUNT ];
    BOOL m_started;
};

} // namespace Platform
} // namespace Blade
