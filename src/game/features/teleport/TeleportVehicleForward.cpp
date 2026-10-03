#include "core/commands/Command.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	static FloatCommand _TeleportVehicleForwardDistance{"teleportvehicleforwarddistance", TR("Teleport Distance"), TR("Controls how far forward the vehicle is teleported"), 1.0f, 100.0f, 10.0f};

	class TeleportVehicleForward : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!Self::GetVehicle())
				return;

			const auto pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Self::GetVehicle().GetHandle(), 0.0f, _TeleportVehicleForwardDistance.GetState(), 0.0f);
			Self::GetVehicle().SetPosition({pos.x, pos.y, pos.z});
		}
	};

	static TeleportVehicleForward _TeleportVehicleForward{"teleportvehicleforward", TR("Teleport Vehicle Forward"), TR("Instantly teleports your vehicle forward by the selected distance")};
}
