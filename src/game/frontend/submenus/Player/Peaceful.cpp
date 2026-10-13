#include "Peaceful.hpp"
#include "game/frontend/items/Items.hpp"
#include "core/localization/Translator.hpp"
namespace YimMenu::Submenus
{
    std::shared_ptr<Category> BuildPeacefulMenu()
    {
        auto menu = std::make_shared<Category>(TR("Peaceful"));

        auto friendly = std::make_shared<Group>(TR("Friendly"), 1);

        friendly->AddItem(std::make_shared<PlayerCommandItem>("copyoutfit"_J,TR("Copy Outfit")));

        menu->AddItem(friendly);

        return menu;
    }
}
