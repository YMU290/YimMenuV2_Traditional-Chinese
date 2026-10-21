#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	static FloatCommand _SuperRunMoveRateOverride{"moverateoverride", TR("Move Rate Override"), TR("Multipler for base run/sprint speed"), 0.0f, 10.0f, 2.0f};
	static FloatCommand _SuperRunRunSprintMultiplier{"runsprintswimmultiplier", TR("Run/Sprint/Swim Multiplier"), TR("Multipler with which the run/sprint/swim speed is increased with until maximum speed is reached"), 1.0f, 1.49f, 1.0f};

	class SuperRun : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnDisable() override
		{
			if (auto player = Self::GetPlayer())
			{
				auto playerId = player.GetId();
				PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(playerId, 1.0f);
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(playerId, 1.0f);
			}
		}

		virtual void OnEnable() override
		{
			if (auto player = Self::GetPlayer())
			{
				auto playerId = player.GetId();
				PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(playerId, _SuperRunRunSprintMultiplier.GetState());
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(playerId, _SuperRunRunSprintMultiplier.GetState());
			}
		}

		virtual void OnTick() override
		{
			if (auto ped = Self::GetPed())
				PED::SET_PED_MOVE_RATE_OVERRIDE(ped.GetHandle(), _SuperRunMoveRateOverride.GetState());
		}
	};

	static SuperRun _Superrun{"superrun", TR("Super Run"), TR("Run faster than normal")};
}