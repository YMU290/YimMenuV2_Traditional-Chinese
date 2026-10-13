#include "game/backend/Self.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class TeleportToPlayer : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			if (auto ped = player.GetPed())
				Self::GetPed().TeleportTo(ped.GetPosition());
		}
	};

	static TeleportToPlayer _TeleportToPlayer{"tptoplayer", TR("Teleport to Player"), "Teleports you to the selected player"};
}