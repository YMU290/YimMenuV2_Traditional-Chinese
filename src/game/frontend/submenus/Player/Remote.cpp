#include "Remote.hpp"
#include "core/localization/Translator.hpp"
namespace YimMenu::Submenus
{
    std::shared_ptr<Category> BuildRemoteMenu()
    {
        auto menu = std::make_shared<Category>(TR("Remote"));

        auto actions = std::make_shared<Group>(TR("Actions"), 1);
        actions->AddItem(std::make_shared<PlayerCommandItem>("ceokick"_J,TR("CEO Kick")));
        actions->AddItem(std::make_shared<PlayerCommandItem>("sendpizza"_J,TR("Send to Pizza")));

        auto missions = std::make_shared<Group>(TR("Force Mission"));
        missions->AddItem(std::make_shared<ListCommandItem>("forcemissiontype"_J,TR("Force Mission Type")));
        missions->AddItem(std::make_shared<PlayerCommandItem>("forcemission"_J,TR("Force Into Mission")));


        auto notifications = std::make_shared<Group>(TR("Notifications"));
        notifications->AddItem(std::make_shared<ListCommandItem>("notificationtype"_J,TR("Notification Type")));
        notifications->AddItem(std::make_shared<PlayerCommandItem>("sendnotification"_J,TR("Send Notification")));

        menu->AddItem(actions);
		menu->AddItem(missions);
        menu->AddItem(notifications);

        return menu;
    }
}
