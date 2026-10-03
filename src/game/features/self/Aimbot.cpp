#include "core/commands/BoolCommand.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class Aimbot : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Apply();
			Pointers.GetAssistedAimTypePatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Restore();
			Pointers.GetAssistedAimTypePatch->Restore();
		}
	};

	class AimbotAimForHead : BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.GetLockOnPosPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.GetLockOnPosPatch->Restore();
		}
	};

	class AimbotTargetDrivers : BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Restore();
		}
	};

	static Aimbot _Aimbot{"aimbot", TR("Aimbot"), TR("Locks on to enemies and other players")};
	static AimbotAimForHead _AimbotAimForHead{"aimbotaimforhead", TR("Aim For Head"), TR("Targets the head when locking on to enemies and other players")};
	static AimbotTargetDrivers _AimbotTargetDrivers{"aimbottargetdrivers", TR("Target Drivers"), TR("Allows aimbot to lock on to enemies and other players in vehicles")};
}