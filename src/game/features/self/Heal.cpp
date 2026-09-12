#include "core/commands/Command.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class Heal : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			int maxHealth = Self::GetPed().GetMaxHealth();
			int maxArmour = Self::GetPlayer().GetMaxArmour();

			Self::GetPed().SetHealth(maxHealth);
			Self::GetPed().SetArmour(maxArmour);
		}
	};

	class AutoHeal : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			if (Self::GetPed().GetHealth() < Self::GetPed().GetMaxHealth())
				Self::GetPed().SetHealth(Self::GetPed().GetMaxHealth());
		}
	};

	class AutoArmor : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			if (Self::GetPed().GetArmour() < Self::GetPlayer().GetMaxArmour())
				Self::GetPed().SetArmour(Self::GetPlayer().GetMaxArmour());
		}
	};

	static Heal _Heal{"heal", TR("Heal"), TR("Restores your health and armour.")};
	static AutoHeal _AutoHeal{"autoheal", TR("Auto Heal"), TR("Automatically restores your health when it decreases.")};
	static AutoArmor _AutoArmor{"autoarmor", TR("Auto Armor"), TR("Automatically restores your armor when it decreases.")};
}