#include "core/commands/LoopedCommand.hpp"
#include "core/memory/BytePatches.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/localization/Translator.hpp"
namespace YimMenu::Features
{
	//Needs Work
	class FPSUnlock : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			if (!Pointers.FrameLimiter_Patch)
				return;
			Pointers.FrameLimiter_Patch->Apply();
		}

		virtual void OnDisable() override
		{
			if (!Pointers.FrameLimiter_Patch)
				return;
			Pointers.FrameLimiter_Patch->Restore();
		}
	};
	static FPSUnlock _FPSUnlock{"unlockfps", TR("Unlock FPS Bypass Frame Limiter"), TR("Bypass Frame Limiter")};
}
