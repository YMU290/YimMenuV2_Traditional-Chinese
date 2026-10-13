#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "game/backend/Tunables.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class Unlockmisc : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				for (int i = 0; i <= 53; ++i)
					Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_" + std::to_string(i), -1);
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_0", Tunable("ROOT_ID_HASH_THE_FLECCA_JOB"_J).Get<int>());
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_0_L", 5);
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_1", Tunable("ROOT_ID_HASH_THE_PRISON_BREAK"_J).Get<int>());
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_1_L", 5);
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_2", Tunable("ROOT_ID_HASH_THE_HUMANE_LABS_RAID"_J).Get<int>());
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_2_L", 5);
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_3", Tunable("ROOT_ID_HASH_SERIES_A_FUNDING"_J).Get<int>());
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_3_L", 5);
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_4", Tunable("ROOT_ID_HASH_THE_PACIFIC_STANDARD_JOB"_J).Get<int>());
				Stats::SetInt("MPX_HEIST_SAVED_STRAND_4_L", 5);
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
		}
	};
	static Unlockmisc _Unlockmisc{
	    "unlock_misc",
	    TR("Unlock misc"),
	    TR("Unlock misc")};

}

