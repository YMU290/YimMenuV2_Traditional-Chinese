#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class BeastJump : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());

			if (PED::IS_PED_JUMPING(Self::GetPed().GetHandle()))
				ENTITY::APPLY_FORCE_TO_ENTITY(Self::GetPed().GetHandle(), 1, 0.0f, 0.0f, 12.0f, 0.0f, 0.0f, 0.0f, 0, false, true, true, false, true);
		}
	};

	static BeastJump _BeastJump{"beastjump", TR("Beast Jump"), TR("Adds an extremely powerful high jump ability.")};
}
