#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class Suicide : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPed().SetInvincible(false);
			Self::GetPed().SetHealth(0);
		}
	};

	static Suicide _Suicide{"suicide", TR("Suicide"), TR("Kills you")};
}