#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class SuperJump : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			MISC::SET_SUPER_JUMP_THIS_FRAME(Self::GetPlayer().GetId());
			Ped ped = Self::GetPed();
			int handle = ped.GetHandle();
			if (!ENTITY::DOES_ENTITY_EXIST(handle)) 
				return;
			if (WEAPON::HAS_PED_GOT_WEAPON(handle, Joaat("GADGET_PARACHUTE"), false))
			{
				WEAPON::REMOVE_WEAPON_FROM_PED(handle, Joaat("GADGET_PARACHUTE"));
			}		
		}
	};

	static SuperJump _SuperJump{"superjump", TR("Super Jump"), TR("Jump higher than normal")};
}