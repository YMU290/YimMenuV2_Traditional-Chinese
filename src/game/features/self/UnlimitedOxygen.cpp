#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class UnlimitedOxygen : LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			Self::GetPed().SetMaxTimeUnderwater(INT_MAX);
		}

		virtual void OnDisable() override
		{
			Self::GetPed().SetMaxTimeUnderwater(-1.0f); // default value
		}
	};

	static UnlimitedOxygen _UnlimitedOxygen{"unlimitedoxygen", TR("Unlimited Oxygen"), TR("Allows you to stay underwater without losing oxygen.")};
}