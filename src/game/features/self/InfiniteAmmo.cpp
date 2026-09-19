#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class InfiniteAmmo : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPed())
				Self::GetPed().SetInfiniteAmmo(true);
		}

		virtual void OnDisable() override
		{
			if (Self::GetPed())
				Self::GetPed().SetInfiniteAmmo(false);
		}
	};

	static InfiniteAmmo _InfiniteAmmo{"infiniteammo", TR("Infinite Ammo"), TR("You will never run out of ammo")};
}