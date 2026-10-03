#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class UnlockAllTradePrices : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				Stats::SetPackedBool(42281, true); // Dominator FX Interceptor
				Stats::SetPackedBool(42282, true); //Dorado Cruiser
				Stats::SetPackedBool(42283, true); //Impaler SZ Cruiser
				Stats::SetPackedBool(42284, true); //Impaler LX Cruiser
				Stats::SetPackedBool(42288, true); // Taco Van, Terminus Patrol
				Stats::SetPackedBool(42289, true); //Caracara Pursuit
				Stats::SetPackedBool(54732, true); //Buffalo STX Pursuit
				Stats::SetPackedBool(54733, true); //Buffalo Cruiser
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
			else
			{
				Notifications::Show("YimMenuV2", TR("You Must be Online"), NotificationType::Error);
			}
		}
	};
	static UnlockAllTradePrices _UnlockAllTradePrices{
	    "unlockalltradeprices",
	    TR("Unlock Trade Prices"),
	    TR("Unlocks Trade Prices")};

}
