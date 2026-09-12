#include "DoomsdayHeist.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderDoomsdayHeistMenu()
	{
		auto tab = std::make_shared<TabItem>(TR("Doomsday Heist"));

		auto cuts = std::make_shared<Group>(TR("Heist Cuts"), 2);
		auto setups = std::make_shared<Group>(TR("Heist Setups"));
		auto misc = std::make_shared<Group>(TR("Misc"), 1);

		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut1"_J,TR("Player 1")));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut3"_J,TR("Player 3")));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut2"_J,TR("Player 2")));
		cuts->AddItem(std::make_shared<IntCommandItem>("doomsdayheistcut4"_J,TR("Player 4")));
		cuts->AddItem(std::make_shared<CommandItem>("doomsdayheistforceready"_J,TR("Force Ready")));
		cuts->AddItem(std::make_shared<CommandItem>("doomsdayheistsetcuts"_J,TR("Set Cuts")));

		setups->AddItem(std::make_shared<ListCommandItem>("doomsdayheistcategory"_J,TR("Select Heist")));
		setups->AddItem(std::make_shared<CommandItem>("doomsdayheistsetup"_J,TR("Setup")));

		misc->AddItem(std::make_shared<CommandItem>("doomsdayheistskiphacking"_J,TR("Skip Hacking")));
		misc->AddItem(std::make_shared<CommandItem>("doomsdayheistinstantfinish"_J, TR("Instant Finish")));
		misc->AddItem(std::make_shared<CommandItem>("doomsdayheistinstantfinishact3"_J,TR("Instant Finish (Act:III)")));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(misc);

		return tab;
	}
}