#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Stats.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class AutoSource : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			Stats::SetPackedBoolRange(32359, 32363, true);
			Stats::SetPackedBool(36828, true);
			ScriptMgr::Yield();
		}
		virtual void OnDisable() override
		{
			Stats::SetPackedBoolRange(32359, 32363, false);
			Stats::SetPackedBool(36828, false);
		}
	};
	static AutoSource _AutoSource{
	    "auto_source",
	    TR("Auto Source"),
	    TR("CEO and Hangar Resupply")};
}
