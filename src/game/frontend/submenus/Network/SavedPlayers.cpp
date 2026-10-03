#include "SavedPlayers.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include "core/frontend/Notifications.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/gta/Network.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	static std::uint64_t g_SelectedRid = 0;
	static SavedPlayerData* g_SelectedPlayer = nullptr;
	static char g_SelectedPlayerName[24]{};
	static char g_NameToSearch[24]{};

	static ImColor GetStatusCircleColor(SavedPlayerData* data)
	{
		if (!data->m_FetchedData)
			return ImGui::Colors::Gray;
		else if (data->m_FetchedData->m_GameState == FetchedPlayerData::GameState::INVALID)
			return ImGui::Colors::Red;
		else if (data->m_FetchedData->m_GameState == FetchedPlayerData::GameState::PUBLIC)
			return ImGui::Colors::Green;
		else
			return ImGui::Colors::Yellow;
	}

	static bool ShouldRenderPlayer(std::string_view name, std::string_view search)
	{
		if (search.empty())
			return true;

		if (name.size() < search.size())
			return false;

		// TODO: this doesn't do what YimMenuV1 did (which is to lowercase both inputs and perform a substring search)
		for (int i = 0; i < search.size(); i++)
			if (tolower(name[i]) != tolower(search[i]))
				return false;

		return true;
	}

	static void RenderPlayerItem(std::uint64_t rid, SavedPlayerData* data)
	{
		ImGui::PushID(rid);

		constexpr float circle_size = 7.5f;
		auto cursor_pos = ImGui::GetCursorScreenPos();

		// render status circle
		ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(cursor_pos.x + 4.f + circle_size, cursor_pos.y + 4.f + circle_size), circle_size, GetStatusCircleColor(data));

		// we need some padding
		ImVec2 cursor = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(cursor.x + 25.f, cursor.y));

		if (ImGui::Selectable(data->m_Name.data(), rid == g_SelectedRid))
		{
			g_SelectedRid = rid;
			g_SelectedPlayer = data;
			strncpy(g_SelectedPlayerName, data->m_Name.data(), sizeof(g_SelectedPlayerName));
		}

		if (data->m_FetchedData && ImGui::IsItemHovered())
			ImGui::SetTooltip("%s", FetchedPlayerData::GameStateToString(data->m_FetchedData->m_GameState).data());

		ImGui::PopID();
	}

	static void RenderPlayerList()
	{
		ImGui::SetNextItemWidth(200.f);
		ImGui::InputTextWithHint(TR("Search"), TR("Search"), g_NameToSearch, sizeof(g_NameToSearch));

		if (ImGui::BeginListBox("###player-list", {180, -100 /* static_cast<float>(*Pointers.ScreenResY - 700 - 38 * 4) */}))
		{
			auto& players = SavedPlayers::GetSavedPlayers();

			if (players.size() == 0)
			{
				ImGui::TextDisabled(TR("No saved players"));
				ImGui::EndListBox();
				return;
			}

			// TODO: surely there must be a better way to do this

			for (auto& [rid, data] : players)
				if (data.m_FetchedData && data.m_FetchedData->m_GameState == FetchedPlayerData::GameState::PUBLIC && ShouldRenderPlayer(data.m_Name, g_NameToSearch))
					RenderPlayerItem(rid, &data);

			for (auto& [rid, data] : players)
				if (data.m_FetchedData && data.m_FetchedData->m_GameState != FetchedPlayerData::GameState::PUBLIC
				    && data.m_FetchedData->m_GameState != FetchedPlayerData::GameState::INVALID && ShouldRenderPlayer(data.m_Name, g_NameToSearch))
					RenderPlayerItem(rid, &data);

			for (auto& [rid, data] : players)
				if ((!data.m_FetchedData || (data.m_FetchedData->m_GameState == FetchedPlayerData::GameState::INVALID)) && ShouldRenderPlayer(data.m_Name, g_NameToSearch))
					RenderPlayerItem(rid, &data);


			ImGui::EndListBox();
		}
	}

	static void RenderPlayerEditor()
	{
		if (!g_SelectedPlayer || g_SelectedRid == 0)
			return;

		if (ImGui::BeginChild("##player-editor", {500, -100 /* static_cast<float>(*Pointers.ScreenResY - 688 - 38 * 4) */}, 0, ImGuiWindowFlags_NoBackground))
		{
			ImGui::SetNextItemWidth(180.f);
			if (ImGui::InputText("Name", g_SelectedPlayerName, sizeof(g_SelectedPlayerName)))
			{
				g_SelectedPlayer->m_Name = g_SelectedPlayerName;
			}

			int old_rid = g_SelectedRid;
			ImGui::SetNextItemWidth(180.0f);
			if (ImGui::InputScalar("Rockstar Id", ImGuiDataType_U64, &g_SelectedRid))
			{
				SavedPlayers::UpdateRockstarId(old_rid, g_SelectedRid);
				g_SelectedPlayer = SavedPlayers::GetPlayerData(g_SelectedRid);
			}

			ImGui::Checkbox("Track Player", &g_SelectedPlayer->m_TrackPlayer);

			if (g_SelectedPlayer->m_FetchedData)
			{
				auto& data = *g_SelectedPlayer->m_FetchedData;
				ImGui::Text("Session Type: %s", FetchedPlayerData::GameStateToString(data.m_GameState).data());
				ImGui::Text("Host of Session: %s", data.m_HostOfSession ? "Yes" : "No");
				ImGui::Text("Is Spectating: %s", data.m_Spectating ? "Yes" : "No");
				ImGui::Text("Is Job Lobby: %s", data.m_InTransition ? "Yes" : "No");
				ImGui::Text("Host of Job Lobby: %s", data.m_HostOfTransition ? "Yes" : "No");
				if (data.m_MissionType != FetchedPlayerData::MissionType::NONE)
				{
					ImGui::Text("Mission Type: %s", FetchedPlayerData::MissionTypeToString(data.m_MissionType).data());
					if (data.m_MissionName)
						ImGui::Text("Mission Name: %s", data.m_MissionName->data());
					else
						; // TODO: add fetch mission name
				}
			}
			else
			{
				ImGui::TextDisabled("Data not fetched yet");
			}

			if (ImGui::Button(TR("Join")))
			{
				FiberPool::Push([] {
					Network::JoinRockstarId(g_SelectedRid);
				});
			}

			if (ImGui::Button(TR("Save")))
			{
				SavedPlayers::Save();
			}
			ImGui::SameLine();
			if (ImGui::Button(TR("Remove")))
			{
				SavedPlayers::RemovePlayerData(g_SelectedRid);
				g_SelectedPlayer = nullptr;
				g_SelectedRid = 0;
			}
		}
		ImGui::EndChild();
	}

	static void RenderSavedPlayers()
	{
		RenderPlayerList();
		ImGui::SameLine();
		RenderPlayerEditor();
	}

	static void RenderAddNewPlayer()
	{
		static char name_buf[24]{};

		ImGui::SetNextItemWidth(180.0f);
		ImGui::InputText(TR("Username"), name_buf, sizeof(name_buf));
		ImGui::SameLine();
		if (ImGui::Button(TR("Add")))
			FiberPool::Push([] {
				auto rid = YimMenu::Network::ResolveRockstarId(name_buf);
				if (rid)
				{
					SavedPlayers::AddPlayerData(*rid, name_buf);
				}
				else
				{
					Notifications::Show("Saved Players", "Failed to get RID from username", NotificationType::Error);
				}
			});
	}

	std::shared_ptr<Category> BuildSavedPlayersMenu()
	{
		auto menu = std::make_shared<Category>(TR("Saved Players"));
		auto players = std::make_shared<Group>(TR("Players"));
		auto new_player = std::make_shared<Group>(TR("New"));
		auto tracking = std::make_shared<Group>(TR("Tracking"));
		auto notifications = std::make_shared<Group>(TR("Notifications"));

		players->AddItem(std::make_shared<ImGuiItem>([] {
			RenderSavedPlayers();
		}));

		new_player->AddItem(std::make_shared<ImGuiItem>([] {
			RenderAddNewPlayer();
		}));

		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifywhenjoinable"_J,TR("Notify When Joinable")));
		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifywhenunjoinable"_J,TR("Notify When Unjoinable")));
		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifywhenonline"_J,TR("Notify When Online")));
		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifywhenoffline"_J,TR("Notify When Offine")));
		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifyonseschange"_J,TR("Notify On Session Type Change")));
		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifyonmischange"_J,TR("Notify On Mission Change")));
		notifications->AddItem(std::make_shared<BoolCommandItem>("playerdbnotifyonjoblobby"_J,TR("Notify On Job Lobby Change")));

		auto update = std::make_shared<Group>("", 1);
		update->AddItem(std::make_shared<BoolCommandItem>("playerdbautoupdate"_J, TR("Auto Update")));
		update->AddItem(std::make_shared<CommandItem>("playerdbupdatenow"_J, TR("Update Now")));

		tracking->AddItem(std::move(update));
		tracking->AddItem(std::make_shared<BoolCommandItem>("playerdbnotify"_J, TR("Tracking Notifications")));
		tracking->AddItem(std::make_shared<ConditionalItem>("playerdbnotify"_J, std::move(notifications)));

		menu->AddItem(players);
		menu->AddItem(new_player);
		menu->AddItem(tracking);

		return menu;
	}
}