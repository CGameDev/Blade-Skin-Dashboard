#pragma once

#include <xtl.h>

namespace Blade
{
namespace Platform
{

class LaunchService
{
public:
    LaunchService();

    HRESULT QueueLaunch( const char* imagePath );
    void Clear();
    BOOL HasPendingLaunch() const;
    HRESULT CopyPendingPath( char* destination, size_t destinationSize ) const;
    void DispatchPending() const;

private:
    char m_imagePath[ MAX_PATH ];
};

} // namespace Platform
} // namespace Blade
