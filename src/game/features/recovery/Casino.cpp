#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Stats.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/backend/Tunables.hpp"
#include "core/backend/ScriptMgr.hpp"
#include <set>
#include "core/localization/Translator.hpp"

namespace YimMenu::Features

{
	static std::vector<std::pair<int, const char*>> wheelPrizes = {
	    {0, (const char*)u8"服飾 1"},
	    {1, (const char*)u8"2,500 RP"},
	    {2, (const char*)u8"現金$20,000"},
	    {3, (const char*)u8"10,000 籌碼"},
	    {4, (const char*)u8"打折優惠"},
	    {5, (const char*)u8"5,000 RP"},
	    {6, (const char*)u8"現金$30,000"},
	    {7, (const char*)u8"15,000 籌碼"},
	    {8, (const char*)u8"服飾 2"},
	    {9, (const char*)u8"7,500 RP"},
	    {10, (const char*)u8"20,000 籌碼"},
	    {11, (const char*)u8"神秘大獎"},
	    {12, (const char*)u8"服飾 3"},
	    {13, (const char*)u8"10,000 RP"},
	    {14, (const char*)u8"現金$40,000"},
	    {15, (const char*)u8"25,000 籌碼"},
	    {17, (const char*)u8"15,000 RP"},
	    {18, (const char*)u8"載具"},
	    {19, (const char*)u8"現金$50,000"},
	};

	static ListCommand _CasinoWheelPrize{"casinowheelprize", TR("Lucky Wheel Prize"), TR("Select prize for lucky wheel"), wheelPrizes, 18};

	class CasinoGiveWheelPrize : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			int prize = _CasinoWheelPrize.GetState();
			// 設定獎品 1.73 (iLocal_311.f_14)
			*ScriptLocal("casino_lucky_wheel"_J, 325).As<int*>() = prize;
			// 設定狀態為發放獎品 1.73 (iLocal_311.f_45 = 11)
			*ScriptLocal("casino_lucky_wheel"_J, 356).As<int*>() = 11;
			
			LOG(INFO) << "Lucky wheel prize given: " << prize;
		}
	};
	
	class CasinoBypass : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			Stats::SetInt("MPPLY_CASINO_CHIPS_WON_GD", 0);
			Stats::SetInt("MPPLY_CASINO_CHIPS_WONTIM", 0);
			Stats::SetInt("MPPLY_CASINO_GMBLNG_GD", 0);
			Stats::SetInt("MPPLY_CASINO_BAN_TIME", 0);
			Stats::SetInt("MPPLY_CASINO_CHIPS_PURTIM", 0);
			Stats::SetInt("MPPLY_CASINO_CHIPS_PUR_GD", 0);

			*ScriptGlobal(1972794).As<BOOL*>() = true;

			ScriptMgr::Yield(5000ms);
		}
	};

	static std::vector<std::pair<int, const char*>> chipLimits = {
	    {20000, (const char*)u8"20,000 籌碼 (Standard)"},
	    {50000, (const char*)u8"50,000 籌碼 (Penthouse)"}};

	static ListCommand _CasinoChipLimit{"casinochiplimit", TR("Chip Purchase Limit"), TR("Select chip purchase limit"), chipLimits, 50000};

	class CasinoAcquireChips : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			int limit = _CasinoChipLimit.GetState();
			int tunableHash = (limit == 20000) ? 0x7E4B8C1A : 0x7E4B8C1B;
			Tunable buyLimit(tunableHash);
			if (buyLimit.IsReady())
				buyLimit.Set(limit);
			LOG(INFO) << "Chip purchase limit set to: " << limit;
		}
	};

	class CasinoTradeChips : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Tunable tradeLimit(0x2C9F4D8C);
			if (tradeLimit.IsReady())
				tradeLimit.Set(10000000);
			LOG(INFO) << "Chip trade limit set to 10,000,000";
		}
	};
	 
	class CasinoManipulateRigSlotMachines : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		int slots_random_results_table = 1357; // Static_1381.f_1[][]
		std::set<int> slots_blacklist = {9, 21, 22, 87, 152};
		int spin_state_var = 1675;
		std::set<int> spin_state_whitelist = {8, 14};

		virtual void OnTick() override
		{
			if (Scripts::SafeToModifyFreemodeBroadcastGlobals() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J))
			{
				Player casinoSlotsScriptHostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("casino_slots", -1, 0);
				auto casinoSlotsScriptHostPlayerId = casinoSlotsScriptHostPlayer.GetId();
				auto selfPlayerId = Self::GetPlayer().GetId();
				if (casinoSlotsScriptHostPlayerId != selfPlayerId)
				{
					Scripts::ForceScriptHost(Scripts::FindScriptThread("casino_slots"_J));
				}
				int* spin_state = ScriptLocal("casino_slots"_J, spin_state_var).As<int*>();


				bool needs_run = false;
				for (int slots_iter = 3; slots_iter <= 196; ++slots_iter)
				{
					if (!slots_blacklist.contains(slots_iter))
					{
						if (*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() != 6)
						{
							needs_run = true;
							break;
						}
					}
				}
				if (needs_run)
				{
					for (int slots_iter = 3; slots_iter <= 196; ++slots_iter)
					{
						if (!slots_blacklist.contains(slots_iter) && spin_state_whitelist.contains(*spin_state))
						{
							int slot_result = 6;
							*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
						}
					}
				}
			}
		}

