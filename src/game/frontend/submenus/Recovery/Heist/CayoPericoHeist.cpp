#include "CayoPericoHeist.hpp"
#include "game/gta/Natives.hpp"
#include "core/util/utils.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
	{
	static int g_SelectedTeleport = 0;
	static const char* g_TeleportItems[] = {
		//Just a test
	    "Kosatka",
	    "Drainage Pipe",
	    "Drainage Pipe Checkpoint",
	    "El Rubio's Office",
	    "Front Gate Exit",
	    "Ocean (Exit)",
	};

	std::shared_ptr<TabItem> RenderCayoPericoHeistMenu()
	{
		auto tab = std::make_shared<TabItem>(TR("Cayo Perico Heist"));

		auto cuts = std::make_shared<Group>(TR("Heist Cuts"), 2);
		auto setups = std::make_shared<Group>(TR("Heist Setups"));
		auto loots = std::make_shared<Group>(TR("Loots"), 2);
		auto misc = std::make_shared<Group>(TR("Misc"), 1);
		auto cayo_tp = std::make_shared<Group>("Teleport");

		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut1"_J,TR("Player 1")));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut3"_J,TR("Player 3")));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut2"_J, TR("Player 2")));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut4"_J,TR("Player 4")));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistforceready"_J,TR("Force Ready")));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistsetcuts"_J,TR("Set Cuts")));

		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistdifficulty"_J,TR("Difflicully")));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistprimarytarget"_J,TR("Primary Target")));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistweapon"_J,TR("Weapon")));
		setups->AddItem(std::make_shared<CommandItem>("cayopericoheistsetup"_J,TR("Setup")));

		loots->AddItem(std::make_shared<IntCommandItem>("cayopericoheistprimarytargetvalue"_J,TR("Primary Target Value")));
		loots->AddItem(std::make_shared<IntCommandItem>("cayopericoheistsecondarytakevalue"_J,TR("Secondary Take Value")));
		loots->AddItem(std::make_shared<CommandItem>("cayopericoheistsetprimarytargetvalue"_J,(std::string(TR("Set")) + "##primarytargetvalue").c_str()));
		loots->AddItem(std::make_shared<CommandItem>("cayopericoheistsetsecondarytakevalue"_J,(std::string(TR("Set")) + "Set##secondarytakevalue").c_str()));

		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistskiphacking"_J,TR("Skip Hack")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistcutsewer"_J,TR("Cut Sewer")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistcutglass"_J,TR("Cut Glass")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheisttakeprimarytarget"_J, TR("Take Primary Target")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistinstantfinish"_J,TR("Instant Finish")));

	cayo_tp->AddItem(std::make_unique<ImGuiItem>([] {
			ImGui::SetNextItemWidth(140.f);
			ImGui::Combo("Teleport To", &g_SelectedTeleport, g_TeleportItems, IM_ARRAYSIZE(g_TeleportItems));
			if (ImGui::Button("Teleport", ImVec2(150, 30))) {
				 Vector3 pos{};
				 switch (g_SelectedTeleport) {
					  case 0: // Kosatka
						  pos = { 1561.2369, 385.8831, -49.689915 };
					      Utils::SetHeading(175);
					  break;
					  case 1: // Drainage Pipe
						   pos = { 5044.001, -5815.6426, -11.808871 };
					  break;
					  case 2: // Drainage Pipe Checkpoint
						   pos = { 5053.773, -5773.2266, -5.40778 };
					  break;
					  case 3: // El Rubio's Office
						    pos = { 5010.12, -5750.1353, 28.84334 };
						    Utils::SetHeading(325);
					  break;
					  case 4: // Front Gate Exit
						    pos = { 4990.0386, -5717.6895, 19.880217 };
						    Utils::SetHeading(50);
					  break;
					  case 5: // Ocean (Exit)
						   pos = { 4771.479, -6165.737, -39.079613 };
					  break;

					}
					   Ped ped = PLAYER::PLAYER_PED_ID();
					    if (PED::IS_PED_IN_ANY_VEHICLE(ped, false)) {
							Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(ped, false);
							ENTITY::SET_ENTITY_COORDS(veh, pos.x, pos.y, pos.z, false, false, false, true);
							}
						else {
							 ENTITY::SET_ENTITY_COORDS(ped, pos.x, pos.y, pos.z, false, false, false, true);
						}
					}
			}));


		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(loots);
		tab->AddItem(misc);

		return tab;
	}
}