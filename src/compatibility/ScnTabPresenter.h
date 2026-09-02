#pragma once

#include <xtl.h>
#include <xui.h>
#include <xuiapp.h>

namespace Blade
{
namespace Compatibility
{

class ScnTabPresenter : public CXuiSceneImpl
{
public:
    XUI_IMPLEMENT_CLASS( ScnTabPresenter, L"ScnTabPresenter", XUI_CLASS_SCENE )
};

} // namespace Compatibility
} // namespace Blade
