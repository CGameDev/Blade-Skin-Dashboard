#pragma once

#include <xtl.h>

namespace Blade
{
namespace Models
{

enum GameCategory
{
    GameCategoryXbox360 = 0,
    GameCategoryXboxLiveArcade,
    GameCategoryXboxClassic,
    GameCategoryEmulators,
    GameCategoryHomebrew,
    GameCategoryCount
};

struct InstalledGame
{
    GameCategory category;
    WCHAR displayName[ 128 ];
    char imagePath[ MAX_PATH ];
};

const char* GetGameCategoryLogName( GameCategory category );

} // namespace Models
} // namespace Blade
