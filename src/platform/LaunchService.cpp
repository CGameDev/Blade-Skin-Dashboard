#include "platform/LaunchService.h"

namespace Blade
{
namespace Platform
{

LaunchService::LaunchService()
{
    Clear();
}

HRESULT LaunchService::QueueLaunch( const char* imagePath )
{
    if( imagePath == NULL || imagePath[ 0 ] == '\0' )
        return E_INVALIDARG;

    if( strcpy_s( m_imagePath, ARRAYSIZE( m_imagePath ), imagePath ) != 0 )
    {
        Clear();
        return E_INVALIDARG;
    }

    return S_OK;
}

void LaunchService::Clear()
{
    ZeroMemory( m_imagePath, sizeof( m_imagePath ) );
}

BOOL LaunchService::HasPendingLaunch() const
{
    return m_imagePath[ 0 ] != '\0';
}

HRESULT LaunchService::CopyPendingPath( char* destination, size_t destinationSize ) const
{
    if( destination == NULL || destinationSize == 0 )
        return E_POINTER;
    if( !HasPendingLaunch() )
        return S_FALSE;
    return strcpy_s( destination, destinationSize, m_imagePath ) == 0 ? S_OK : E_FAIL;
}

void LaunchService::DispatchPending() const
{
    if( HasPendingLaunch() )
        XLaunchNewImage( m_imagePath, XLAUNCH_FLAG_CLEAR_LAUNCH_DATA );
}

} // namespace Platform
} // namespace Blade
