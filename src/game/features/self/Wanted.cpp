#include "core/commands/Command.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	static IntCommand _WantedSlider{"wantedslider", TR("Wanted Slider"), TR("Wanted level to set/freeze"), 0, 5, 0};

	class ClearWanted : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPlayer().SetWantedLevel(0);
		}
	};

	class SetWanted : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPlayer().SetWantedLevel(_WantedSlider.GetState());
		}
	};

	class NeverWanted : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			Self::GetPlayer().SetWantedLevel(0);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}

		virtual void OnDisable() override
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
		}
	};

	class FreezeWanted : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPlayer().GetWantedLevel() != _WantedSlider.GetState())
				Self::GetPlayer().SetWantedLevel(_WantedSlider.GetState());
			PLAYER::SET_MAX_WANTED_LEVEL(_WantedSlider.GetState());
		}
	};

	static ClearWanted _ClearWanted{"clearwanted", TR("Clear Wanted"), TR("Clears your wanted level")};
	static SetWanted _SetWanted{"setwanted", TR("Set Wanted"), TR("Sets your wanted level to the desired level")};
	static NeverWanted _NeverWanted{"neverwanted", TR("Never Wanted"), TR("Never gain a wanted level")};
	static FreezeWanted _FreezeWanted{"freezewanted", TR("Freeze Wanted"), TR("Freeze your wanted level to the desired level")};
}