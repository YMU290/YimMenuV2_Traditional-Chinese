#include "World.hpp"
#include "game/frontend/items/Items.hpp"
#include "World/SpawnPed.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	World::World() :
		#define ICON_FA_GLOBE "\xef\x82\xac"
	    Submenu::Submenu(TR("World"), ICON_FA_GLOBE)
	{
		auto main = std::make_shared<Category>(TR("Main"));
		auto iplsGroup = std::make_shared<Category>(TR("IPLs"));

		auto killPeds = std::make_shared<Group>(TR("Kill"), 1);
		killPeds->AddItem(std::make_shared<CommandItem>("killallpeds"_J,TR("Kill All Peds")));
		killPeds->AddItem(std::make_shared<CommandItem>("killallenemies"_J,TR("Kill All Enemies")));
		auto deleteOpts = std::make_shared<Group>(TR("Delete"), 2);
		deleteOpts->AddItem(std::make_shared<CommandItem>("delpeds"_J,TR("Delete All Peds")));
		deleteOpts->AddItem(std::make_shared<CommandItem>("delvehs"_J,TR("Delete All Vehicles")));
		deleteOpts->AddItem(std::make_shared<CommandItem>("delobjs"_J,TR("Delete All Objects")));
		deleteOpts->AddItem(std::make_shared<CommandItem>("delcams"_J,TR("Delete All Cameras")));
		auto bringOpts = std::make_shared<Group>(TR("Bring"), 1);
		bringOpts->AddItem(std::make_shared<CommandItem>("bringpeds"_J,TR("Bring All Peds")));
		bringOpts->AddItem(std::make_shared<CommandItem>("bringvehs"_J,TR("Bring All Vehicles")));
		bringOpts->AddItem(std::make_shared<CommandItem>("bringobjs"_J,TR("Bring All Objects")));

		auto weatherOpts = std::make_shared<Group>(TR("Weather"), 1);
		weatherOpts->AddItem(std::make_shared<ListCommandItem>("weather"_J,TR("Weather")));
		weatherOpts->AddItem(std::make_shared<ConditionalItem>("forceweather"_J, std::make_shared<CommandItem>("setweather"_J,TR("Set Weather")), true));
		weatherOpts->AddItem(std::make_shared<BoolCommandItem>("forceweather"_J,TR("Force Weather")));

		auto timeGroup = std::make_shared<Group>(TR("Time"));

		auto hms = std::make_shared<Group>("", 1);
		hms->AddItem(std::make_shared<IntCommandItem>("networktimehour"_J, TR("Hour")));
		hms->AddItem(std::make_shared<IntCommandItem>("networktimeminute"_J, TR("Minute")));
		hms->AddItem(std::make_shared<IntCommandItem>("networktimesecond"_J, TR("Second")));
		timeGroup->AddItem(std::move(hms));

		timeGroup->AddItem(std::make_shared<CommandItem>("setnetworktime"_J, TR("Set")));
		timeGroup->AddItem(std::make_shared<BoolCommandItem>("freezenetworktime"_J, TR("Freeze")));

		auto otherOpts = std::make_shared<Group>(TR("Other"), 1);
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("pedsignore"_J,TR("Peds Ignore")));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("PedRiotMode"_J,TR("Riot Mode")));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("CopsDispatch"_J,TR("Cops Dispatch")));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("enablecreatordevmode"_J,TR("Enable Creator Dev Mode")));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("infiniteboundary"_J,TR("Infinite Boundary")));
        otherOpts->AddItem(std::make_shared<CommandItem>("clearworld"_J,TR("Clear World")));

		main->AddItem(std::move(killPeds));
		main->AddItem(std::move(deleteOpts));
		main->AddItem(std::move(bringOpts));
		main->AddItem(std::move(weatherOpts));
		main->AddItem(std::move(otherOpts));
		main->AddItem(timeGroup);

		iplsGroup->AddItem(std::make_shared<ListCommandItem>("iplselector"_J,TR("IPL set to load")));
		iplsGroup->AddItem(std::make_shared<CommandItem>("loadipl"_J,TR("Load IPL")));
		iplsGroup->AddItem(std::make_shared<CommandItem>("unloadipl"_J,TR("Unload")));
		iplsGroup->AddItem(std::make_shared<CommandItem>("ipltp"_J,TR("Teleport to IPL")));

		AddCategory(std::move(main));
		AddCategory(std::move(BuildSpawnPedMenu()));
		AddCategory(std::move(iplsGroup));
	}
};