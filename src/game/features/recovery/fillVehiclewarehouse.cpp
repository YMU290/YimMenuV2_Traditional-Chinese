#include "core/commands/Command.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class FillVehicleWarehouse : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			constexpr std::size_t base = 32359;
			for (int i = 0; i < 5; i++)
			{
				ScriptGlobal(base + i).As<bool&>() = true;
			}
		}
	};

	static FillVehicleWarehouse _FillVehicleWarehouse{
	    "fillvehwarehouse",
	    TR("Fill Vehicle Warehouse"),
	    TR("Instantly fills all 5 Import/Export vehicle warehouses.")};
}
