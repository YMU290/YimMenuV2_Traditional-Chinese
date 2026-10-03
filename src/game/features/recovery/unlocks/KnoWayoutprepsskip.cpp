#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class KnowWayPrepSkiper : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				Stats::SetInt("MPX_M25_AVI_MISSION_CURRENT", 4);
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
			else
			{
				Notifications::Show("YimMenuV2", TR("You Must be Online"), NotificationType::Error);
			}
		}
	};
	static KnowWayPrepSkiper _KnowWayPrepSkiper{
	    "KnoWayOutPrepsSkip",
	    TR("KnoWay out preps skip"),
	    TR("KnoWay out preps skip")};
}
