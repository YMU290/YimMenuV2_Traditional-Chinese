#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	class MobileRadio : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;


		virtual void OnTick() override
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		}

		virtual void OnDisable() override
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		}
	};

	static MobileRadio _MobileRadio{"mobileradio", TR("Mobile Radio"), TR("Allows you to listen to any radio station on foot with Hotkey Q")};
}
