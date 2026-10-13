#include "game/commands/PlayerCommand.hpp"
#include "types/script/globals/GSBD_Kicking.hpp"
#include "game/gta/Scripts.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class ScriptHostKick : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			if (auto freemode = Scripts::FindScriptThread("freemode"_J); freemode && Scripts::SafeToModifyFreemodeBroadcastGlobals())
			{
				Scripts::ForceScriptHost(freemode);
				GSBD_Kicking::Get()->KickedPlayers[player.GetId()] = true;
			}
		}
	};

	static ScriptHostKick _ScriptHostKick{"shkick", TR("Script Host Kick"), "Kicks the player by faking a vote kick"};
}