#pragma once

#include <xtl.h>

#include "services/IRuntimeService.h"

namespace Blade
{
namespace Platform
{

class StorageAliasService : public Services::IRuntimeService
{
public:
    StorageAliasService();

    virtual HRESULT Start();
    virtual void Stop();

    DWORD AvailableAliasCount() const;
    DWORD CreatedAliasCount() const;

private:
    BOOL m_started;
    DWORD m_availableAliasCount;
    DWORD m_createdAliasCount;
};

} // namespace Platform
} // namespace Blade
