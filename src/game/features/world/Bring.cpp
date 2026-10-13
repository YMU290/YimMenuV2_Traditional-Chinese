#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class BringAllObjs : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto pos = Self::GetPed().GetPosition();
			for (auto obj : Pools::GetObjects())
			{
				if (obj)
				{
					obj.ForceControl();
					obj.SetPosition(pos);
				}
			}
		}
	};

	class BringAllPeds : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto pos = Self::GetPed().GetPosition();
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
				{
					ped.ForceControl();
					ped.SetPosition(pos);
				}
			}
		}
	};

	class BringAllVehs : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto pos = Self::GetPed().GetPosition();
			for (auto veh : Pools::GetVehicles())
			{
				veh.ForceControl();
				veh.SetPosition(pos);
			}
		}
	};

	static BringAllObjs _BringAllObjs{"bringobjs", TR("Bring All Objects"), "Teleports all game objects to you"};
	static BringAllPeds _BringAllPeds{"bringpeds", TR("Bring All Peds"), "Teleports all game peds to you"};
	static BringAllVehs _BringAllVehs{"bringvehs", TR("Bring All Vehicles"), "Teleports all game vehicles to you"};
}