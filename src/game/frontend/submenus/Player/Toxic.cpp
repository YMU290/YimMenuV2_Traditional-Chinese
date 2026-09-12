#include "Toxic.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildToxicMenu()
	{
		auto menu = std::make_shared<Category>(TR("Toxic"));

		auto damage = std::make_shared<Group>(TR("Damage"), 1);
		damage->AddItem(std::make_shared<PlayerCommandItem>("kill"_J,TR("Kill")));
		damage->AddItem(std::make_shared<PlayerCommandItem>("killexploit"_J,TR("Permadeath")));
		damage->AddItem(std::make_shared<PlayerCommandItem>("explode"_J,TR("Explode")));

		auto griefing = std::make_shared<Group>(TR("Griefing"));
		griefing->AddItem(std::make_shared<PlayerCommandItem>("ceokick"_J,TR("CEO Kick")));

		auto force = std::make_shared<Group>(TR("Magnet/Forcefield"));
		force->AddItem(std::make_shared<BoolCommandItem>("magnet"_J, TR("Magnet")));
		force->AddItem(std::make_shared<FloatCommandItem>("magnetradius"_J, TR("Magnet Radius"), false));
		force->AddItem(std::make_shared<FloatCommandItem>("magnetmagnitude"_J, TR("Magnet Magnitude"), false));
		force->AddItem(std::make_shared<BoolCommandItem>("forcefield"_J, TR("Forcefield")));
		force->AddItem(std::make_shared<FloatCommandItem>("forcefieldradius"_J, TR("Forcefield Radius"), false));
		force->AddItem(std::make_shared<FloatCommandItem>("forcefieldmagnitude"_J, TR("Forcefield Magnitude"), false));

		menu->AddItem(damage);
		menu->AddItem(griefing);
		menu->AddItem(force);

		return menu;
	}
}