#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/Weapons.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class GiveAllWeapons : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto weapon : g_WeaponHashes)
				Self::GetPed().GiveWeapon(weapon);
		}
	};

	static GiveAllWeapons _GiveAllWeapons{"giveallweapons", TR("Give All Weapons"), TR("Gives you all weapons")};
}