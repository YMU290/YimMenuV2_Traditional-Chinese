#include "core/commands/IntCommand.hpp"
#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	static IntCommand ArenaWarRankSlider{
		"arenawarrank",
		TR("Arena War Rank"),
		TR("Sets Arena War sponsorship tier."),
		1,
		1000,
		1
	};

	class ApplyArenaWarRank : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			const int rank = std::clamp(ArenaWarRankSlider.GetState(), 1, 1000);
			Stats::SetInt("MPX_ARENAWARS_AP_TIER", rank);
			STATS::STAT_SAVE(0, 0, 3, 0);
			Notifications::Show("YimMenuV2", "Arena War rank applied.", NotificationType::Success);
		}
	};

	static ApplyArenaWarRank _ApplyArenaWarRank{
		"applyarenawarrank",
		TR("Apply Arena War Rank"),
		TR("Applies the selected Arena War sponsorship tier.")
	};
}
