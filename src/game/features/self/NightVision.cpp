#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class NightVision : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			GRAPHICS::SET_NIGHTVISION(true);
		}

		virtual void OnDisable() override
		{
			GRAPHICS::SET_NIGHTVISION(false);
		}
	};

	static NightVision _NightVision{"nightvision", TR("Night Vision"), TR("Enables enhanced visibility in dark environments.")};
}
