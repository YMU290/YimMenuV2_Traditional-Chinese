#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "core/localization/Translator.hpp"

//https://github.com/Tessio/YimMenuV2/tree/fix-unload-crash
namespace YimMenu::Features
{
	class UnloadMenu : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			g_Running = false;
		}
	};

	static UnloadMenu _UnloadMenu{"unloadmenu", TR("Unload"), TR("Unload YimMenuV2.")};
}