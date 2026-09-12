#include "Debug.hpp"
#include "Debug/Misc.hpp"
#include "Debug/Globals.hpp"
#include "Debug/Locals.hpp"
#include "Debug/Scripts.hpp"
#include "game/frontend/items/Items.hpp"
#include "Debug/ScriptStarter.hpp"
#include "Debug/CutscenesStarter.hpp"
#include "Debug/LuaDownloader.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	   Debug::Debug() :
       #define ICON_FA_ARROW_RIGHT "\xef\x84\xa0"
	    Submenu::Submenu(TR("Debug"), ICON_FA_ARROW_RIGHT)
	{
		auto main = std::make_shared<Category>(TR("Main"));
		auto GeneralGroup = std::make_shared<Group>(TR("General"));

		GeneralGroup->AddItem(std::make_shared<BoolCommandItem>("unlockfps"_J,TR("unlockfps")));

		main->AddItem(GeneralGroup);
		AddCategory(std::move(main));
		AddCategory(BuildMiscMenu());
		AddCategory(BuildGlobalsMenu());
		AddCategory(BuildLocalsMenu());
		AddCategory(BuildScriptsMenu());
		AddCategory(BuildScriptStarterMenu());
		AddCategory(BuildCutscenesStarterMenu());
		AddCategory(BuildLuaDownloaderMenu());
	}
}