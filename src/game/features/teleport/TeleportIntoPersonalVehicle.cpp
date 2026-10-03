#include "core/commands/Command.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class TeleportIntoPersonalVehicle : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			if (auto value = ScriptGlobal(2640101).At(8).As<int*>())
			{
				*value = 1;
			}
		}
	};

	static TeleportIntoPersonalVehicle _TeleportIntoPersonalVehicle{
	    "teleportintopersonalvehicle",
	    TR("Teleport Into Personal Vehicle"),
	    TR("Teleports you into your personal vehicle")
	};
}