#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class UnlockGunrunning : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				*ScriptGlobal(262145).At(21602).As<int*>() = 1;
				*ScriptGlobal(262145).At(21603).As<int*>() = 1;
				*ScriptGlobal(262145).At(21604).As<int*>() = 1;
				*ScriptGlobal(262145).At(21605).As<int*>() = 1;
				*ScriptGlobal(262145).At(21606).As<int*>() = 1;
				*ScriptGlobal(262145).At(21607).As<int*>() = 1;
				*ScriptGlobal(262145).At(21608).As<int*>() = 1;
				*ScriptGlobal(262145).At(21609).As<int*>() = 1;
				*ScriptGlobal(262145).At(21610).As<int*>() = 1;
				*ScriptGlobal(262145).At(21611).As<int*>() = 1;
				*ScriptGlobal(262145).At(21612).As<int*>() = 1;
				*ScriptGlobal(262145).At(21613).As<int*>() = 1;
				*ScriptGlobal(262145).At(21614).As<int*>() = 1;
				*ScriptGlobal(262145).At(21615).As<int*>() = 1;
				*ScriptGlobal(262145).At(21616).As<int*>() = 1;
				*ScriptGlobal(262145).At(21617).As<int*>() = 1;
				//Liveries
				*ScriptGlobal(262145).At(21618).As<int*>() = 1;
				*ScriptGlobal(262145).At(21619).As<int*>() = 1;
				*ScriptGlobal(262145).At(21620).As<int*>() = 1;
				*ScriptGlobal(262145).At(21621).As<int*>() = 1;
				*ScriptGlobal(262145).At(21622).As<int*>() = 1;
				*ScriptGlobal(262145).At(21623).As<int*>() = 1;
				*ScriptGlobal(262145).At(21624).As<int*>() = 1;
				*ScriptGlobal(262145).At(21625).As<int*>() = 1;
				// Ammo
				*ScriptGlobal(262145).At(21626).As<int*>() = 1;
				*ScriptGlobal(262145).At(21627).As<int*>() = 1;
				*ScriptGlobal(262145).At(21628).As<int*>() = 1;
				*ScriptGlobal(262145).At(21629).As<int*>() = 1;
				*ScriptGlobal(262145).At(21630).As<int*>() = 1;
				// Mk II Attachments
				*ScriptGlobal(262145).At(21631).As<int*>() = 1;
				*ScriptGlobal(262145).At(21632).As<int*>() = 1;
				*ScriptGlobal(262145).At(21633).As<int*>() = 1;
				*ScriptGlobal(262145).At(21634).As<int*>() = 1;
				*ScriptGlobal(262145).At(21635).As<int*>() = 1;
				*ScriptGlobal(262145).At(21636).As<int*>() = 1;
				*ScriptGlobal(262145).At(21637).As<int*>() = 1;
				*ScriptGlobal(262145).At(21638).As<int*>() = 1;
				*ScriptGlobal(262145).At(21639).As<int*>() = 1;
				*ScriptGlobal(262145).At(21640).As<int*>() = 1;
				*ScriptGlobal(262145).At(21641).As<int*>() = 1;
				*ScriptGlobal(262145).At(21642).As<int*>() = 1;
				*ScriptGlobal(262145).At(21643).As<int*>() = 1;
				// Explosives
				*ScriptGlobal(262145).At(21644).As<int*>() = 1;
				// Camos
				*ScriptGlobal(262145).At(21645).As<int*>() = 1;
				*ScriptGlobal(262145).At(21646).As<int*>() = 1;
				*ScriptGlobal(262145).At(21647).As<int*>() = 1;
				*ScriptGlobal(262145).At(21648).As<int*>() = 1;
				*ScriptGlobal(262145).At(21649).As<int*>() = 1;
				*ScriptGlobal(262145).At(21650).As<int*>() = 1;
				*ScriptGlobal(262145).At(21651).As<int*>() = 1;
				*ScriptGlobal(262145).At(21652).As<int*>() = 1;
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
		}
	};
	static UnlockGunrunning _UnlockGunrunning{
	    "Unlock_Gunrunning",
	    TR("Unlock Gunrunning"),
	    TR("Unlock Gunrunning")};
}
