#include "Toxic.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildKickMenu()
	{
		auto menu = std::make_shared<Category>(TR("Kick"));

		auto kicks = std::make_shared<Group>(TR("Kicks"));
		//kicks->AddItem(std::make_shared<PlayerCommandItem>("hkick"_J));
		//kicks->AddItem(std::make_shared<PlayerCommandItem>("shkick"_J));
		//kicks->AddItem(std::make_shared<PlayerCommandItem>("endkick"_J));
		//kicks->AddItem(std::make_shared<PlayerCommandItem>("nfkick"_J));

		kicks->AddItem(std::make_shared<PlayerCommandItem>("hkick"_J,TR("Hosts Kick")));
		kicks->AddItem(std::make_shared<PlayerCommandItem>("shkick"_J,TR("Script Host Kick")));
		kicks->AddItem(std::make_shared<PlayerCommandItem>("endkick"_J,TR("Freemode State Kick")));
		kicks->AddItem(std::make_shared<PlayerCommandItem>("nfkick"_J,TR("Null Function Kick")));

		auto other = std::make_shared<Group>(TR("Other"));
		other->AddItem(std::make_shared<PlayerCommandItem>("blackscreen"_J,TR("Blackscreen")));

		menu->AddItem(kicks);
		menu->AddItem(other);

		return menu;
	}
}