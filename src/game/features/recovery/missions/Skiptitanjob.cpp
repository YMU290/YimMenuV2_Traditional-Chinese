#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class Titan_job : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				Stats::SetInt("MPX_HACKER24_INST_BS", -1);
				Stats::SaveStats();
			}
			else
			{
				Notifications::Show("YimMenuV2", "You Must be Online", NotificationType::Error);
			}
		}
	};
	static Titan_job _Titan_job{
	    "Skiptitanjob",TR("Skip titan job setup"),TR("Skip titan job setup.")};
}
