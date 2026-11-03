#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class Unlockalltattoos : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				Stats::SetPackedBool(41273, 41284);
				Stats::SetPackedBool(15737, 15737);
				Stats::SetPackedBool(15887, 15887);
				Stats::SetPackedBool(54615, 54634);
				Stats::SetPackedBool(15456, 15460);
				Stats::SetPackedBool(36920, 36922);
				Stats::SetPackedBool(15700, 15800);
				Stats::SetPackedBool(50000, 51000);
				Stats::SetInt("MPX_AWD_100_HEADSHOTS", 1000);
				Stats::SetInt("MPX_PLAYER_HEADSHOTS", 1000);
				Stats::SetInt("MPX_AWD_100_KILLS", 1000);
				Stats::SetInt("MPX_AWD_100_WINS", 1000);
				Stats::SetInt("MPX_AWD_50_KILLS", 1000);
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
			else
			{
				Notifications::Show("YimMenuV2", TR("You Must be Online"), NotificationType::Error);
			}
		}
	};
	static Unlockalltattoos _Unlockalltattoos{
	    "unlockalltattoos",
	    TR("Unlock All Tattoos"),
	    TR("Unlocks every tattoo")};
}

