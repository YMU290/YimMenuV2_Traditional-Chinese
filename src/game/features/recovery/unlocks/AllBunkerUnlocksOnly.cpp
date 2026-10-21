#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
    class BunkerUnlocks : public Command
    {
        using Command::Command;
        virtual void OnCall() override    
        {
            if (*Pointers.IsSessionStarted)
            {
                for (int i = 15381; i <= 15382; ++i)
                    Stats::SetPackedBool(i, true);

                for (int i = 15428; i <= 15439; ++i)
                    Stats::SetPackedBool(i, true);

                for (int i = 15447; i <= 15474; ++i)
                    Stats::SetPackedBool(i, true);

                for (int i = 15491; i <= 15499; ++i)
                    Stats::SetPackedBool(i, true);

                STATS::STAT_SAVE(0, 0, 3, 0);
            }
            else
            {
                Notifications::Show("All Bunker research unlocked!", "All Bunker Research Only Please join any freemode session.", NotificationType::Error);
            }
        }
    };
    static BunkerUnlocks _BunkerUnlocks{
        "BunkerUnlocks",
        TR("Bunker Unlocks"),
        TR("Bunker Unlocks")};

}
