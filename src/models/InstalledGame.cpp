#include "models/InstalledGame.h"

namespace Blade
{
namespace Models
{

const char* GetGameCategoryLogName( GameCategory category )
{
    switch( category )
    {
    case GameCategoryXbox360:
        return "XBOX360";
    case GameCategoryXboxLiveArcade:
        return "XBLA";
    case GameCategoryXboxClassic:
        return "XBOXCLASSIC";
    case GameCategoryEmulators:
        return "EMULATORS";
    case GameCategoryHomebrew:
        return "HOMEBREW";
    default:
        return "UNKNOWN";
    }
}

} // namespace Models
} // namespace Blade
