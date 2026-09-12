#include "Network.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/submenus/Network/SavedPlayers.hpp"
#include "game/frontend/submenus/Network/RandomEvents.hpp"
#include "game/gta/Network.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	Network::Network() :
		#define ICON_FA_ROUTE "\xef\x9b\xbf"
	    Submenu::Submenu(TR("Network"), ICON_FA_ROUTE)
	{
		// TODO: this needs a rework
		auto session = std::make_shared<Category>(TR("Session"));
		auto joinGroup = std::make_shared<Group>(TR("Join"));
		auto bountyGroup = std::make_shared<Group>(TR("Bounty"), 1);
		auto toxicGroup = std::make_shared<Group>(TR("Toxic"));
		auto teleportGroup = std::make_shared<Group>(TR("Teleport"));
		auto trollGroup = std::make_shared<Group>(TR("Troll"));
		auto miscGroup = std::make_shared<Group>(TR("Misc"));
		auto enhancements = std::make_shared<Group>(TR("Enhancements"));

		auto joinSession = std::make_shared<Group>("", 1);
		joinSession->AddItem(std::make_shared<ListCommandItem>("joinsessiontype"_J, TR("Session Type")));
		joinSession->AddItem(std::make_shared<CommandItem>("joinsession"_J, TR("Join##session")));

		joinGroup->AddItem(joinSession);
		joinGroup->AddItem(std::make_shared<ImGuiItem>([] {
			static std::uint64_t rockstar_id{};
			static char name_buf[24]{};

			ImGui::SetNextItemWidth(150.0f);
			ImGui::InputText(TR("Username"), name_buf, sizeof(name_buf));
			ImGui::SameLine();
			if (ImGui::Button(TR("Join##username")))
				FiberPool::Push([] {
					auto rid = YimMenu::Network::ResolveRockstarId(name_buf);
					if (rid)
					{
						YimMenu::Network::JoinRockstarId(*rid);
					}
					else
					{
						Notifications::Show("Joiner", "Failed to get RID from username", NotificationType::Error);
					}
				});

			ImGui::SetNextItemWidth(150.0f);
			ImGui::InputScalar("Rockstar Id", ImGuiDataType_U64, &rockstar_id);
			ImGui::SameLine();
			if (ImGui::Button(TR("Join##rid")))
				FiberPool::Push([] {
					YimMenu::Network::JoinRockstarId(rockstar_id);
				});
		}));

		bountyGroup->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, TR("Amount")));
		bountyGroup->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, TR("Anonymous")));
		bountyGroup->AddItem(std::make_shared<CommandItem>("setbountyall"_J, TR("Set Bounties")));

		auto customPlayerTp = std::make_shared<Group>("", 1);
		customPlayerTp->AddItem(std::make_shared<Vector3CommandItem>("playertpcoord"_J, ""));
		customPlayerTp->AddItem(std::make_shared<CommandItem>("tpplayertocoordall"_J, TR("Teleport Everyone")));
		auto tpToProperty = std::make_shared<Group>("", 1);
		tpToProperty->AddItem(std::make_shared<ListCommandItem>("sendtopropertyindex"_J, "##selproperty"));
		tpToProperty->AddItem(std::make_shared<CommandItem>("sendtopropertyall"_J, TR("Send All to Property")));
		auto tpToInterior = std::make_shared<Group>("", 1);
		tpToInterior->AddItem(std::make_shared<ListCommandItem>("sendtointeriorindex"_J, "##selinterior"));
		tpToInterior->AddItem(std::make_shared<CommandItem>("sendtointeriorall"_J, TR("Send All to Interior")));
		teleportGroup->AddItem(tpToProperty);
		teleportGroup->AddItem(tpToInterior);
		teleportGroup->AddItem(std::make_shared<CommandItem>("bringall"_J, TR("Bring All")));
		teleportGroup->AddItem(customPlayerTp);

		trollGroup->AddItem(std::make_shared<CommandItem>("sendsextall"_J, TR("Send Sexts")));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("harassplayers"_J,TR("harassplayers")));
		trollGroup->AddItem(std::make_shared<BoolCommandItem>("spamkillfeed"_J,TR("spamkillfeed")));
		trollGroup->AddItem(std::make_shared<CommandItem>("deletevehall"_J, TR("Delete Player Vehicles")));

		toxicGroup->AddItem(std::make_shared<CommandItem>("killall"_J, TR("Kill All")));
		toxicGroup->AddItem(std::make_shared<CommandItem>("killexploitall"_J, TR("Permadeath All")));
		toxicGroup->AddItem(std::make_shared<CommandItem>("explodeall"_J, TR("Explode All")));
		toxicGroup->AddItem(std::make_shared<CommandItem>("ceokickall"_J, TR("CEO Kick All")));
		toxicGroup->AddItem(std::make_shared<CommandItem>("hkickall"_J, TR("hostkick for all player")));

		miscGroup->AddItem(std::make_shared<BoolCommandItem>("forcethunder"_J,TR("Force Thunder")));

		enhancements->AddItem(std::make_shared<BoolCommandItem>("notifyonplayerjoin"_J,TR("Notify on Player Join")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("fastjoin"_J,TR("Fast Join")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("disabledeathbarriers"_J,TR("Disable Death Barriers")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("despawnbypass"_J,TR("despawnbypass")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("bypasscasinogeoblock"_J,TR("bypasscasinogeoblock")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("forcescripthost"_J,TR("forcescripthost")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("pausegame"_J,TR("pausegame")));
		enhancements->AddItem(std::make_shared<BoolCommandItem>("nocalls"_J,TR("nocalls")));

		session->AddItem(joinGroup);
		session->AddItem(bountyGroup);
		session->AddItem(trollGroup);
		session->AddItem(teleportGroup);
		session->AddItem(toxicGroup);
		session->AddItem(miscGroup);
		session->AddItem(enhancements);

		auto spoofing = std::make_shared<Category>(TR("Spoofing"));
		auto matchmakingGroup = std::make_shared<Group>(TR("Matchmaking (Client)"));
		matchmakingGroup->AddItem(std::make_shared<BoolCommandItem>("cheaterpool"_J,TR("Join YimMenu-only Sessions")));
		auto spoofMMRegion = std::make_shared<Group>("", 1);
		spoofMMRegion->AddItem(std::make_shared<BoolCommandItem>("spoofmmregion"_J, TR("Spoof Region")));
		spoofMMRegion->AddItem(std::make_shared<ConditionalItem>("spoofmmregion"_J, std::make_shared<ListCommandItem>("mmregion"_J, "##mmregion")));
		matchmakingGroup->AddItem(std::make_shared<ConditionalItem>("cheaterpool"_J, spoofMMRegion, true));
		matchmakingGroup->AddItem(std::make_shared<BoolCommandItem>("spoofdatahash"_J,TR("spoofdatahash")));
		spoofing->AddItem(matchmakingGroup);

		auto matchmakingSrvGroup = std::make_shared<Group>(TR("Matchmaking (Server)"));
		auto srvSpoofRegion = std::make_shared<Group>("", 1);
		srvSpoofRegion->AddItem(std::make_shared<BoolCommandItem>("mmspoofregiontype"_J,TR("Spoof Region Type")));
		srvSpoofRegion->AddItem(std::make_shared<ConditionalItem>("mmspoofregiontype"_J, std::make_shared<ListCommandItem>("mmregiontype"_J, "##mmregiontype")));
		auto srvSpoofLanguage = std::make_shared<Group>("", 1);
		srvSpoofLanguage->AddItem(std::make_shared<BoolCommandItem>("mmspooflanguage"_J,TR("Spoof Language")));
		srvSpoofLanguage->AddItem(std::make_shared<ConditionalItem>("mmspooflanguage"_J, std::make_shared<ListCommandItem>("mmlanguage"_J, "##mmlanguage")));
		auto srvSpoofPlayerCount = std::make_shared<Group>("", 1);
		srvSpoofPlayerCount->AddItem(std::make_shared<BoolCommandItem>("mmspoofplayercount"_J,TR("Spoof Player Count")));
		srvSpoofPlayerCount->AddItem(std::make_shared<ConditionalItem>("mmspoofplayercount"_J, std::make_shared<IntCommandItem>("mmplayercount"_J, "##mmplayercount")));
		auto srvMultiplex = std::make_shared<Group>("", 1);
		srvMultiplex->AddItem(std::make_shared<BoolCommandItem>("mmmultiplexsession"_J,TR("Multiplex Session")));
		srvMultiplex->AddItem(std::make_shared<ConditionalItem>("mmmultiplexsession"_J, std::make_shared<IntCommandItem>("mmmultiplexsessioncount"_J, "##mmmultiplexsessioncount")));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofRegion));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofLanguage));
		matchmakingSrvGroup->AddItem(std::move(srvSpoofPlayerCount));
		matchmakingSrvGroup->AddItem(std::move(srvMultiplex));
		spoofing->AddItem(matchmakingSrvGroup);

		AddCategory(std::move(session));
		AddCategory(std::move(spoofing));
		AddCategory(std::move(BuildSavedPlayersMenu()));
		AddCategory(BuildRandomEventsMenu());
	}
}