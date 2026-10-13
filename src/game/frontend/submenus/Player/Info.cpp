#include "Info.hpp"

#include "core/frontend/Notifications.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "types/network/rlGamerInfo.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	static std::string BuildIPStr(int field1, int field2, int field3, int field4)
	{
		std::ostringstream oss;
		oss << field1 << '.' << field2 << '.' << field3 << '.' << field4;
		return oss.str();
	}

	std::shared_ptr<Category> BuildInfoMenu()
	{
		auto menu = std::make_shared<Category>(TR("Info"));

		auto teleportGroup = std::make_shared<Group>(TR("Teleport"));
		auto playerOptionsGroup = std::make_shared<Group>(TR("Info"));

		playerOptionsGroup->AddItem(std::make_shared<ImGuiItem>([] {
			if (Players::GetSelected().IsValid())
				ImGui::Text("%s", Players::GetSelected().GetName());
		}));
		playerOptionsGroup->AddItem(std::make_shared<BoolCommandItem>("spectate"_J,TR("Spectate")));
		playerOptionsGroup->AddItem(std::make_shared<ImGuiItem>([] {
			if (Players::GetSelected().IsValid())
			{
				ImGui::Text(TR("Rank: %d (%d RP)"), Players::GetSelected().GetRank(), Players::GetSelected().GetRP());
				ImGui::Text(TR("Money: %d"), Players::GetSelected().GetMoney());

				if (Players::GetSelected().GetPed())
				{
					auto health = Players::GetSelected().GetPed().GetHealth();
					auto maxHealth = Players::GetSelected().GetPed().GetMaxHealth();
					
					//std::string healthStr = std::format(TR("HP: {}/{} ({:.2f}%)", health, maxHealth, (float)health / maxHealth * 100.0f));
					std::string healthStr = TR("HP:") + std::to_string(health) + "/" + std::to_string(maxHealth) + " (" + std::to_string(static_cast<float>(health) / maxHealth * 100.0f).substr(0, 4) + "%)";
					ImGui::Text("%s", healthStr.c_str());

					auto coords = Players::GetSelected().GetPed().GetPosition();
					ImGui::Text(TR("Coords: %.2f, %.2f, %.2f"), coords.x, coords.y, coords.z);

					auto distance = Players::GetSelected().GetPed().GetPosition().GetDistance(Self::GetPed().GetPosition());
					ImGui::Text(TR("Distance: %.2f"), distance);
				}
				else
				{
					ImGui::Text(TR("Ped missing or deleted"));
				}

				auto rid1 = Players::GetSelected().GetRID();

				std::string ridStr = std::to_string(rid1);

				ImGui::Text("RID:");
				ImGui::SameLine();
				if (ImGui::SmallButton(std::to_string(rid1).c_str()))
				{
					ImGui::SetClipboardText(std::to_string(rid1).c_str());
				}

				auto& platformAccountId = Players::GetSelected().GetHandle()->m_PlatformAccountId;
				switch (platformAccountId.m_Platform)
				{
				case PlatformAccountId::PLATFORM_XBOX:
					ImGui::Text("Xbox User ID:");
					ImGui::SameLine();
					if (ImGui::SmallButton(std::to_string(platformAccountId.m_XboxUserId).c_str()))
					{
						ImGui::SetClipboardText(std::to_string(platformAccountId.m_XboxUserId).c_str());
					}
					break;
				case PlatformAccountId::PLATFORM_STEAM:
					ImGui::Text("Steam ID:");
					ImGui::SameLine();
					if (ImGui::SmallButton(std::to_string(platformAccountId.m_SteamId).c_str()))
					{
						ImGui::SetClipboardText(std::to_string(platformAccountId.m_SteamId).c_str());
					}
					break;
				case PlatformAccountId::PLATFORM_EPIC:
					ImGui::Text("Epic Account ID:");
					ImGui::SameLine();
					if (ImGui::SmallButton(platformAccountId.m_EpicAccountId))
					{
						ImGui::SetClipboardText(platformAccountId.m_EpicAccountId);
					}
					break;
				default:
					break;
				}


				auto ip = Players::GetSelected().GetExternalAddress();

				auto& playerData = Players::GetSelected().GetData();
				if (playerData.m_HasAddresses)
				{
					ip = playerData.m_ExternalAddress;
				}

				auto addr2 = BuildIPStr(ip.m_IpAddress.m_Field1, ip.m_IpAddress.m_Field2, ip.m_IpAddress.m_Field3, ip.m_IpAddress.m_Field4);

				ImGui::Text(TR("IP Address:"));
				ImGui::SameLine();
				if (ImGui::SmallButton(addr2.c_str()))
				{
					ImGui::SetClipboardText(addr2.c_str());
				}

				if (ImGui::Button(TR("Add to Saved")))
					SavedPlayers::GetPlayerData(Players::GetSelected());
				ImGui::SameLine();
				if (ImGui::Button(TR("View SC Profile")))
					FiberPool::Push([] {
						uint64_t handle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(Players::GetSelected().GetId(), handle, std::size(handle));
						NETWORK::NETWORK_SHOW_PROFILE_UI(handle);
					});
				ImGui::SameLine();
				if (ImGui::Button(TR("Add Friend")))
					FiberPool::Push([] {
						uint64_t handle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(Players::GetSelected().GetId(), handle, std::size(handle));
						NETWORK::NETWORK_ADD_FRIEND(handle, "");
					});

				if (ImGui::Button(TR("More Info")))
					ImGui::OpenPopup("More Info");

				ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
				if (ImGui::BeginPopupModal("More Info", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_Modal | ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(TR("Average Latency: %.2f"), Players::GetSelected().GetAverageLatency());
					ImGui::Text(TR("Packet Loss: %.2f"), Players::GetSelected().GetAveragePacketLoss());

					ImGui::Spacing();

					if (ImGui::Button(TR("Close")) || ((!ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}
			}
			else
			{
				Players::SetSelected(Self::GetPlayer());
				ImGui::Text(TR("No players yet!"));
			}
		}));

		menu->AddItem(playerOptionsGroup);

		
		auto customPlayerTp = std::make_shared<Group>("", 1);
		customPlayerTp->AddItem(std::make_shared<Vector3CommandItem>("playertpcoord"_J, ""));
		customPlayerTp->AddItem(std::make_shared<PlayerCommandItem>("tpplayertocoord"_J, TR("Teleport")));
		auto tpToProperty = std::make_shared<Group>("", 1);
		tpToProperty->AddItem(std::make_shared<ListCommandItem>("sendtopropertyindex"_J, "##selproperty"));
		tpToProperty->AddItem(std::make_shared<PlayerCommandItem>("sendtoproperty"_J,TR("Send to Property")));
		auto tpToInterior = std::make_shared<Group>("", 1);
		tpToInterior->AddItem(std::make_shared<ListCommandItem>("sendtointeriorindex"_J, "##selinterior"));
		tpToInterior->AddItem(std::make_shared<PlayerCommandItem>("sendtointerior"_J,TR("Send to Interior")));
		teleportGroup->AddItem(tpToProperty);
		teleportGroup->AddItem(tpToInterior);
		teleportGroup->AddItem(std::make_shared<PlayerCommandItem>("tptoplayer"_J, TR("Teleport To")));
		teleportGroup->AddItem(std::make_shared<PlayerCommandItem>("bring"_J,TR("Bring")));
		teleportGroup->AddItem(customPlayerTp);

		menu->AddItem(teleportGroup);

		return menu;
	}
}