#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class Free_S95 : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			//Stats::SetPackedBool(36828, true);
			Stats::SetPackedBool(7332, true);
			Stats::SaveStats();
		}
	}; 
	static Free_S95 _Free_S95{"FKarin_S95", TR("Karin S95"), TR("Free at SSASA.")};
}