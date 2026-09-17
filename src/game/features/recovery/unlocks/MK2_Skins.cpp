#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class mk2_skins : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetPackedBool(51196, true);
			Stats::SetPackedBool(42148, true);
			Stats::SetPackedBool(42249, true);
			Stats::SetPackedBoolRange(18981,3, true);
			Stats::SetPackedBool(25002, true);
			Stats::SetInt("MPX_CAS_HEIST_FLOW", 4096);
	        Stats::SetPackedBool(28158, true);
			Stats::SetPackedBool(30633, true);
			Stats::SetPackedBool(30632, true);
			Stats::SetPackedBoolRange(7315,5, true);
			Stats::SetPackedBool(32293, true);
			/*OLD = *ScriptGlobal(262145).At(0).As<int*>() = 1;*/
			Stats::SaveStats();
		}
	};
	static mk2_skins _mk2_skins{"mk2_skins", TR("MK2 Gun Skins"), TR("MK2 Gun Skins.")};
}
