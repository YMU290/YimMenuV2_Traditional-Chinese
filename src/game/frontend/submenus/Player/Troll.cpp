#include "Troll.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildTrollMenu()
	{
		auto menu = std::make_shared<Category>(TR("Troll"));

		auto general = std::make_shared<Group>(TR("General"));
		auto bounty = std::make_shared<Group>(TR("Bounty"), 1);
		auto vehicle = std::make_shared<Group>(TR("Vehicle"));

		general->AddItem(std::make_shared<PlayerCommandItem>("sendsext"_J,TR("Send Sext")));
		general->AddItem(std::make_shared<PlayerCommandItem>("sendphantomcar"_J,TR("Send Phantom Car")));
		general->AddItem(std::make_shared<PlayerCommandItem>("sendgooch"_J,TR("Send Gooch")));
		general->AddItem(std::make_shared<PlayerCommandItem>("giveplayerallweapon"_J,TR("Give Player All Weapon")));

		bounty->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, TR("Amount")));
		bounty->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, TR("Anonymous")));
		bounty->AddItem(std::make_shared<PlayerCommandItem>("setbounty"_J,TR("Set Bounty")));

		vehicle->AddItem(std::make_shared<PlayerCommandItem>("deleteveh"_J,TR("Delete Vehicle")));

		menu->AddItem(general);
		menu->AddItem(bounty);
		menu->AddItem(vehicle);

		return menu;
	}
}