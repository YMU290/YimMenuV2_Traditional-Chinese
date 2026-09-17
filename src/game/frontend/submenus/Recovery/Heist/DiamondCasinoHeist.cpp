#include "DiamondCasinoHeist.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderDiamondCasinoHeistMenu()
	{
		auto tab = std::make_shared<TabItem>(TR("Diamond Casino Heist"));

		auto cuts = std::make_shared<Group>(TR("Heist Cuts"), 2);
		auto setups = std::make_shared<Group>(TR("Heist Setups"));
		auto loots = std::make_shared<Group>(TR("Loots"), 2);
		auto misc = std::make_shared<Group>(TR("Misc"), 1);

		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut1"_J,TR("Player 1")));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut3"_J,TR("Player 3")));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut2"_J,TR("Player 2")));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut4"_J,TR("Player 4")));
		cuts->AddItem(std::make_shared<CommandItem>("diamondcasinoheistforceready"_J,TR("Force Ready")));
		cuts->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetcuts"_J,TR("Set Cuts")));

		auto gunmanAndDriver = std::make_shared<Group>("", 2);
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistgunman"_J,TR("Gunman")));
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistdriver"_J,TR("Driver")));
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistweapon"_J,TR("Weapon")));
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistvehicle"_J,TR("Vehicle")));

		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistdifficulty"_J,TR("Difficulty")));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistprimarytarget"_J,TR("Primary Target")));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistapproach"_J,TR("Approach")));
		setups->AddItem(std::move(gunmanAndDriver));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheisthacker"_J,TR("Hacker")));
		setups->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetup"_J,TR("Setup")));

		loots->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistpotentialtake"_J,TR("Potential Take")));
		loots->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistactualtake"_J,TR("Actual Take")));
		loots->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetpotentialtake"_J,(std::string(TR("Set")) + "##potentialtake").c_str()));
		loots->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetactualtake"_J,(std::string(TR("Set")) + "##actualtake").c_str()));

		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistskiphacking"_J,TR("Skip Hack")));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistskipdrilling"_J,TR("Skip Drilling")));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsolomantrap"_J,TR("Solo Mantrap")));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistinstantfinish"_J,TR("Instant Finish")));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistremovecameras"_J,TR("Remove Cam")));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistkeycard"_J,TR("Remove Keycard")));
		misc->AddItem(std::make_shared<BoolCommandItem>("autocollecttargets"_J,TR("Auto Collect Targets")));
		misc->AddItem(std::make_shared<BoolCommandItem>("diamondcasinoheistautograb"_J, TR("Auto-Grab")));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(loots);
		tab->AddItem(misc);

		return tab;
	}
}