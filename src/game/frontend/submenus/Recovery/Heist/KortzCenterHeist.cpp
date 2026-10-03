#include "KortzCenterHeist.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderKortzCenterHeistMenu()
	{
		auto tab = std::make_shared<TabItem>(TR("Kortz Center Heist"));

		auto target    = std::make_shared<Group>(TR("Primary Target"), 1);
		auto general   = std::make_shared<Group>(TR("General"), 2);
		auto preps     = std::make_shared<Group>(TR("Prep Work"), 2);
		auto scoping   = std::make_shared<Group>(TR("Scoping"), 2);
		auto action    = std::make_shared<Group>("", 1);
		auto misc = std::make_shared<Group>(TR("Misc"), 1);

		target->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistprimarytarget"_J,TR("Primary Target")));

		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutes"_J,TR("Guard routes")));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutter"_J,TR("Glass Cutter")));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrills"_J,TR("Power Drills")));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistempcharges"_J,TR("EMP Charges")));

		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopeout"_J,TR("Scope Out")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistalphamail"_J,TR("Alpha Mail")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthazmat"_J,TR("Hazmat Suit")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheiststaffkeycard"_J,TR("Staff Keycard")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisttacticalequip"_J,TR("Tactical Equipment")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthackingdevice"_J,TR("Hacking Device")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistaccesscode"_J,TR("Access Code")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistunmarkedweapons"_J,TR("Unmarked Weapons")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistcaracara"_J,TR("Caracara")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistannihilator"_J,TR("Annihilator")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanchez"_J,TR("Manchez")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistprepemp"_J,TR("Prep EMP")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardshipments"_J,TR("Guard Shipments")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutesprep"_J,TR("Guard Routes Prep")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutterprep"_J,TR("Glass Cutter Prep")));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrillsprep"_J,TR("Power Drills Prep")));

		scoping->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopesecondary"_J,TR("Secondary Scope")));
		scoping->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopepoi"_J,TR("Scope POI")));

		action->AddItem(std::make_shared<CommandItem>("kortzcenterheistsetup"_J, TR("Setup##kortz")));

		misc->AddItem(std::make_shared<CommandItem>("kortz_skip_fingerprint_hack"_J, TR("Skip Fingerprint Hacking")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_skip_Signal_Nodes_hack"_J, TR("Skip Signal Nodes Hacking")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_take_primary"_J, TR("Take Primary Target")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_take_secondary"_J, TR("Take Secondary Target")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_disablelasergrid"_J, TR("Disable Laser Grid")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_skipdatacrack"_J, TR("Skip Data Crack")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_cutglass"_J, TR("Cut Glass")));
		misc->AddItem(std::make_shared<CommandItem>("kortz_centercooldowns"_J, TR("Kortz Center Cooldowns")));
		misc->AddItem(std::make_shared<BoolCommandItem>("kortz_centerpayouts"_J, TR("Kortz Center Payouts")));
        misc->AddItem(std::make_shared<CommandItem>("kortzcenterheistautoenterpcaccesscode"_J,TR("Auto-Enter PC Access Code")));

		tab->AddItem(target);
		tab->AddItem(general);
		tab->AddItem(preps);
		tab->AddItem(scoping);
		tab->AddItem(action);
		tab->AddItem(misc);

		return tab;
	}
}