#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class NewUnlock : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
Stats::SetPackedInt(262145, 37394);
				Stats::SetPackedBool(54687, true);
				Stats::SetInt("MPPLY_XMAS22CPAINT0", -1);
				Stats::SetInt("MPPLY_XMAS22CPAINT1", -1);
				Stats::SetInt("MPPLY_SUM23WHEELCPAINT0", -1);
				Stats::SetInt("MPPLY_SUM23WHEELCPAINT1", -1);
				Stats::SetInt("MPPLY_XMAS23_PLATES0", -1);
				Stats::SetInt("MPX_AWD_TRANSPORT", 20);
				Stats::SetBool("MPX_AWD_SECUREDEL", TRUE);
				Stats::SetInt("MPX_AWD_SUNBURNED", 20);
				Stats::SetBool("MPX_AWD_TWOOFAKIND", TRUE);
				Stats::SetInt("MPX_AWD_UNDEADPARTY", 100);
				Stats::SetPackedBool(54711, true);
				Stats::SetPackedInt(262145, 26702);
				Stats::SetPackedBool(3595, true);
				Stats::SetPackedBool(3594, true);
				Stats::SetPackedBool(3596, true);
				Stats::SetPackedBool(3597, true);
				Stats::SetPackedBool(3598, true);
				Stats::SetPackedBool(3599, true);
				Stats::SetPackedBool(3604, true);
				Stats::SetPackedBool(3605, true);
				Stats::SetPackedBool(3606, true);
				Stats::SetPackedBool(3607, true);
				Stats::SetPackedBool(36689, 62); // Acid Production Boost (0/f = Reset)
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
		}
	};
	static NewUnlock _NewUnlock{
	    "New_Unlock",
	    TR("NewUnlock"),
	    TR("New Unlock")};
}
