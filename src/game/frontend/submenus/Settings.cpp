#include "Settings.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/items/DrawHotkey.hpp"
#include "game/frontend/submenus/Settings/LuaScripts.hpp"
#include "game/frontend/submenus/Settings/GUISettings.hpp"
#include "game/frontend/submenus/Settings/ASILoader.hpp"
#include "game/features/theme/theme.hpp"
#include <imgui.h>
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	// TODO: refactor this
	static void Hotkeys()
	{
		ImGui::BulletText(TR("Hold the button with the command name and enter a keystroke to change its hotkey"));
		ImGui::BulletText(TR("If a command has an existing hotkey, clicking the button will remove it"));

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		
		// this assumes we can't add new commands in runtime, but a lot of other subsystems assume that too
		static std::map<std::string, CommandLink*> sortedCommands;
		static bool commandsSorted = []() {
			for (auto& [hash, command] : Commands::GetCommands())
			{
				if (auto it = g_HotkeySystem.m_CommandHotkeys.find(hash); it != g_HotkeySystem.m_CommandHotkeys.end())
					sortedCommands.emplace(command->GetLabel(), &it->second);
			}
			return true;
		}();

		HotkeySystem::SetBeingModifed(false);

		for (auto& [name, link] : sortedCommands)
		{
			if (name.empty())
				continue;
			DrawHotkey(link, name);
		}
	};

	Settings::Settings() :
	#define ICON_FA_GEARS "\xef\x80\x93"
	    Submenu::Submenu(TR("Settings"), ICON_FA_GEARS)
	{
		auto hotkeys = std::make_shared<Category>(TR("Hotkeys"));
		auto gui = std::make_shared<Category>(TR("GUI"));
		auto game = std::make_shared<Category>(TR("Game"));
		auto theme = std::make_shared<Category>(TR("Theme"));

		auto uiStyle = std::make_shared<Group>(TR("UI"));
		auto playerEsp = std::make_shared<Group>(TR("Player ESP"), 10);
		auto pedEsp = std::make_shared<Group>(TR("Ped ESP"), 10);
		auto objectEsp = std::make_shared<Group>(TR("Object ESP"));
		auto overlay = std::make_shared<Group>(TR("Overlay"));
		auto chat = std::make_shared<Group>(TR("Chat"));
		auto hud = std::make_shared<Group>("HUD");

		hotkeys->AddItem(std::make_shared<ImGuiItem>(Hotkeys));

		// Players
		uiStyle->AddItem(std::make_shared<ListCommandItem>("styleselector"_J,TR("Styles Elector")));
		uiStyle->AddItem(std::make_shared<BoolCommandItem>("menubgfireworks"_J,TR("Menu Fireworks Background")));
		//uiStyle->AddItem(std::make_shared<BoolCommandItem>("menubgsnow"_J,TR("Menu Snow Background")));

		playerEsp->AddItem(std::make_shared<BoolCommandItem>("espdrawplayers"_J,TR("Draw Players")));
		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espdrawdeadplayers"_J,TR("Draw Dead Players"))));

		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espnameplayers"_J, TR("Player Name"))));
		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<ColorCommandItem>("namecolorplayers"_J,TR("Player Name Color"))));

		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espdistanceplayers"_J, TR("Player Distance"))));

		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espskeletonplayers"_J, TR("Player Skeleton"))));
		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<ColorCommandItem>("skeletoncolorplayers"_J,TR("Player Skeleton Color"))));

		// Peds
		pedEsp->AddItem(std::make_shared<BoolCommandItem>("espdrawpeds"_J,TR("Draw Peds")));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espdrawdeadpeds"_J,TR("Draw Dead Peds"))));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espmodelspeds"_J, TR("Ped Hashes"))));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<ColorCommandItem>("hashcolorpeds"_J,TR("Ped Hashes Color"))));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espnetinfopeds"_J, TR("Ped Net Info"))));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espscriptinfopeds"_J, TR("Ped Script Info"))));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espdistancepeds"_J, TR("Ped Distance"))));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espskeletonpeds"_J, TR("Ped Skeleton"))));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<ColorCommandItem>("skeletoncolorpeds"_J,TR("Ped Skeleton Color"))));

		objectEsp->AddItem(std::make_shared<BoolCommandItem>("espdrawobjects"_J,TR("Draw Special Objects")));
		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<ColorCommandItem>("hashcolorobjects"_J,TR("Draw Special Objects Color"))));
		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<BoolCommandItem>("espnetinfoobjects"_J, TR("Object Net Info"))));
		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<BoolCommandItem>("espscriptinfoobjects"_J, TR("Object Script Info"))));

		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<BoolCommandItem>("espdistanceobjects"_J, TR("Object Distance"))));


		overlay->AddItem(std::make_shared<BoolCommandItem>("overlay"_J,TR("Overlay Enable")));
		overlay->AddItem(std::make_shared<ConditionalItem>("overlay"_J, std::make_shared<BoolCommandItem>("overlayfps"_J,TR("Overlay Show FPS"))));
		overlay->AddItem(std::make_shared<ConditionalItem>("overlay"_J, std::make_shared<ListCommandItem>("overlaypos"_J,TR("Overlay Position"))));
		overlay->AddItem(std::make_shared<ConditionalItem>("overlay"_J, std::make_shared<BoolCommandItem>("overlaylock"_J,TR("Lock Overlay Position"))));

		chat->AddItem(std::make_shared<BoolCommandItem>("clearchat"_J,TR("Clear Chat")));
        
		gui->AddItem(std::make_shared<CommandItem>("unloadmenu"_J,TR("unloadmenu")));

		hud->AddItem(std::make_shared<BoolCommandItem>("hidehud"_J,TR("hidehud")));
		hud->AddItem(std::make_shared<BoolCommandItem>("disabletextsounds"_J,TR("Disable Text Sounds")));
		
			//Editor
		theme->AddItem(std::make_shared<ImGuiItem>(theme::theme_editor));

		game->AddItem(playerEsp);
		game->AddItem(pedEsp);
		game->AddItem(objectEsp);

		gui->AddItem(uiStyle);
		gui->AddItem(overlay);
		gui->AddItem(chat);
		gui->AddItem(hud);

		AddCategory(std::move(hotkeys));
		AddCategory(std::move(gui));
		AddCategory(std::move(game));
		AddCategory(std::move(theme));
		AddCategory(DrawGUISettingsMenu());
		AddCategory(BuildLuaScriptsMenu());
		AddCategory(BuildASILoaderMenu());
	}
}