#pragma once

#include <xtl.h>

namespace Blade
{
namespace Diagnostics
{

HRESULT Initialize();
void Shutdown();
void Write( const char* message );
void WriteFailure( const char* operation, HRESULT result );

} // namespace Diagnostics
} // namespace Blade
