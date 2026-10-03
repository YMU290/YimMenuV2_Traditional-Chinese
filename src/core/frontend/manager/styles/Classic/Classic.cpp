#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/localization/Translator.hpp"
namespace YimMenu
{
	static BoolCommand menuFireworks{"menubgfireworks",TR("Menu Fireworks Background"),TR("Toggle 4th of July fireworks in the menu background")};

		struct FireworkSpark
	{
		ImVec2 pos;
		ImVec2 vel;
		ImU32 color;
		float life;
		float maxLife;
		float size;
	};

	struct Rocket
	{
		ImVec2 pos;
		ImVec2 vel;
		float targetY;
		bool exploded;
	};

	static std::vector<Rocket> g_Rockets{};
	static std::vector<FireworkSpark> g_Sparks{};
	static bool g_FireworksInit = false;
	static float g_SpawnTimer = 0.0f;
	static ImU32 RandomPatrioticColor()
	{
		int choice = rand() % 3;
		switch (choice)
		{
		case 0: return IM_COL32(237, 41, 57, 255);   // red
		case 1: return IM_COL32(255, 255, 255, 255); // white
		default: return IM_COL32(60, 100, 246, 255); // blue
		}
	}

	static float RandRange(float lo, float hi)
	{
		return lo + (hi - lo) * ((float)rand() / (float)RAND_MAX);
	}

	static void SpawnRocket(ImVec2 winPos, ImVec2 winSize)
	{
		Rocket r{};
		r.pos = ImVec2(winPos.x + RandRange(winSize.x * 0.1f, winSize.x * 0.9f), winPos.y + winSize.y);
		r.vel = ImVec2(RandRange(-15.0f, 15.0f), RandRange(-260.0f, -180.0f));
		r.targetY = winPos.y + RandRange(winSize.y * 0.15f, winSize.y * 0.55f);
		r.exploded = false;
		g_Rockets.push_back(r);
	}

	static void Explode(ImVec2 pos)
	{
		int count = 40 + rand() % 25;
		ImU32 burstColor = RandomPatrioticColor();
		bool mixed = (rand() % 100) < 50; // some bursts mix colors, some are single-color
		for (int i = 0; i < count; ++i)
		{
			float angle = RandRange(0.0f, 2.0f * 3.14159265f);
			float speed = RandRange(60.0f, 220.0f);
			FireworkSpark s{};
			s.pos = pos;
			s.vel = ImVec2(cosf(angle) * speed, sinf(angle) * speed);
			s.color = mixed ? RandomPatrioticColor() : burstColor;
			s.maxLife = RandRange(0.8f, 1.6f);
			s.life = s.maxLife;
			s.size = RandRange(1.5f, 3.0f);
			g_Sparks.push_back(s);
		}
	}

	static void InitFireworks()
	{
		static bool seeded = false;
		if (!seeded)
		{
			srand((unsigned)time(nullptr));
			seeded = true;
		}
		g_Rockets.clear();
		g_Sparks.clear();
		g_SpawnTimer = 0.0f;
		g_FireworksInit = true;
	}

	static void RenderFireworksInWindow(ImVec2 winPos, ImVec2 winSize)
	{
		if (!menuFireworks.GetState() || !UIManager::ShowingContentWindow())
		{
			g_Rockets.clear();
			g_Sparks.clear();
			g_FireworksInit = false;
			return;
		}

		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* draw = ImGui::GetWindowDrawList();

		if (!g_FireworksInit)
			InitFireworks();

		ImVec2 clipMin = winPos;
		ImVec2 clipMax = winPos + winSize;
		draw->PushClipRect(clipMin, clipMax, true);

		// Spawn new rockets periodically
		g_SpawnTimer -= io.DeltaTime;
		if (g_SpawnTimer <= 0.0f)
		{
			SpawnRocket(winPos, winSize);
			g_SpawnTimer = RandRange(0.5f, 1.1f);
		}

		const float gravity = 140.0f;

		for (size_t i = 0; i < g_Rockets.size();)
		{
			Rocket& r = g_Rockets[i];
			r.pos.x += r.vel.x * io.DeltaTime;
			r.pos.y += r.vel.y * io.DeltaTime;
			r.vel.y += gravity * 0.35f * io.DeltaTime;

			draw->AddCircleFilled(r.pos, 2.0f, IM_COL32(255, 235, 180, 220));
			draw->AddLine(r.pos, ImVec2(r.pos.x - r.vel.x * 0.03f, r.pos.y - r.vel.y * 0.03f), IM_COL32(255, 200, 120, 120), 1.5f);

			if (r.pos.y <= r.targetY || r.vel.y >= 0.0f)
			{
				Explode(r.pos);
				g_Rockets.erase(g_Rockets.begin() + i);
				continue;
			}
			++i;
		}

		// Update + draw exploded sparks
		for (size_t i = 0; i < g_Sparks.size();)
		{
			FireworkSpark& s = g_Sparks[i];
			s.life -= io.DeltaTime;
			if (s.life <= 0.0f)
			{
				g_Sparks.erase(g_Sparks.begin() + i);
				continue;
			}

			s.vel.y += gravity * io.DeltaTime;
			s.vel.x *= (1.0f - 0.6f * io.DeltaTime);
			s.pos.x += s.vel.x * io.DeltaTime;
			s.pos.y += s.vel.y * io.DeltaTime;

			float t = s.life / s.maxLife; // 1 -> 0
			int alpha = (int)(t * 255.0f);
			ImU32 base = s.color;
			ImU32 faded = (base & 0x00FFFFFF) | ((ImU32)alpha << 24);

			if (s.pos.x >= clipMin.x && s.pos.x <= clipMax.x && s.pos.y >= clipMin.y && s.pos.y <= clipMax.y)
			{
				// soft glow
				ImU32 glow = (base & 0x00FFFFFF) | ((ImU32)(alpha / 4) << 24);
				draw->AddCircleFilled(s.pos, s.size + 2.0f, glow);
				draw->AddCircleFilled(s.pos, s.size, faded);
			}

			++i;
		}

		draw->PopClipRect();
	}

