#include "platform/ControllerInput.h"

namespace Blade
{
namespace Platform
{

ControllerInput::ControllerInput()
    : m_started( FALSE )
{
    ZeroMemory( m_previous, sizeof( m_previous ) );
    ZeroMemory( m_current, sizeof( m_current ) );
    ZeroMemory( m_connected, sizeof( m_connected ) );
}

HRESULT ControllerInput::Start()
{
    ZeroMemory( m_previous, sizeof( m_previous ) );
    ZeroMemory( m_current, sizeof( m_current ) );
    ZeroMemory( m_connected, sizeof( m_connected ) );
    m_started = TRUE;
    Poll();
    return S_OK;
}

void ControllerInput::Stop()
{
    m_started = FALSE;
    ZeroMemory( m_previous, sizeof( m_previous ) );
    ZeroMemory( m_current, sizeof( m_current ) );
    ZeroMemory( m_connected, sizeof( m_connected ) );
}

void ControllerInput::Poll()
{
    if( !m_started )
        return;

    for( DWORD userIndex = 0; userIndex < XUSER_MAX_COUNT; ++userIndex )
    {
        m_previous[ userIndex ] = m_current[ userIndex ];
        ZeroMemory( &m_current[ userIndex ], sizeof( XINPUT_STATE ) );
        m_connected[ userIndex ] =
            XInputGetState( userIndex, &m_current[ userIndex ] ) == ERROR_SUCCESS;
    }
}

BOOL ControllerInput::IsConnected( DWORD userIndex ) const
{
    return userIndex < XUSER_MAX_COUNT ? m_connected[ userIndex ] : FALSE;
}

WORD ControllerInput::PressedButtons( DWORD userIndex ) const
{
    if( userIndex >= XUSER_MAX_COUNT || !m_connected[ userIndex ] )
        return 0;

    return static_cast< WORD >(
        m_current[ userIndex ].Gamepad.wButtons &
        ~m_previous[ userIndex ].Gamepad.wButtons );
}

} // namespace Platform
} // namespace Blade
