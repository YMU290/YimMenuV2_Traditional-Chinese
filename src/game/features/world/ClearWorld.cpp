#include "core/commands/Command.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
    class ClearWorld : public Command
    {
        using Command::Command;

        virtual void OnCall() override
        {
            *ScriptGlobal(1690454).As<int*>() = 1; // Peds
            *ScriptGlobal(1690455).As<int*>() = 1; // Vehicles
            *ScriptGlobal(1690456).As<int*>() = 1; // Objects
        }
    };

    static ClearWorld _ClearWorld{
        "clearworld",
        TR("Clear World"),
        TR("Clear World (Remove Ped, Vehicles & Objects)")
    };
}
