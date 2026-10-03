#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "types/script/Timer.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class ResetCasinoCooldown : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				Stats::SetInt("MPPLY_CASINO_CHIPS_WON_GD", 0);
				Stats::SetInt("MPPLY_CASINO_BAN_TIME", 0);
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
			else
			{
				Notifications::Show("YimMenuV2", "You Must be Online", NotificationType::Error);
			}
		}
	};
	static ResetCasinoCooldown _ResetCasinoCooldown{
	    "reset_casino_cd",
	    TR("Reset Casino Cooldowns"),
	    TR("Resets casino daily chip limit and gambling ban")};
	//vehicle reset
	class ResetVehicleSellCooldown : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				Stats::SetInt("MPPLY_VEHICLE_SELL_TIME", 0);
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
			else
			{
				Notifications::Show("YimMenuV2", "You Must be Online", NotificationType::Error);
			}
		}
	};
	static ResetVehicleSellCooldown _ResetVehicleSellCooldown{
	    "reset_vehicle_sell_cd",
	    TR("Reset Vehicle Sell Cooldown"),
	    TR("Resets the vehicle sell cooldown timer")};

	class ResetDeliveryCooldown : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					ScriptGlobal(2686095).At(4357).At(260).At(7, 2).As<TIMER*>()->Destroy();
				});
				STATS::STAT_SAVE(0, 0, 3, 0);
			}
			else
			{
				Notifications::Show("YimMenuV2", "You Must be Online", NotificationType::Error);
			}
		}
	};
	static ResetDeliveryCooldown _ResetDeliveryCooldown{
	    "Reset_vehicle_Delivery_cd",
	    TR("Reset Vehicle Delivery Cooldown"),
	    TR("Reset Vehicle Delivery Cooldown")};
}
