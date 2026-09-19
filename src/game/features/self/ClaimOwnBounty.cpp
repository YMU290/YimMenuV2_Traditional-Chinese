#include "core/commands/Command.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	class ClaimOwnBounty : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted)
			{
				FiberPool::Push([] {
					*ScriptGlobal(2359296).At(0, 5574).At(5156).At(13).As<int*>() = 2880000;
				});
			}
			else
			{
				Notifications::Show("YimMenuV2", TR("You must be online"), NotificationType::Error);
			}
		}
	};

	static ClaimOwnBounty _ClaimOwnBounty{"claimownbounty", TR("Claim Own Bounty"), TR("Removes the wait and allows you to claim your own bounty")};
}