virtual void OnDisable() override
		{
			if (Scripts::SafeToModifyFreemodeBroadcastGlobals() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("casino_slots"_J))
			{
				Player casinoSlotsScriptHostPlayer = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("casino_slots", -1, 0);
				auto casinoSlotsScriptHostPlayerId = casinoSlotsScriptHostPlayer.GetId();
				auto selfPlayerId = Self::GetPlayer().GetId();
				if (casinoSlotsScriptHostPlayerId != selfPlayerId)
				{
					Scripts::ForceScriptHost(Scripts::FindScriptThread("casino_slots"_J));
				}

				int* spin_state = ScriptLocal("casino_slots"_J, spin_state_var).As<int*>();
				// waiting for reset until next time using
				while (!spin_state_whitelist.contains(*spin_state))
				{
					ScriptMgr::Yield();
					spin_state = ScriptLocal("casino_slots"_J, spin_state_var).As<int*>();
					if (spin_state == nullptr){
						return;
					}
				}

				for (int slots_iter = 3; slots_iter <= 196; ++slots_iter)
				{
					if (!slots_blacklist.contains(slots_iter))
					{
						int slot_result = 6;
						std::srand(static_cast<unsigned int>(std::time(0)) + slots_iter);
						slot_result = 3 + std ::rand() % 7; // Generates a pseudo random number [3,9] 
						*ScriptLocal("casino_slots"_J, slots_random_results_table + slots_iter).As<int*>() = slot_result;
					}
				}
			}
		}
	};
	/*
	class CasinoSlotsWin : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			int randomResultTable = 1374; 
			for (int i = 3; i <= 196; i++)
			{
				if (i != 67 && i != 132)
				{
					*ScriptLocal("casino_slots"_J, randomResultTable + i).As<int*>() = 6;
				}
			}
		}
	};

	class CasinoSlotsLose : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			int randomResultTable = 1374; 
			for (int i = 3; i <= 196; i++)
			{
				if (i != 67 && i != 132)
				{
					*ScriptLocal("casino_slots"_J, randomResultTable + i).As<int*>() = 0;
				}
			}
		}
	};
	   */
	class CasinoMembershipBonus : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			*ScriptGlobal(1973325).As<int*>() = 1;
		}
	};

	//static CasinoSlotsWin _CasinoSlotsWin{"casinoslotswin", TR("Rig Slot Machines"), TR("Forces slot machines to give jackpot")};
	//static CasinoSlotsLose _CasinoSlotsLose{"casinoslotslose", TR("Lose Slot Machines"), TR("Forces slot machines to lose")};
	static CasinoManipulateRigSlotMachines _CasinoManipulateRigSlotMachines{"casinomanipulaterigslotmachines", TR("Manipulate Rig Slot Machines"), TR("Lets you win the Rig Slot Machines every time")};
	static CasinoGiveWheelPrize _CasinoGiveWheelPrize{"casinogivewheelprize", TR("Give Lucky Wheel Prize"), TR("Gives selected lucky wheel prize")};
	static CasinoBypass _CasinoBypass{"casinobypass", TR("Bypass Casino Limits"), TR("Bypasses casino purchase and time limits")};
	static CasinoAcquireChips _CasinoAcquireChips{"casinoacquirechips", TR("Set Chip Purchase Limit"), TR("Sets maximum chips you can buy")};
	static CasinoTradeChips _CasinoTradeChips{"casinotradechips", TR("Set Chip Trade Limit"), TR("Sets maximum chips you can trade in")};
	static CasinoMembershipBonus _CasinoMembershipBonus{"casino_membership_bonus", TR("Casino Membership Bonus"), TR("Triggers the Casino Membership Bonus.")};
}
