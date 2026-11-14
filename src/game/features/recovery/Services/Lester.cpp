#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class Lester_services : Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			Stats::SetInt("MPX_FM_ACT_PHN", -1);
			Stats::SetInt("MPX_FM_ACT_PH2", -1);
			Stats::SetInt("MPX_FM_ACT_PH3", -1);
			Stats::SetInt("MPX_FM_ACT_PH4", -1);
			Stats::SetInt("MPX_FM_ACT_PH5", -1);
			Stats::SetInt("MPX_FM_VEH_TX1", -1);
			Stats::SetInt("MPX_FM_ACT_PH6", -1);
			Stats::SetInt("MPX_FM_ACT_PH7", -1);
			Stats::SetInt("MPX_FM_ACT_PH8", -1);
			Stats::SetInt("MPX_FM_ACT_PH9", -1);
			Stats::SetInt("MPX_FM_CUT_DON", -1);
			Stats::SetInt("MPX_FM_CUT_DONE_2", -1);
		}
	};
	static Lester_services _Lester_services{"Lester_services", TR("Lester Services"), TR("Fix Lester Services Bug.")};
}
