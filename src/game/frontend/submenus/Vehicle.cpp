#include "Vehicle.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/submenus/Vehicle/SpawnVehicle.hpp"
#include "Vehicle/VehicleEditor.hpp"
#include "Vehicle/SavedVehicles.hpp"
#include "core/localization/Translator.hpp"
#define TR(key) YimMenu::Translator::Get(key).c_str()

namespace YimMenu::Submenus
{
	Vehicle::Vehicle() :
		#define ICON_FA_CAR "\xef\x86\xb9"
		Submenu::Submenu(TR("Vehicle"), ICON_FA_CAR)
	{
		auto main = std::make_shared<Category>(TR("Main"));

		auto globals = std::make_shared<Group>(TR("Globals"));
		auto tools = std::make_shared<Group>(TR("Tools"), 2);
		auto misc = std::make_shared<Group>(TR("Misc"));
		auto deletePV = std::make_shared<Group>(TR("Delete Personal Vehicle"));

		globals->AddItem(std::make_shared<BoolCommandItem>("vehiclegodmode"_J, TR("Godmode")));
		globals->AddItem(std::make_shared<BoolCommandItem>("keepfixed"_J, TR("Keep Fixed")));
		globals->AddItem(std::make_shared<BoolCommandItem>("hornboost"_J, TR("Horn Boost")));

		globals->AddItem(std::make_shared<ConditionalItem>("hornboost"_J, std::make_shared<FloatCommandItem>("hornboostspeed"_J,TR("Horn Boost Power"))));
		globals->AddItem(std::make_shared<BoolCommandItem>("camerashake"_J,TR("Camera Shake")));
		globals->AddItem(std::make_shared<ConditionalItem>("camerashake"_J, std::make_shared<FloatCommandItem>("camerashakeintensity"_J,TR("Camera Shake Intensity"))));
		globals->AddItem(std::make_shared<BoolCommandItem>("speedblur"_J,TR("Speed Blur")));
		globals->AddItem(std::make_shared<ConditionalItem>("speedblur"_J, std::make_shared<FloatCommandItem>("speedblurintensity"_J, TR("Speed Blur Intensity"))));
		globals->AddItem(std::make_shared<BoolCommandItem>("tornadomode"_J,TR("Tornado Mode")));
		globals->AddItem(std::make_shared<ConditionalItem>("tornadomode"_J, std::make_shared<FloatCommandItem>("tornadostrength"_J,TR("Tornado Strength"))));
		globals->AddItem(std::make_shared<BoolCommandItem>("wheeliemode"_J,TR("Wheelie Mode")));
		globals->AddItem(std::make_shared<ConditionalItem>("wheeliemode"_J, std::make_shared<FloatCommandItem>("wheeliestrength"_J,TR("Wheelie Strength"))));

		globals->AddItem(std::make_shared<BoolCommandItem>("modifyboostbehavior"_J, TR("Modify Boost Behavior")));
		globals->AddItem(std::make_shared<ConditionalItem>("modifyboostbehavior"_J, std::make_shared<ListCommandItem>("boostbehavior"_J,TR("Boost Behavior"))));
		globals->AddItem(std::make_shared<BoolCommandItem>("autodrive"_J,TR("Auto Drive")));
		globals->AddItem(std::make_shared<BoolCommandItem>("npcautodrive"_J,TR("NPC Auto Drive")));
		globals->AddItem(std::make_shared<BoolCommandItem>("autodrivehud"_J,TR("Auto Drive Hud")));

		auto isAutoDriveEnabled = [] {
			const auto playerAutoDrive = Commands::GetCommand<BoolCommand>("autodrive"_J);
			const auto npcAutoDrive = Commands::GetCommand<BoolCommand>("npcautodrive"_J);
			return (playerAutoDrive && playerAutoDrive->GetState())
				|| (npcAutoDrive && npcAutoDrive->GetState());
		};

		globals->AddItem(std::make_shared<ConditionalItem>(isAutoDriveEnabled, std::make_shared<IntCommandItem>("autodrivespeed"_J,TR("Auto Drive Speed"))));
		globals->AddItem(std::make_shared<ConditionalItem>(isAutoDriveEnabled, std::make_shared<ListCommandItem>("autodrivestyle"_J,TR("Auto Drive Style"))));


		tools->AddItem(std::make_shared<CommandItem>("enterlastvehicle"_J, TR("Enter Last Vehicle")));
		tools->AddItem(std::make_shared<CommandItem>("enterpvvehicle"_J,TR("Enter PV Vehicle")));
		tools->AddItem(std::make_shared<CommandItem>("repairvehicle"_J, TR("Repair Vehicle")));
		tools->AddItem(std::make_shared<CommandItem>("fixallvehicles"_J, TR("Fix All Vehicles")));
		tools->AddItem(std::make_shared<CommandItem>("callmechanic"_J, TR("Call Mechanic")));
		tools->AddItem(std::make_shared<CommandItem>("requestpv"_J, TR("Request Personal Vehicle")));
		tools->AddItem(std::make_shared<CommandItem>("despawnpv"_J, TR("Despawn Personal Vehicle")));
		tools->AddItem(std::make_shared<CommandItem>("savepersonalvehicle"_J, TR("Save Personal Vehicle")));
		tools->AddItem(std::make_shared<CommandItem>("deletePV"_J, TR("Delete Personal Vehicle")));

		// Rainbow Paint feature with options
		misc->AddItem(std::make_shared<BoolCommandItem>("rainbowpaint"_J, TR("Rainbow Paint")));
		misc->AddItem(std::make_shared<ConditionalItem>("rainbowpaint"_J, std::make_shared<ListCommandItem>("rainbowtype"_J, TR("Paint Type"))));
		misc->AddItem(std::make_shared<ConditionalItem>("rainbowpaint"_J, std::make_shared<BoolCommandItem>("rainbowpri"_J, TR("Primary"))));
		misc->AddItem(std::make_shared<ConditionalItem>("rainbowpaint"_J, std::make_shared<BoolCommandItem>("rainbowsec"_J, TR("Secondary"))));
		misc->AddItem(std::make_shared<ConditionalItem>("rainbowpaint"_J, std::make_shared<IntCommandItem>("rainbowspeed"_J, TR("Speed"))));

		// Vehicle Jump feature
		misc->AddItem(std::make_shared<BoolCommandItem>("vehjump"_J, TR("Vehicle Jump")));

		misc->AddItem(std::make_shared<BoolCommandItem>("speedometer"_J, TR("Speedometer")));
		misc->AddItem(std::make_shared<BoolCommandItem>("seatbelt"_J, TR("Seatbelt")));
		misc->AddItem(std::make_shared<BoolCommandItem>("loudsubwoffer"_J,TR("loudsubwoofer")));
		misc->AddItem(std::make_shared<BoolCommandItem>("vehicle_indicators"_J,TR("Vehicle Indicators")));
		misc->AddItem(std::make_shared<BoolCommandItem>("lowervehiclestance"_J, TR("Lower Stance")));
		misc->AddItem(std::make_shared<BoolCommandItem>("allowhatsinvehicles"_J, TR("Allow Hats In Vehicles")));
		misc->AddItem(std::make_shared<BoolCommandItem>("lsccustomsbypass"_J, TR("Remove LSC Restrictions")));
		misc->AddItem(std::make_shared<BoolCommandItem>("dlcvehicles"_J, TR("Enable Allow DLC Vehicles")));
		misc->AddItem(std::make_shared<BoolCommandItem>("vehicledrift"_J,TR("Drift Mode")));
		misc->AddItem(std::make_shared<ListCommandItem>("driftvariant"_J,TR("Drift Variant")));

		main->AddItem(globals);
		main->AddItem(tools);
		main->AddItem(misc);

		AddCategory(std::move(main));
		AddCategory(BuildSpawnVehicleMenu());
		AddCategory(BuildVehicleEditorMenu());
		AddCategory(BuildSavedVehiclesMenu());
	}
}