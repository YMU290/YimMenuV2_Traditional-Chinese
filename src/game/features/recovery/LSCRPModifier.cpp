#include "core/commands/IntCommand.hpp"
#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/backend/FiberPool.hpp"
#include <algorithm>
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	static IntCommand LSCarMeetRankSlider{
	    "lscarmeetrank",
	    TR("LS Car Meet Rank"),
	    "Sets LS Car Meet rank (writes CAR_CLUB_REP).",
	    1,
	    1000,
	    1};

	class ApplyLSCarMeetRank : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			int rank = std::clamp(LSCarMeetRankSlider.GetState(), 1, 1000);
			int rep = rank * 1100;
			Stats::SetInt("MPX_CAR_CLUB_REP", rep);
		}
	};

	static ApplyLSCarMeetRank _ApplyLSCarMeetRank{
	    "applylscarmeetrank",
	    TR("Apply LS Car Meet Rank"),
	    TR("Applies the selected LS Car Meet rank.")};
	//Location Needs Changed 
	class Complete_Challenge : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetBool("MPX_CARMEET_PV_CHLLGE_CMPLT", true);
			Stats::SetBool("MPX_CARMEET_PV_CLMED", false);
			STATS::STAT_SAVE(0, 0, 3, 0);
			Notifications::Show("YimMenuV2", "Done. If you are in LSCM, re-enter to collect the prize.", NotificationType::Success);
		}
	};
	static Complete_Challenge _Complete_Challenge{
    "Complete_Challenge",
    TR("Unlock LSCM Prize Ride"),
    TR("Unlocks the LS Car Meet prize ride instantly")};
	//tp
	class TeleportToLSCM : public Command
	{
	 using Command::Command;
    void OnCall() override
    {
        FiberPool::Push([]()
        {
            auto blip = HUD::GET_FIRST_BLIP_INFO_ID(777);
            auto coords = HUD::GET_BLIP_COORDS(blip);
            PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z);
        });
    }
};
static TeleportToLSCM _TeleportToLSCM{
    "tp_lscm",
    TR("Teleport to LS Car Meet"),
    TR("Teleport to the LS Car Meet")};
}
