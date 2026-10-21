#include "core/commands/Command.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Features
{
	static constexpr int SERVICE_GLOBAL_BASE = 2733326;
	inline void RequestService(int index)
	{
		*ScriptGlobal(SERVICE_GLOBAL_BASE).At(index).As<int*>() = 1;
	}
	class RequestMOC : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(577);
		}
	};

	class RequestAvenger : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(585);
		}
	};

	class RequestTerrorbyte : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(591);
		}
	};

	class RequestKosatka : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(613);
		}
	};

	class RequestAcidLab : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(592);
		}
	};

	class RequestAcidBike : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(648);
		}
	};

	class RequestAmmoDrop : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(538);
		}
	};

	class RequestBullShark : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(546);
		}
	};

	class RequestAirstrike : public Command
	{
		using Command::Command;
		void OnCall() override
		{
			RequestService(3580);
		}
	};


	static RequestMOC _reqMoc{
	"requestmoc",
	TR("Request MOC"),
	TR("Requests the Mobile Operations Center")};

static RequestAvenger _reqAvenger{
	"requestavenger",
	TR("Request Avenger"),
	TR("Requests the Avenger aircraft")};

static RequestTerrorbyte _reqTb{
	"requestterrorbyte",
	TR("Request Terrorbyte"),
	TR("Requests the Terrorbyte")};

static RequestKosatka _reqKosatka{
	"requestkosatka",
	TR("Request Kosatka"),
	TR("Requests the Kosatka submarine")};

static RequestAcidLab _reqAcid{
	"requestacidlab",
	TR("Request Acid Lab"),
	TR("Requests the Acid Lab")};

static RequestAcidBike _reqBike{
	"requestacidbike",
	TR("Request Acid Lab Bike"),
	TR("Requests the Acid Lab delivery bike")};

static RequestAmmoDrop _reqAmmo{
	"requestammodrop",
	TR("Ammo Drop"),
	TR("Requests an ammo drop")};

static RequestBullShark _reqBull{
	"requestbullshark",
	TR("Bull Shark"),
	TR("Requests Bull Shark Testosterone")};

static RequestAirstrike _reqStrike{
	"requestairstrike",
	TR("Airstrike"),
	TR("Requests an airstrike")};

}