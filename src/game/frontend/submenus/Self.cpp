#include "Self.hpp"
#include "core/util/Joaat.hpp"
#include "game/frontend/items/Items.hpp"
#include "Self/OutfitEditor.hpp"
#include "Self/Weapons.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	Self::Self() :
		#define ICON_FA_USER "\xef\x80\x87"
	    Submenu::Submenu(TR("Self"), ICON_FA_USER)
	{
		auto main = std::make_shared<Category>(TR("Main"));
		auto globalsGroup = std::make_shared<Group>(TR("Globals"));
		auto movementGroup = std::make_shared<Group>(TR("Movement"));
		auto toolsGroup = std::make_shared<Group>(TR("Tools"), 2);
		auto specialAbilityGroup = std::make_shared<Group>(TR("Special Ability"));
		auto wantedGroup = std::make_shared<Group>(TR("Wanted"));

		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("godmode"_J,TR("Godmode")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("invis"_J,TR("invisible")));
		globalsGroup->AddItem(std::make_shared<ConditionalItem>("invis"_J, std::make_shared<BoolCommandItem>("localvis"_J,TR("localvis"))));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("otr"_J,TR("Otr")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noragdoll"_J,TR("Noragdoll")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noidlekick"_J,TR("NoIdleKick")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("unlimitedoxygen"_J,TR("Unlimite Doxygen")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("formatmoney"_J, TR("Format Money")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("mobileradio"_J,TR("Mobile Radio")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("keepplayerclean"_J,TR("Keep Player Clean")));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("disablecriticalhits"_J,TR("Disable Critical Hits")));

		toolsGroup->AddItem(std::make_shared<CommandItem>("skipcutscene"_J,TR("Skip Cut Scene")));
		toolsGroup->AddItem(std::make_shared<CommandItem>("skipconversation"_J,TR("Skip Conversation")));
		toolsGroup->AddItem(std::make_shared<CommandItem>("suicide"_J,TR("Suicide")));
		toolsGroup->AddItem(std::make_shared<CommandItem>("heal"_J,TR("Heal")));
		toolsGroup->AddItem(std::make_shared<CommandItem>("cleardamage"_J,TR("Clear Damage")));
		toolsGroup->AddItem(std::make_shared<CommandItem>("fillinventory"_J,TR("Fill Inventory")));
		toolsGroup->AddItem(std::make_shared<CommandItem>("openwardrobe"_J,TR("Open Wardrobe")));

		auto clearWanted = std::make_shared<Group>("", 1);
		clearWanted->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, std::make_shared<CommandItem>("clearwanted"_J,TR("clearwanted")), true));
		clearWanted->AddItem(std::make_shared<BoolCommandItem>("neverwanted"_J,TR("Never Wanted")));
		auto setWanted = std::make_shared<Group>("", 1);
		setWanted->AddItem(std::make_shared<IntCommandItem>("wantedslider"_J, TR("wantedslider")));
		setWanted->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, std::make_shared<CommandItem>("setwanted"_J, TR("setwanted")), true));
		setWanted->AddItem(std::make_shared<BoolCommandItem>("freezewanted"_J,TR("Freeze Wanted")));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, clearWanted, true));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, setWanted, true));

		movementGroup->AddItem(std::make_shared<BoolCommandItem>("standonvehicles"_J,TR("Standon Vehicles")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("disableactionmode"_J,TR("Disable Action Mode")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("superrun"_J,TR("Super Run")));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("superrun"_J, std::make_shared<FloatCommandItem>("moverateoverride"_J, TR("moverateoverride", std::nullopt, false))));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("superrun"_J, std::make_shared<FloatCommandItem>("runsprintswimmultiplier"_J, TR("runsprintswimmultiplier", std::nullopt, false))));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("superjump"_J,TR("Super Jump")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("megajump"_J,TR("Mega Jump")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("fastswim"_J,TR("Fast Swim")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("fastdive"_J,TR("Fast Dive")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("swiminair"_J,TR("Swim In Air")));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("noclip"_J,TR("Noclip")));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("noclip"_J, std::make_shared<FloatCommandItem>("noclipspeed"_J,TR("noclipspeed"))));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("freecam"_J,TR("Freecam")));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("freecam"_J, std::make_shared<FloatCommandItem>("freecamspeed"_J,TR("freecamspeed"))));

		specialAbilityGroup->AddItem(std::make_shared<BoolCommandItem>("infspecialability"_J,TR("Inf Special Ability")));
		auto specialInMp = std::make_shared<Group>("", 1);
		specialInMp->AddItem(std::make_shared<BoolCommandItem>("mpspecialability"_J, TR("mpspecialability")));
		specialInMp->AddItem(std::make_shared<ConditionalItem>("mpspecialability"_J, std::make_shared<ListCommandItem>("selspecialability"_J, TR("selspecialability"))));
		specialAbilityGroup->AddItem(std::move(specialInMp));

		main->AddItem(globalsGroup);
		main->AddItem(toolsGroup);
		main->AddItem(specialAbilityGroup);
		main->AddItem(wantedGroup);
		main->AddItem(movementGroup);
		AddCategory(std::move(main));

		AddCategory(BuildWeaponsMenu());

		auto outfitEditorCategory = YimMenu::CreateOutfitsMenu();
		AddCategory(std::move(outfitEditorCategory));
	}
}