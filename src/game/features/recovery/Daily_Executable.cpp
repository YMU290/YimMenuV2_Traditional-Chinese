#pragma once
#include "core/commands/Command.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/Stats.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class ClubPopularity : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetInt("MPx_CLUB_POPULARITY", 1000);
				});
			}
		}
	};
	static ClubPopularity _ClubPopularity{"club_popularity", TR("Nightclub Popularity At 100%"), TR("Set Nightclub Popularity At 100%")};
	class ClubPayout : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetInt("MPX_CLUB_PAY_TIME_LEFT", -1);
				});
			}
		}
	};
	static ClubPayout _ClubPayout{"club_payout", TR("Nightclub Payout"), TR("Force Next Nightclub Payout")};
	class BailAgent1 : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetPackedInt(42270, 1);
				});
			}
		}
	};
	static BailAgent1 _BailAgent1{"bail_agent1", TR("Bail Enforcement Agent 1"), TR("Agent 1 will fill your safe")};
	class BailAgent2 : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetPackedInt(42271, 1);
				});
			}
		}
	};
	static BailAgent2 _BailAgent2{"bail_agent2", TR("Bail Enforcement Agent 2"), TR("Agent 2 will fill your safe")};
	class CarWash : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetPackedInt(24924, 0);
				});
			}
		}
	};
	static CarWash _CarWash{"carwash", TR("Reset Hands On Car Wash Heat"), TR("Reset Hands On Car Wash Heat")};
	class SmokeWater : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetPackedInt(24925, 0); 
				});
			}
		}
	};
	static SmokeWater _SmokeWater{"smokewater", TR("Reset Smoke On The Water Heat"), TR("Reset Smoke On The Water Heat")};

	
	class Helitours : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetPackedInt(24926, 0);
				});
			}
		}
	};
	static Helitours _Helitours{"helitours", TR("Reset Higgins Helitours Heat"), TR("Reset Higgins Helitours Heat")};
	class SalvageYard : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					Stats::SetPackedInt(51051, 100);
				});
			}
		}
	};
	static SalvageYard _SalvageYard{"salvageyard", TR("Max Salvage Yard Reputation"), TR("Max Salvage Yard Reputation")};
}
