#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class InfiniteSpecialAbility : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			auto id = Self::GetPlayer().GetId();

			if (PLAYER::IS_SPECIAL_ABILITY_UNLOCKED(Self::GetPed().GetModel()) && !PLAYER::IS_SPECIAL_ABILITY_METER_FULL(id, 0))
				PLAYER::SPECIAL_ABILITY_CHARGE_ABSOLUTE(id, 200, true, 0);
		}
	};

	static InfiniteSpecialAbility _InfiniteSpecialAbility{"infspecialability", TR("Infinite Special Ability"), TR("Ensures that the special ability bar never runs out")};
}