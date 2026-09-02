#pragma once

#include <xtl.h>

namespace Blade
{
namespace Services
{

class IRuntimeService
{
public:
    virtual ~IRuntimeService() {}
    virtual HRESULT Start() = 0;
    virtual void Stop() = 0;
};

} // namespace Services
} // namespace Blade
