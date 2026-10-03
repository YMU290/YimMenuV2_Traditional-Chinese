#include "Recovery.hpp"
#include "Recovery/HeistModifier.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "Recovery/DailyActivities.hpp"
#include "game/frontend/items/Items.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
#define ICON_FA_SACK_DOLLAR "\xef\x93\x80"
		Submenu::Submenu(TR("Recovery"), ICON_FA_SACK_DOLLAR)
	{
		auto main = std::make_shared<Category>(TR("Main"));
		auto businesses = std::make_shared<Category>(TR("Businesses"));
		auto casino = std::make_shared<Category>(TR("Casino"));
		auto unlocks = std::make_shared<Category>(TR("Unlocks"));
		auto generalUnlocks = std::make_shared<Group>(TR("General"));
		auto nightclubGroup = std::make_shared<Group>("Nightclub");
		auto LSCMGroupe = std::make_shared<Group>(TR("LS Car Meet"));
		auto ArenaWarGroup = std::make_shared<Group>("Arena War");
		auto trophies = std::make_shared<Group>(TR("Trophies"));
		auto skip = std::make_shared<Group>(TR("Skipper"));
		auto Unreleased = std::make_shared<Group>(TR("Unreleased"));
		auto requestServices = std::make_shared<Group>(TR("Request Services"));
		auto missions = std::make_shared<Group>(TR("Missions"));
		auto achievements = std::make_shared<Group>(TR("Unlock Achievements"));
		auto cooldown = std::make_shared<Group>(TR("Cooldown"));
		auto Safehouseinhills = std::make_shared<Group>(TR("Safehouse in the Hills"));

		auto generalGroup = std::make_shared<Group>(TR("General"));
		auto gunvanGroup = std::make_shared<Group>(TR("Gun Van"));
		auto businessGroup = std::make_shared<Group>(TR("Business"));
		auto Bailloffice = std::make_shared<Group>(TR("Bail Office"));
		auto Misc_business = std::make_shared<Group>(TR("Misc"));
		auto over_lay = std::make_shared<Group>(TR("Overlay"));
		auto instantfinish = std::make_shared<Group>(TR("Instant Finish Missions"));

		auto casinoSlots = std::make_shared<Group>(TR("Slot Machines"));
		auto casinoWheel = std::make_shared<Group>(TR("Lucky Wheel"));
		auto casinoMisc = std::make_shared<Group>(TR("Casino Misc"));

		auto free = std::make_shared<Group>(TR("Free"));
		auto exhibitGroup = std::make_shared<Group>(TR("Exhibit Loot"));
		auto stashHouse = std::make_shared<Group>(TR("Stash House"));

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J,TR("Play All Missions Solo")));
		//generalGroup->AddItem(std::make_shared<BoolCommandItem>("businessoverlay"_J,TR("Business Overlay")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("unlockgtaplus"_J,TR("Unlock GTA+")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("overriderpmultiplier"_J,TR("Override RP Multiplier")));
		generalGroup->AddItem(std::make_shared<ConditionalItem>("overriderpmultiplier"_J, std::make_shared<FloatCommandItem>("rpmultiplierinput"_J,TR("RP Multiplier Input"))));
		generalGroup->AddItem(std::make_shared<CommandItem>("maxskills"_J,TR("Max All Skills")));
		generalGroup->AddItem(std::make_shared<IntCommandItem>("rpslider"_J, TR("Character Level")));
		generalGroup->AddItem(std::make_shared<CommandItem>("applyrp"_J,TR("Apply RP")));
		generalGroup->AddItem(std::make_shared<CommandItem>("Rockstar_dev_tshirt"_J,TR("Rockstar_Dev_Tshirt")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("freechangeappearance"_J,TR("Change Appearance For Free")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("nochangeappearancecooldown"_J,TR("No Change Appearance Cooldown")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("allowgenderchange"_J,TR("Allow Gender Change")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("autocollecttargets"_J,TR("Auto Collect Targets")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("peddropcash"_J,TR("Ped Drop Cash")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("vehicledropcash"_J,TR("Vehicle Drop Cash")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("casinosolo"_J,TR("Casino Solo")));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("highdemandsell"_J,TR("High Demand Sell")));


		gunvanGroup->AddItem(std::make_shared<ListCommandItem>("gunvanslot"_J, TR("gunvanslot")));
		gunvanGroup->AddItem(std::make_shared<ListCommandItem>("gunvanweapon"_J, TR("gunvanweapon")));
		gunvanGroup->AddItem(std::make_shared<CommandItem>("setgunvanweapon"_J, TR("setgunvanweapon")));
		gunvanGroup->AddItem(std::make_shared<CommandItem>("removegunvanweapon"_J, TR("removegunvanweapon")));
		gunvanGroup->AddItem(std::make_shared<ListCommandItem>("gunvanlocation"_J, TR("gunvanlocation")));
		gunvanGroup->AddItem(std::make_shared<CommandItem>("setgunvanlocation"_J, TR("setgunvanlocation")));
		gunvanGroup->AddItem(std::make_shared<CommandItem>("teleportgunvan"_J, TR("teleportgunvan")));
		gunvanGroup->AddItem(std::make_shared<BoolCommandItem>("gunvanskins"_J, TR("gunvanskins")));
		gunvanGroup->AddItem(std::make_shared<BoolCommandItem>("gunvanblip"_J, TR("gunvanblip")));


		nightclubGroup->AddItem(std::make_shared<CommandItem>("maxnightclubpopularity"_J,TR("Max Nightclub Popularity")));
		nightclubGroup->AddItem(std::make_shared<BoolCommandItem>("keepnightclubpopularity"_J, TR("Keep Nightclub Popularity Max")));
		nightclubGroup->AddItem(std::make_shared<IntCommandItem>("nightclubpopularityinterval"_J, TR("Popularity Loop Interval (min)")));
		nightclubGroup->AddItem(std::make_shared<BoolCommandItem>("autocollectnightclubsafe"_J, TR("Auto Collect Nightclub Safe")));
		nightclubGroup->AddItem(std::make_shared<IntCommandItem>("nightclubsafeinterval"_J, TR("Safe Collection Interval (min)")));
		nightclubGroup->AddItem(std::make_shared<BoolCommandItem>("autoresetnightclubpaytime"_J, TR("Auto Reset Pay Time Left")));
		nightclubGroup->AddItem(std::make_shared<IntCommandItem>("nightclubpaytimeinterval"_J, TR("Pay Time Reset Interval (min)")));


		businessGroup->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J,TR("Business")));
		businessGroup->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J,TR("Claim Safe Earnings")));

		businessGroup->AddItem(std::make_shared<CommandItem>("resupplybusiness"_J, TR("Resupply Business")));
		businessGroup->AddItem(std::make_shared<CommandItem>("hangerresupply"_J, TR("Resupply Hanger Supplies")));
		businessGroup->AddItem(std::make_shared<CommandItem>("warehouseresupply"_J, TR("Resupply Warehouse Supplies")));
		businessGroup->AddItem(std::make_shared<CommandItem>("nightclubpopularity"_J, TR("Max Nightclub Popularity")));
		businessGroup->AddItem(std::make_shared<CommandItem>("salvageyardpopularity"_J, TR("Max Salvage Yard Popularity")));
		businessGroup->AddItem(std::make_shared<CommandItem>("moneyfrontheatremove"_J, TR("Remove Money Front Heat")));
		businessGroup->AddItem(std::make_shared<BoolCommandItem>("removeresupplycooldown"_J, TR("Remove Resupply Cooldown")));
		businessGroup->AddItem(std::make_shared<BoolCommandItem>("enforceeasiestmission"_J, TR("Enforce Easiest Mission")));

		
		over_lay->AddItem(std::make_shared<BoolCommandItem>("businessoverlay"_J, TR("Show Business Overlay")));
		over_lay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("showwarehouse"_J,TR("Show Warehouse"))));
		over_lay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("showhangar"_J,TR("Show Hangar"))));		
		//over_lay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("showbusinesses"_J,TR("Show Businesses"))));
		over_lay->AddItem(std::make_shared<ConditionalItem>("businessoverlay"_J, std::make_shared<BoolCommandItem>("shownightclub"_J,TR("Show Nightclub"))));


	   Bailloffice->AddItem(std::make_shared<ListCommandItem>("bailtarget"_J, TR("bailtarget")));
	   Bailloffice->AddItem(std::make_shared<CommandItem>("baildeliver"_J, TR("baildeliver")));
	   Bailloffice->AddItem(std::make_shared<CommandItem>("bailsecure"_J, TR("bailsecure")));
	   Bailloffice->AddItem(std::make_shared<CommandItem>("baildeliver_mw"_J, TR("baildeliver_mw")));
	   Bailloffice->AddItem(std::make_shared<CommandItem>("bailsecure_mw"_J, TR("bailsecure_mw")));
	   Bailloffice->AddItem(std::make_shared<CommandItem>("Skip_Office_Dialogues"_J, TR("Skip_Office_Dialogues")));

	  Misc_business->AddItem(std::make_shared<BoolCommandItem>("mansion_business_boost"_J, TR("mansion_business_boost")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("club_popularity"_J, TR("club_popularity")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("club_payout"_J, TR("club_payout")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("bail_agent1"_J, TR("bail_agent1")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("bail_agent2"_J, TR("bail_agent2")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("carwash"_J, TR("carwash")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("smokewater"_J, TR("smokewater")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("helitours"_J, TR("helitours")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("salvageyard"_J, TR("salvageyard")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("auto_source"_J, TR("auto_source")));
	  Misc_business->AddItem(std::make_shared<CommandItem>("fillvehwarehouse"_J,TR("Fill Vehicle Warehouse")));

	  casinoSlots->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J,TR("Manipulate Rig Slot Machines")));
	  //casinoSlots->AddItem(std::make_shared<CommandItem>("casinoslotswin"_J,TR("Rig Slot Machines")));
	  //casinoSlots->AddItem(std::make_shared<CommandItem>("casinoslotslose"_J,TR("Lose Slot Machines"))); 
	  casinoWheel->AddItem(std::make_shared<ListCommandItem>("casinowheelprize"_J, TR("Lucky Wheel Prize")));
	  casinoWheel->AddItem(std::make_shared<CommandItem>("casinogivewheelprize"_J, TR("Give Lucky Wheel Prize")));
	  casinoMisc->AddItem(std::make_shared<BoolCommandItem>("casinobypass"_J, TR("Bypass Casino Limits")));
	  casinoMisc->AddItem(std::make_shared<ListCommandItem>("casinochiplimit"_J, TR("Set Chip Purchase Limit")));
	  casinoMisc->AddItem(std::make_shared<CommandItem>("casinoacquirechips"_J, TR("Acquire Chips")));
	  casinoMisc->AddItem(std::make_shared<CommandItem>("casinotradechips"_J, TR("Trade Chips")));
	  casinoMisc->AddItem(std::make_shared<BoolCommandItem>("casino_membership_bonus"_J, TR("Casino Membership Bonus")));
	  //casinoBlackJack->AddItem(std::make_shared<CommandItem>("casinoblackjackforcewin"_J));
	  //casinoBlackJack->AddItem(std::make_shared<CommandItem>("casinoblackjackdealerbust"_J));


	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlockallcareerprogress"_J, TR("unlockallcareerprogress")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlockalltattoos"_J, TR("unlockalltattoos")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("BunkerUnlocks"_J, TR("BunkerUnlocks")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlockallAwards"_J, TR("unlockallAwards")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlock_paints"_J, TR("unlock_paints")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlock_packed_bools"_J, TR("unlock_packed_bools")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlock_misc"_J, TR("unlock_misc")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("Unlock_Gunrunning"_J, TR("Unlock_Gunrunning")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlockalltradeprices"_J, TR("unlockalltradeprices")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("Unlock_Festive_Gifts"_J, TR("Unlock_Festive_Gifts")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("New_Unlock"_J, TR("New_Unlock")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("unlockfastrun"_J, TR("unlockfastrun")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("all_Collectibles"_J, TR("all_Collectibles")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("Collectibles_Unlocks"_J, TR("Collectibles_Unlocks")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("CompleteWSameCrewheist"_J, TR("CompleteWSameCrewheist")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("enable_jack_o_latern"_J, TR("Enable Jack O' Lantern")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("Lester_services"_J, TR("Lester_services")));
	 generalUnlocks->AddItem(std::make_shared<CommandItem>("mk2_skins"_J, TR("MK2 Gun Skins")));

	skip->AddItem(std::make_shared<CommandItem>("SkipDrDreeContract"_J, TR("SkipDrDreeContract")));
	skip->AddItem(std::make_shared<CommandItem>("SkipJenetteTheMutette"_J, TR("SkipJenetteTheMutette")));
	skip->AddItem(std::make_shared<CommandItem>("SkipCluckinBellRaid"_J, TR("SkipCluckinBellRaid")));
	skip->AddItem(std::make_shared<CommandItem>("SkipOscargunzmanflies"_J, TR("SkipOscargunzmanflies")));
	skip->AddItem(std::make_shared<CommandItem>("Skiptitanjob"_J,TR("Skip titan job setup")));

	trophies->AddItem(std::make_shared<CommandItem>("unlockallmansiontrophies"_J,TR("unlockallmansiontrophies")));

	requestServices->AddItem(std::make_shared<CommandItem>("requestmoc"_J, TR("requestmoc")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestavenger"_J, TR("requestavenger")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestterrorbyte"_J, TR("requestterrorbyte")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestkosatka"_J, TR("requestkosatka")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestacidlab"_J, TR("requestacidlab")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestacidbike"_J, TR("requestacidbike")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestammodrop"_J, TR("requestammodrop")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestbullshark"_J, TR("requestbullshark")));
	requestServices->AddItem(std::make_shared<CommandItem>("requestairstrike"_J, TR("requestairstrike")));

	Unreleased->AddItem(std::make_shared<CommandItem>("Unreleased_content"_J, TR("Unreleased_content")));
	Unreleased->AddItem(std::make_shared<ListCommandItem>("luckyclover_location"_J, TR("luckyclover_location")));
	Unreleased->AddItem(std::make_shared<CommandItem>("teleport_luckyclover"_J, TR("teleport_luckyclover")));

	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_hidden_liveries"_J, TR("enable_hidden_liveries")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_halloween_dlc"_J, TR("enable_halloween_dlc")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_independence_dlc"_J, TR("enable_independence_dlc")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_christmas_dlc"_J, TR("enable_christmas_dlc")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_new_years_gifts"_J, TR("enable_new_years_gifts")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_valentines_day"_J, TR("enable_valentines_day")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_limited_items"_J, TR("enable_limited_items")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_thanksgiving"_J, TR("Enable Thanksgiving")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("TongvaM_Unlock"_J, TR("TongvaM_Unlock")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("RichmanM_Unlock"_J, TR("RichmanM_Unlock")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("VinewoodM_Unlock"_J, TR("VinewoodM_Unlock")));
	Safehouseinhills->AddItem(std::make_shared<CommandItem>("enable_anniversary_dlc"_J,TR("Enable Anniversary DLC")));
    missions->AddItem(std::make_shared<CommandItem>("alien_egg_mission"_J, TR("alien_egg_mission")));
	achievements->AddItem(std::make_shared<CommandItem>("unlock_achievements"_J, TR("unlock_achievements")));

	cooldown->AddItem(std::make_shared<CommandItem>("reset_casino_cd"_J, TR("reset_casino_cd")));
	cooldown->AddItem(std::make_shared<CommandItem>("reset_vehicle_sell_cd"_J, TR("reset_vehicle_sell_cd")));
	cooldown->AddItem(std::make_shared<CommandItem>("Reset_vehicle_Delivery_cd"_J, TR("Reset_vehicle_Delivery_cd")));

	free->AddItem(std::make_shared<CommandItem>("FKarin_S95"_J));

	LSCMGroupe->AddItem(std::make_shared<IntCommandItem>("lscarmeetrank"_J, TR("LS Car Meet Rank")));
	LSCMGroupe->AddItem(std::make_shared<CommandItem>("applylscarmeetrank"_J,TR("Apply ls Car Meet Rank")));
	LSCMGroupe->AddItem(std::make_shared<CommandItem>("Complete_Challenge"_J,TR("Complete_Challenge")));
	LSCMGroupe->AddItem(std::make_shared<CommandItem>("tp_lscm"_J,TR("tp_lscm")));

	ArenaWarGroup->AddItem(std::make_shared<IntCommandItem>("arenawarrank"_J, TR("Arena War Rank")));
	ArenaWarGroup->AddItem(std::make_shared<CommandItem>("applyarenawarrank"_J,TR("Apply Arena War Rank")));

   instantfinish->AddItem(std::make_shared<CommandItem>("InstantFinishTowTruckServiceMission"_J, TR("InstantFinishTowTruckServiceMission")));
   instantfinish->AddItem(std::make_shared<CommandItem>("instantfinishvehiclerobberies"_J, TR("instantfinishvehiclerobberies")));
   instantfinish->AddItem(std::make_shared<CommandItem>("InstantSellBunkerStuff"_J, TR("InstantSellBunkerStuff")));
   instantfinish->AddItem(std::make_shared<CommandItem>("sellandbuyspecialcargo"_J, TR("sellandbuyspecialcargo")));
   instantfinish->AddItem(std::make_shared<CommandItem>("instantaircargosell"_J, TR("instantaircargosell")));
   instantfinish->AddItem(std::make_shared<CommandItem>("mcbusinesssellmissions"_J, TR("MC Business Sell Missions")));
   instantfinish->AddItem(std::make_shared<CommandItem>("setfibfilepayouts"_J,TR("Set FIB File Payouts")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishblackboxprep"_J,TR("Finish Black Box Prep")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishblackboxfinale"_J,TR("Finish Black Box Finale")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishfineartprep"_J,TR("Finish Fine Art Prep")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishfineartfinale"_J,TR("Finish Fine Art Finale")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishbreakawayprep"_J,TR("Finish Breakaway Prep")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishbreakawayfinale"_J,TR("Finish Breakaway Finale")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishbruteforceprep"_J,TR("Finish Brute Force Prep")));
   instantfinish->AddItem(std::make_shared<CommandItem>("finishbruteforcefinale"_J,TR("Finish Brute Force Finale")));


   exhibitGroup->AddItem(std::make_shared<ListCommandItem>("soloexhibittarget"_J, TR("Target")));
   exhibitGroup->AddItem(std::make_shared<BoolCommandItem>("soloexhibitloot"_J,TR("Solo Exhibit Loot")));

   stashHouse->AddItem(std::make_shared<CommandItem>("getstashhousecode"_J,TR("Get Stash House Code")));

	main->AddItem(generalGroup);
	main->AddItem(LSCMGroupe);
	main->AddItem(ArenaWarGroup);
	main->AddItem(gunvanGroup);
	main->AddItem(stashHouse);
	main->AddItem(requestServices);
	main->AddItem(missions);
	main->AddItem(achievements);
	main->AddItem(cooldown);
	main->AddItem(free);

	businesses->AddItem(businessGroup);
	businesses->AddItem(Bailloffice);
	businesses->AddItem(Misc_business);
	businesses->AddItem(over_lay);

	casino->AddItem(casinoSlots);
	casino->AddItem(casinoWheel);
	casino->AddItem(casinoMisc);

	unlocks->AddItem(generalUnlocks);
	unlocks->AddItem(trophies);
	unlocks->AddItem(skip);
	unlocks->AddItem(Unreleased);
	unlocks->AddItem(Safehouseinhills);
	unlocks->AddItem(instantfinish);

	AddCategory(std::move(main));
	AddCategory(std::move(businesses));
	AddCategory(std::move(casino));
	AddCategory(std::move(unlocks));
	AddCategory(BuildStatEditorMenu());
	AddCategory(BuildTransactionsMenu());
	AddCategory(BuildHeistModifierMenu());
	AddCategory(BuildDailyActivitiesMenu());
	}
}