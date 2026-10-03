#include "core/commands/LoopedCommand.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class AlienEggMission : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			*ScriptGlobal(2733326).At(3989).At(348).As<int*>() = 20;
		}
	};
	static AlienEggMission _AlienEggMission{
	    "alien_egg_mission",
	    TR("Alien Egg Mission"),
	    TR("Forces Alien Egg mission progression")};
}