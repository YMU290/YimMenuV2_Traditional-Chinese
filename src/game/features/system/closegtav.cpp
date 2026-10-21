#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class CloseGTAV : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			MISC::QUIT_GAME();
		}
	};

	static CloseGTAV _CloseGTAV{"closegtav", TR("Close GTA V Enhanced"), TR("Closing GTA V Enhanced and GTA Online")};
}
