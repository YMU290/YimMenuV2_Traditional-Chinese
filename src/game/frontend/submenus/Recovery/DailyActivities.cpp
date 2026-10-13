#include "DailyActivities.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildDailyActivitiesMenu()
	{
		auto dailyActivities = std::make_shared<Category>(TR("Daily Activities"));

		auto challengesTab       = std::make_shared<CollapsingHeaderItem>(TR("Challenges"));
		auto hiddenCacheTab      = std::make_shared<CollapsingHeaderItem>(TR("Hidden Caches"));
		auto treasureChestTab    = std::make_shared<CollapsingHeaderItem>(TR("Treasure Chests"));
		auto shipwreckedTab      = std::make_shared<CollapsingHeaderItem>(TR("Shipwreck"));
		auto buriedStashTab      = std::make_shared<CollapsingHeaderItem>(TR("Buried Stashes"));
		auto skydiveTab          = std::make_shared<CollapsingHeaderItem>(TR("Junk Energy Skydives"));
		auto timeTrialsTab       = std::make_shared<CollapsingHeaderItem>(TR("Time Trials"));
		auto exoticExportsTab    = std::make_shared<CollapsingHeaderItem>(TR("Exotic Exports"));
		auto deadDropTab         = std::make_shared<CollapsingHeaderItem>(TR("G's Cache"));
		auto stashHouseTab       = std::make_shared<CollapsingHeaderItem>(TR("Stash House"));
		auto streetDealerTab     = std::make_shared<CollapsingHeaderItem>(TR("Street Dealers"));
		auto lsTagsTab           = std::make_shared<CollapsingHeaderItem>(TR("LS Tags"));
		auto madrazoHitsTab      = std::make_shared<CollapsingHeaderItem>(TR("Madrazo Hits"));
		auto wildlifePhotography = std::make_shared<CollapsingHeaderItem>(TR("Shoot Animals Photography"));
		auto smokeOnTheWater     = std::make_shared<CollapsingHeaderItem>(TR("Smoke on the Water"));
		auto goldenClover        = std::make_shared<CollapsingHeaderItem>(TR("Golden Clover"));

		dailyActivities->AddItem(std::make_shared<CommandItem>("setallactivitiescompleted"_J,TR("Set All Activities Completed")));
		dailyActivities->AddItem(std::make_shared<CommandItem>("resetallactivities"_J,TR("Reset All Activities")));

		challengesTab->AddItem(std::make_shared<CommandItem>("completeallchallenges"_J,TR("Complete All Challenges")));

		hiddenCacheTab->AddItem(std::make_shared<ListCommandItem>("hiddencacheindex"_J,TR("Hidden Cache")));
		hiddenCacheTab->AddItem(std::make_shared<CommandItem>("tptohiddencache"_J,TR("Teleport to Hidden Cache")));
		hiddenCacheTab->AddItem(std::make_shared<CommandItem>("collecthiddencache"_J,TR("Collect Hidden Cache")));

		treasureChestTab->AddItem(std::make_shared<ListCommandItem>("treasurechestindex"_J,TR("Treasure Chest")));
		treasureChestTab->AddItem(std::make_shared<CommandItem>("tptotreasurechest"_J,TR("Teleport to Treasure Chest")));
		treasureChestTab->AddItem(std::make_shared<CommandItem>("collecttreasurechest"_J,TR("Collect Treasure Chest")));
		treasureChestTab->AddItem(std::make_shared<BoolCommandItem>("enabletreasurechestinls"_J,TR("Enable Treasure Chests in LS")));

		shipwreckedTab->AddItem(std::make_shared<CommandItem>("tptoshipwrecked"_J,TR("Teleport to Shipwreck")));
		shipwreckedTab->AddItem(std::make_shared<CommandItem>("collectshipwrecked"_J,TR("Collect Shipwreck")));

		buriedStashTab->AddItem(std::make_shared<ListCommandItem>("buriedstashindex"_J,TR("Buried Stash")));
		buriedStashTab->AddItem(std::make_shared<CommandItem>("tptoburiedstash"_J,TR("Teleport to Buried Stash")));
		buriedStashTab->AddItem(std::make_shared<CommandItem>("collectburiedstash"_J,TR("Collect Buried Stash")));
		buriedStashTab->AddItem(std::make_shared<BoolCommandItem>("enableburiedstashinls"_J,TR("Enable Buried Stashes in LS")));

		skydiveTab->AddItem(std::make_shared<ListCommandItem>("skydiveindex"_J,TR("Skydive")));
		skydiveTab->AddItem(std::make_shared<CommandItem>("tptoskydive"_J,TR("Teleport to Skydive")));
		skydiveTab->AddItem(std::make_shared<CommandItem>("completeskydive"_J,TR("Complete Skydive")));

		// TO-DO: Add HSW Time Trial
		timeTrialsTab->AddItem(std::make_shared<ListCommandItem>("timetrialindex"_J,TR("Time Trial")));
		timeTrialsTab->AddItem(std::make_shared<CommandItem>("tptotimetrial"_J,TR("Teleport to Time Trial")));
		timeTrialsTab->AddItem(std::make_shared<CommandItem>("beattimetrial"_J,TR("Beat Time Trial")));

		exoticExportsTab->AddItem(std::make_shared<CommandItem>("tptoexoticexportsvehicle"_J,TR("Teleport to Exotic Exports Vehicle")));
		exoticExportsTab->AddItem(std::make_shared<CommandItem>("delivernextexoticexportsvehicle"_J,TR("Deliver Next Exotic Exports Vehicle")));

		deadDropTab->AddItem(std::make_shared<CommandItem>("tptodeaddrop"_J,TR("Teleport to G's Cache")));
		deadDropTab->AddItem(std::make_shared<CommandItem>("collectdeaddrop"_J,TR("Collect G's Cache")));

		stashHouseTab->AddItem(std::make_shared<CommandItem>("tptostashhouse"_J,TR("Teleport to Stash House")));
		stashHouseTab->AddItem(std::make_shared<CommandItem>("enterstashhousesafecode"_J,TR("Enter Stash House Safe Code")));

		streetDealerTab->AddItem(std::make_shared<ListCommandItem>("streetdealerindex"_J,TR("Street Dealer")));
		streetDealerTab->AddItem(std::make_shared<CommandItem>("tptostreetdealer"_J,TR("Teleport to Dealer")));
		streetDealerTab->AddItem(std::make_shared<CommandItem>("openstreetdealermenu"_J,TR("Open Street Dealer Menu")));

		lsTagsTab->AddItem(std::make_shared<ListCommandItem>("lstagindex"_J,TR("LS Tag")));
		lsTagsTab->AddItem(std::make_shared<CommandItem>("tptolstag"_J,TR("Teleport to LS Tag")));
		lsTagsTab->AddItem(std::make_shared<CommandItem>("spraylstag"_J,TR("Spray LS Tag")));

		madrazoHitsTab->AddItem(std::make_shared<CommandItem>("tptomadrazohit"_J,TR("Teleport to Madrazo Hit")));
		madrazoHitsTab->AddItem(std::make_shared<CommandItem>("tptomadrazohittarget"_J,TR("Teleport to Madrazo Hit Target")));

		wildlifePhotography->AddItem(std::make_shared<ListCommandItem>("animalindex"_J,TR("Animal")));
		wildlifePhotography->AddItem(std::make_shared<CommandItem>("spawnanimal"_J,TR("Spawn Animal")));
		wildlifePhotography->AddItem(std::make_shared<CommandItem>("photographanimal"_J,TR("Photograph Animal")));

		smokeOnTheWater->AddItem(std::make_shared<ListCommandItem>("productindex"_J,TR("Product")));
		smokeOnTheWater->AddItem(std::make_shared<CommandItem>("tptoproduct"_J,TR("Teleport to Product")));
		smokeOnTheWater->AddItem(std::make_shared<CommandItem>("collectproduct"_J,TR("Collect Product")));

		goldenClover->AddItem(std::make_shared<CommandItem>("tptogoldenclover"_J,TR("Teleport to Golden Clover")));
		goldenClover->AddItem(std::make_shared<CommandItem>("collectgoldenclover"_J,TR("Collect Golden Clover")));

		dailyActivities->AddItem(std::move(challengesTab));
		dailyActivities->AddItem(std::move(hiddenCacheTab));
		dailyActivities->AddItem(std::move(treasureChestTab));
		dailyActivities->AddItem(std::move(shipwreckedTab));
		dailyActivities->AddItem(std::move(buriedStashTab));
		dailyActivities->AddItem(std::move(skydiveTab));
		dailyActivities->AddItem(std::move(timeTrialsTab));
		dailyActivities->AddItem(std::move(exoticExportsTab));
		dailyActivities->AddItem(std::move(deadDropTab));
		dailyActivities->AddItem(std::move(stashHouseTab));
		dailyActivities->AddItem(std::move(streetDealerTab));
		dailyActivities->AddItem(std::move(lsTagsTab));
		dailyActivities->AddItem(std::move(madrazoHitsTab));
		dailyActivities->AddItem(std::move(wildlifePhotography));
		dailyActivities->AddItem(std::move(smokeOnTheWater));
		dailyActivities->AddItem(std::move(goldenClover));
		return dailyActivities;
	}
}