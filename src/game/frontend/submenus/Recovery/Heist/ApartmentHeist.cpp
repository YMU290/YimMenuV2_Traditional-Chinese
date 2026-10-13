#include "ApartmentHeist.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderApartmentHeistMenu()
	{
		auto tab = std::make_shared<TabItem>(TR("Apartment Heist"));

		auto cuts = std::make_shared<Group>(TR("Heist Cuts"), 2);
		auto setups = std::make_shared<Group>(TR("Heist Setups"));
		auto misc = std::make_shared<Group>(TR("Misc"), 1);
        auto bonus = std::make_shared<Group>(TR("Pacific Bonus"), 1); 

		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut1"_J,TR("Player 1")));
		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut3"_J,TR("Player 3")));
		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut2"_J, TR("Player 2")));
		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut4"_J,TR("Player 4")));
		cuts->AddItem(std::make_shared<CommandItem>("apartmentheistforceready"_J,TR("Force Ready")));
		cuts->AddItem(std::make_shared<CommandItem>("apartmentheistsetcuts"_J,TR("Set Cuts")));

		setups->AddItem(std::make_shared<CommandItem>("apartmentheistsetup"_J,TR("Setup")));

		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskiphacking"_J,TR("Skip Hacking")));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskipdrilling"_J,TR("Skip Drilling")));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskipswiping"_J,TR("Skip Swiping")));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistinstantfinish"_J,TR("Instant Finish")));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistinstantfinishpacific"_J,TR("Instant Finish (Pacific)")));
		
        bonus->AddItem(std::make_shared<CommandItem>("pacificbonus"_J,TR("Pacific 12mil Bonus")));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(misc);
        tab->AddItem(bonus); 

		return tab;
	}
}