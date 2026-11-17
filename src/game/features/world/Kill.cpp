#include "core/commands/Command.hpp"
#include "game/gta/Pools.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class KillAll : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
					ped.Kill();
			}
		}
	};

	class KillAllEnemies : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer() && ped.IsEnemy())
					ped.Kill();
			}
		}
	};

	static KillAll _KillAll{"killallpeds", TR("Kill All Peds"), TR("Kills all peds in the game world")};
	static KillAllEnemies _KillAllEnemies{"killallenemies", TR("Kill All Enemies"), TR("Kills all enemies in the game world")};
}