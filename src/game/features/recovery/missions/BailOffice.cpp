#include "core/commands/ListCommand.hpp"
#include "core/commands/Command.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/Stats.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu::Features
{
	enum class eBailOfficeTarget
	{
		TARGET_1,
		TARGET_2,
		TARGET_3
	};
	static constexpr int TargetsDeliveryBools[] = {
	    51199,
	    51200,
	    51201};
	static constexpr int TargetsSecureBools[] = {
	    42274,
	    42275,
	    42276};

	static std::vector<std::pair<int, const char*>> BailTargets = {
	    {static_cast<int>(eBailOfficeTarget::TARGET_1), "Target 1"},
	    {static_cast<int>(eBailOfficeTarget::TARGET_2), "Target 2"},
	    {static_cast<int>(eBailOfficeTarget::TARGET_3), "Target 3"}};

	static ListCommand _BailOfficeTarget{
	    "bailtarget",
	    TR("Bail Office Target"),
	    TR("Bail Office"),
	    BailTargets,
	    0};

	class DeliverTarget : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			FiberPool::Push([] {
				int index = _BailOfficeTarget.GetState();
				Stats::SetPackedBool(TargetsDeliveryBools[index], true);
			});
		}
	};

	static DeliverTarget _DeliverTarget{
	    "baildeliver",
	    TR("Deliver Target"),
	    TR("Bail Office")};

	class SecureTarget : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			FiberPool::Push([] {
				int index = _BailOfficeTarget.GetState();
				Stats::SetPackedBool(TargetsSecureBools[index], true);
			});
		}
	};

	static SecureTarget _SecureTarget{
	    "bailsecure",
	    TR("Secure Target"),
	    TR("Bail Office")};

	class DeliverMostWanted : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			FiberPool::Push([] {
				Stats::SetPackedBool(51202, true);
			});
		}
	};

	static DeliverMostWanted _DeliverMostWanted{
	    "baildeliver_mw",
	    TR("Deliver Most Wanted"),
	    TR("Bail Office")};

	class SecureMostWanted : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			FiberPool::Push([] {
				Stats::SetPackedBool(42251, true);
			});
		}
	};

	static SecureMostWanted _SecureMostWanted{
	    "bailsecure_mw",
	    TR("Secure Most Wanted"),
	    TR("Bail Office")};

	class SkipOfficeDialogues : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			FiberPool::Push([] {
				Stats::SetPackedBool(51190, true);//Introduction
			});
		}
	};

	static SkipOfficeDialogues _SkipOfficeDialogues{
	    "Skip_Office_Dialogues",
	    TR("Skip Bail Office Dialogues"),
	    TR("Skip Bail Office Dialogues")};
}

