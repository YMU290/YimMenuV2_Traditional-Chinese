#include "core/commands/BoolCommand.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class AllowGenderChange : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Stats::SetInt("MPX_ALLOW_GENDER_CHANGE", 52);
		}

		virtual void OnDisable() override
		{
			Stats::SetInt("MPX_ALLOW_GENDER_CHANGE", 0);
		}
	};

	static AllowGenderChange _AllowGenderChange{"allowgenderchange", TR("Allow Gender Change"), TR("Allows the player to change the character's gender")};
}