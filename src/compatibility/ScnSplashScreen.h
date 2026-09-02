#pragma once

#include <xtl.h>
#include <xui.h>
#include <xuiapp.h>

namespace Blade
{
namespace Compatibility
{

class ScnSplashScreen : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnSplashScreen, L"ScnSplashScreen", XUI_CLASS_SCENE )
};

} // namespace Compatibility
} // namespace Blade
