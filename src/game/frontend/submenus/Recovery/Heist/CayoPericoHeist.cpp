#include "CayoPericoHeist.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/util/utils.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/localization/Translator.hpp"

#include <array>

namespace YimMenu::Submenus
	{
	static int g_SelectedTeleport = 0;
	static constexpr std::array<const char*, 6> g_TeleportItems = {
		//Just a test
		"Kosatka",
		"Drainage Pipe",
		"Drainage Pipe Checkpoint",
		"El Rubio's Office",
		"Front Gate Exit",
		"Ocean (Exit)",
	};

	static bool OwnsKosatka()
	{
		/*freemode.c*/
		/*func_5530*/
		const int player = PLAYER::PLAYER_ID();
		auto value = ScriptGlobal(1845347).At(player, 884).At(260).At(489).As<int*>();
		if (!value)
			return false;

		return (*value & (1 << 0)) != 0;
	}

	std::shared_ptr<TabItem> RenderCayoPericoHeistMenu()
	{
		auto tab = std::make_shared<TabItem>(TR("Cayo Perico Heist"));

		auto cuts = std::make_shared<Group>(TR("Heist Cuts"), 2);
		auto setups = std::make_shared<Group>(TR("Heist Setups"));
		auto loots = std::make_shared<Group>(TR("Loots"), 2);
		auto misc = std::make_shared<Group>(TR("Misc"), 1);
		auto cayo_tp = std::make_shared<Group>(TR("Teleport"));

		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut1"_J,TR("Player 1")));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut3"_J,TR("Player 3")));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut2"_J, TR("Player 2")));
		cuts->AddItem(std::make_shared<IntCommandItem>("cayopericoheistcut4"_J,TR("Player 4")));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistforceready"_J,TR("Force Ready")));
		cuts->AddItem(std::make_shared<CommandItem>("cayopericoheistsetcuts"_J,TR("Set Cuts")));

		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistdifficulty"_J, TR("Difficulty")));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistprimarytarget"_J,TR("Primary Target")));
		setups->AddItem(std::make_shared<ListCommandItem>("cayopericoheistweapon"_J,TR("Weapon")));
		setups->AddItem(std::make_shared<CommandItem>("cayopericoheistsetup"_J,TR("Setup")));

		loots->AddItem(std::make_shared<IntCommandItem>("cayopericoheistprimarytargetvalue"_J,TR("Primary Target Value")));
		loots->AddItem(std::make_shared<IntCommandItem>("cayopericoheistsecondarytakevalue"_J,TR("Secondary Take Value")));
		loots->AddItem(std::make_shared<CommandItem>("cayopericoheistsetprimarytargetvalue"_J,(std::string(TR("Set")) + "##primarytargetvalue").c_str()));
		loots->AddItem(std::make_shared<CommandItem>("cayopericoheistsetsecondarytakevalue"_J,(std::string(TR("Set")) + "##secondarytakevalue").c_str()));

		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistskiphacking"_J,TR("Skip Hack")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistcutsewer"_J,TR("Cut Sewer")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistcutglass"_J,TR("Cut Glass")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheisttakeprimarytarget"_J, TR("Take Primary Target")));
		misc->AddItem(std::make_shared<CommandItem>("cayopericoheistinstantfinish"_J,TR("Instant Finish")));

	cayo_tp->AddItem(std::make_unique<ImGuiItem>([] {
			std::array<std::string, g_TeleportItems.size()> translatedItems;
			for (std::size_t i = 0; i < g_TeleportItems.size(); ++i)
				translatedItems[i] = Translator::TranslateStored(g_TeleportItems[i]);

			ImGui::SetNextItemWidth(140.f);
			if (ImGui::BeginCombo(TR("Teleport To"), translatedItems[g_SelectedTeleport].c_str()))
			{
				for (int i = 0; i < static_cast<int>(translatedItems.size()); ++i)
				{
					if (ImGui::Selectable(translatedItems[i].c_str(), i == g_SelectedTeleport))
						g_SelectedTeleport = i;

					if (i == g_SelectedTeleport)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button(TR("Teleport"), ImVec2(150, 30)))
			{
				if (g_SelectedTeleport == 0 && !OwnsKosatka())
				{
					Notifications::Show(TR("Cayo Perico Heist"), TR("You must own the Kosatka to use this teleport."), NotificationType::Error);

					return;
				}

				Vector3 pos{};

				switch (g_SelectedTeleport)
				{
				case 0: // Kosatka
					pos = {1561.2369f, 385.8831f, -49.689915f};
					Utils::SetHeading(175.f);
					break;

				case 1: // Drainage Pipe
					pos = {5044.001f, -5815.6426f, -11.808871f};
					break;

				case 2: // Drainage Pipe Checkpoint
					pos = {5053.773f, -5773.2266f, -5.40778f};
					break;

				case 3: // El Rubio's Office
					pos = {5010.12f, -5750.1353f, 28.84334f};
					Utils::SetHeading(325.f);
					break;

				case 4: // Front Gate Exit
					pos = {4990.0386f, -5717.6895f, 19.880217f};
					Utils::SetHeading(50.f);
					break;

				case 5: // Ocean (Exit)
					pos = {4771.479f, -6165.737f, -39.079613f};
					break;
				}

				Ped ped = PLAYER::PLAYER_PED_ID();

				if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(ped, false);

					ENTITY::SET_ENTITY_COORDS(veh, pos.x, pos.y, pos.z, false, false, false, true);
				}
				else
				{
					ENTITY::SET_ENTITY_COORDS(ped, pos.x, pos.y, pos.z, false, false, false, true);
				}
			}
		}));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(loots);
		tab->AddItem(misc);
		tab->AddItem(cayo_tp);

		return tab;
	}
	}