	static float LerpFloat(float a, float b, float t)
	{
		if (t < 0.f)
			t = 0.f;
		if (t > 1.f)
			t = 1.f;
		return a + (b - a) * t;
	}
	static float g_MenuAlpha = 0.0f;
	static float g_MenuSlide = 30.0f;
	static float g_ContentSlide = 0.0f;
	static decltype(UIManager::GetActiveSubmenu()) g_LastSubmenu{};
	void RenderClassicTheme()
	{
		ImGuiIO& io = ImGui::GetIO();
		float windowWidth = *Pointers.ScreenResX / 2.5f;
		float centerX = (*Pointers.ScreenResX - windowWidth) * 0.5f;
		float centerY = *Pointers.ScreenResY / 5.0f;
		ImVec2 windowSize(windowWidth, *Pointers.ScreenResY / 2.5f);
		const float animSpeed = 10.0f;
		float t = io.DeltaTime * animSpeed;
		g_MenuAlpha = LerpFloat(g_MenuAlpha, 1.0f, t);
		g_MenuSlide = LerpFloat(g_MenuSlide, 0.0f, t);
		ImGui::SetNextWindowBgAlpha(g_MenuAlpha);
		ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(centerX, centerY + g_MenuSlide), ImGuiCond_FirstUseEver);
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
		if (!ImGui::Begin("##ClassicInputWindow", nullptr, flags))
		{
			ImGui::End();
			return;
		}
		ImVec2 winPos = ImGui::GetWindowPos();
		ImVec2 winSize = ImGui::GetWindowSize();
		RenderFireworksInWindow(winPos, winSize);
		if (ImGui::BeginChild("##submenus", ImVec2(120, ImGui::GetContentRegionAvail().y), true))
		{
			const auto& submenus = UIManager::GetSubmenus();
			auto activeSubmenu = UIManager::GetActiveSubmenu();
			for (auto& submenu : submenus)
			{
				if (ImGui::Selectable(submenu->m_Name.data(), submenu == activeSubmenu))
				{
					UIManager::SetActiveSubmenu(submenu);
					UIManager::SetShowContentWindow(true);
				}
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::TextUnformatted("YimMenuV2");
		if (ImGui::BeginChild("##minisubmenus", ImVec2(0, 50), true))
		{
			auto activeSubmenu = UIManager::GetActiveSubmenu();
			if (activeSubmenu)
				activeSubmenu->DrawCategorySelectors();
		}
		ImGui::EndChild();

		auto activeSubmenu = UIManager::GetActiveSubmenu();
		if (activeSubmenu != g_LastSubmenu)
		{
			g_ContentSlide = 20.0f;
			g_LastSubmenu = activeSubmenu;
		}
		g_ContentSlide = LerpFloat(g_ContentSlide, 0.0f, t);
		ImGui::Dummy(ImVec2(g_ContentSlide, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		if (ImGui::BeginChild("##options", ImVec2(0, 0), true))
		{
			if (ImFont* optionsFont = UIManager::GetOptionsFont())
				ImGui::PushFont(optionsFont);

			if (activeSubmenu)
				activeSubmenu->Draw();

			if (ImGui::GetFont() != ImGui::GetIO().FontDefault)
				ImGui::PopFont();
		}
		ImGui::EndChild();
		ImGui::EndGroup();
		ImGui::End();
	}
}

/*Restore Monday*/
/*#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/commands/BoolCommand.hpp"
namespace YimMenu
{
	static BoolCommand menuSnow{"menubgsnow","Menu Snow Background","Toggle snow particles in the menu background"};
	struct SnowParticle
	{
		ImVec2 pos;
		float speed;
		float size;
	};
	static std::vector<SnowParticle> g_Snow{};
	static bool g_SnowInit = false;
	static void InitSnow(int count, ImVec2 winPos, ImVec2 winSize)
	{
		static bool seeded = false;
		if (!seeded)
		{
			srand((unsigned)time(nullptr));
			seeded = true;
		}
		g_Snow.clear();
		g_Snow.reserve(count);
		for (int i = 0; i < count; ++i)
		{
			g_Snow.push_back({ImVec2(winPos.x + (float)(rand() % (int)winSize.x),winPos.y + (float)(rand() % (int)winSize.y)),
			    20.0f + (rand() % 40),
			    1.5f + (rand() % 3)});
		}
		g_SnowInit = true;
	}
	static void RenderSnowInWindow(ImVec2 winPos, ImVec2 winSize)
	{
		if (!menuSnow.GetState() || !UIManager::ShowingContentWindow())
		{
			g_Snow.clear();
			g_SnowInit = false;
			return;
		}
		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* draw = ImGui::GetWindowDrawList();
		if (!g_SnowInit)
			InitSnow(120, winPos, winSize);
		ImVec2 clipMin = winPos;
		ImVec2 clipMax = winPos + winSize;
		draw->PushClipRect(clipMin, clipMax, true);
		for (auto& p : g_Snow)
		{
			p.pos.y += p.speed * io.DeltaTime;

			if (p.pos.y > clipMax.y)
			{
				p.pos.y = clipMin.y - 5.0f;
				p.pos.x = clipMin.x + (float)(rand() % (int)winSize.x);
			}
			if (p.pos.x < clipMin.x || p.pos.x > clipMax.x)
				continue;
			//Soft
			draw->AddCircleFilled(
			    p.pos,
			    p.size + 1.5f,
			    IM_COL32(255, 255, 255, 40));

			draw->AddCircleFilled(
			    p.pos,
			    p.size,
			    IM_COL32(255, 255, 255, 120));
		}
		draw->PopClipRect();
	}
	static float LerpFloat(float a, float b, float t)
	{
		if (t < 0.f)
			t = 0.f;
		if (t > 1.f)
			t = 1.f;
		return a + (b - a) * t;
	}
	static float g_MenuAlpha = 0.0f;
	static float g_MenuSlide = 30.0f;
	static float g_ContentSlide = 0.0f;
	static decltype(UIManager::GetActiveSubmenu()) g_LastSubmenu{};
	void RenderClassicTheme()
	{
		ImGuiIO& io = ImGui::GetIO();
		float windowWidth = *Pointers.ScreenResX / 2.5f;
		float centerX = (*Pointers.ScreenResX - windowWidth) * 0.5f;
		float centerY = *Pointers.ScreenResY / 5.0f;
		ImVec2 windowSize(windowWidth,*Pointers.ScreenResY / 2.5f);
		const float animSpeed = 10.0f;
		float t = io.DeltaTime * animSpeed;
		g_MenuAlpha = LerpFloat(g_MenuAlpha, 1.0f, t);
		g_MenuSlide = LerpFloat(g_MenuSlide, 0.0f, t);
		ImGui::SetNextWindowBgAlpha(g_MenuAlpha);
		ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(centerX, centerY + g_MenuSlide),ImGuiCond_FirstUseEver);
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
		if (!ImGui::Begin("##ClassicInputWindow", nullptr, flags))
		{
			ImGui::End();
			return;
		}
		ImVec2 winPos = ImGui::GetWindowPos();
		ImVec2 winSize = ImGui::GetWindowSize();
		RenderSnowInWindow(winPos, winSize);
		if (ImGui::BeginChild("##submenus",ImVec2(120, ImGui::GetContentRegionAvail().y),true))
		{
			const auto& submenus = UIManager::GetSubmenus();
			auto activeSubmenu = UIManager::GetActiveSubmenu();
			for (auto& submenu : submenus)
			{
				if (ImGui::Selectable(submenu->m_Name.data(),submenu == activeSubmenu))
				{
					UIManager::SetActiveSubmenu(submenu);
					UIManager::SetShowContentWindow(true);
				}
			}
		}
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginGroup();
		ImGui::TextUnformatted("YimMenuV2");
		if (ImGui::BeginChild("##minisubmenus", ImVec2(0, 50), true))
		{
			auto activeSubmenu = UIManager::GetActiveSubmenu();
			if (activeSubmenu) activeSubmenu->DrawCategorySelectors();
		}
		ImGui::EndChild();

		auto activeSubmenu = UIManager::GetActiveSubmenu();
		if (activeSubmenu != g_LastSubmenu)
		{
			g_ContentSlide = 20.0f;
			g_LastSubmenu = activeSubmenu;
		}
		g_ContentSlide = LerpFloat(g_ContentSlide, 0.0f, t);
		ImGui::Dummy(ImVec2(g_ContentSlide, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		if (ImGui::BeginChild("##options", ImVec2(0, 0), true))
		{
			if (ImFont* optionsFont = UIManager::GetOptionsFont())
				ImGui::PushFont(optionsFont);

			if (activeSubmenu)
				activeSubmenu->Draw();

			if (ImGui::GetFont() != ImGui::GetIO().FontDefault)
				ImGui::PopFont();
		}
		ImGui::EndChild();
		ImGui::EndGroup();
		ImGui::End();
	}
}*/
