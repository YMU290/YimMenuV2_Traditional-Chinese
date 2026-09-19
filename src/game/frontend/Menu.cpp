#include "Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/frontend/fonts/Fonts.hpp"
#include "submenus/Self.hpp"
#include "submenus/Vehicle.hpp"
#include "submenus/Teleport.hpp"
#include "submenus/Network.hpp"
#include "submenus/Players.hpp"
#include "submenus/Recovery.hpp"
#include "submenus/Settings.hpp"
#include "submenus/Debug.hpp"
#include "submenus/World.hpp"
#include "Onboarding.hpp"
#include "core/localization/Translator.hpp"


namespace YimMenu
{
	void Menu::Init()
	{
		// Arguably the only place this file should be edited at for more menus
		UIManager::AddSubmenu(std::make_shared<Submenus::Self>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Vehicle>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Teleport>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Network>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Players>());
		UIManager::AddSubmenu(std::make_shared<Submenus::World>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Recovery>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Settings>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Debug>());

		Renderer::AddRendererCallback(
		    [&] {
			    ProcessOnboarding();
			    if (!GUI::IsOpen())
				    return;

			    ImGui::PushFont(Menu::Font::g_DefaultFont);
			    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(15, 15, 15)));

			    UIManager::Draw();

			    ImGui::PopStyleColor();
			    ImGui::PopFont();
		    },
		    -1);
	}

		static const ImWchar* GetGlyphRangesCyrillicOnly()
	{
		static const ImWchar ranges[] =
		    {
		        0x0400,
		        0x052F, // Cyrillic + Cyrillic Supplement
		        0x2DE0,
		        0x2DFF, // Cyrillic Extended-A
		        0xA640,
		        0xA69F, // Cyrillic Extended-B
		        0,
		    };
		return &ranges[0];
	}

	
	static ImFont* CreateFontWithCyrillicSupport(ImGuiIO& io, float size)
	{
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		auto font = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), size, &FontCfg, io.Fonts->GetGlyphRangesDefault());

		// just use Arial for Cyrillic

		FontCfg.MergeMode = true;
		io.Fonts->AddFontFromFileTTF((std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts" / "arial.ttf").string().c_str(), size, &FontCfg, GetGlyphRangesCyrillicOnly());
		io.Fonts->AddFontFromFileTTF((std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts" / "meiryo.ttc").string().c_str(), size, &FontCfg, io.Fonts->GetGlyphRangesJapanese());

		io.Fonts->Build();

		return font;
	}

	ImFont* CreateFontWithCyrillicAndChineseSupport(ImGuiIO& IO, float size)
	{
		ImFontConfig font_cfg{};
		font_cfg.FontDataOwnedByAtlas = false;

		// 中文字符范围
		static const ImWchar chinese_ranges[] = {
		    0x0020,
		    0x00FF, // 基本拉丁字母 + 拉丁补充
		    0x0400,
		    0x052F, // 西里尔字母
		    0x3000,
		    0x30FF, // 中文标点符号 + 日文假名
		    0x4E00,
		    0x9FFF, // 中文统一表意文字
		    0xFF00,
		    0xFFEF, // 半角全角字符
		    0,
		};

		// 加载支持中文的字体文件
		// 方法1: 加载外部中文字体文件
		std::filesystem::path font_path = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2" / "Fonts";

		// 常用的中文字体文件路径
		std::vector<std::string> chinese_fonts = {
		    (font_path / "msyh.ttc").string(),   // 微软雅黑
		    (font_path / "simhei.ttf").string(), // 黑体
		    (font_path / "simsun.ttc").string(), // 宋体
		    "C:/Windows/Fonts/msyh.ttc",         // 系统默认路径
		    "C:/Windows/Fonts/simhei.ttf",
		};

		// 尝试加载中文字体
		for (const auto& font_file : chinese_fonts)
		{
			if (std::filesystem::exists(font_file))
			{
				return IO.Fonts->AddFontFromFileTTF(
				    font_file.c_str(),
				    size,
				    &font_cfg,
				    chinese_ranges);
			}
		}

		// 方法2: 如果外部字体不存在，使用内置字体并合并中文字体
		ImFont* base_font = IO.Fonts->AddFontDefault(&font_cfg);

		// 合并中文字体到默认字体
		font_cfg.MergeMode = true;
		font_cfg.GlyphOffset = ImVec2(0, 0);

		// 再次尝试加载外部中文字体用于合并
		for (const auto& font_file : chinese_fonts)
		{
			if (std::filesystem::exists(font_file))
			{
				IO.Fonts->AddFontFromFileTTF(
				    font_file.c_str(),
				    size,
				    &font_cfg,
				    chinese_ranges);
				break;
			}
		}

		return base_font;
	}

	void Menu::SetupFonts()
	{
		auto& IO = ImGui::GetIO();
		auto file_path = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2" / "imgui.ini";
		static auto path = file_path.string();
		IO.IniFilename = path.c_str();
		IO.LogFilename = NULL;
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		IO.Fonts->Clear();

		// 中文字符范围 (包含中文、拉丁字母、西里尔字母等常用字符)
		static const ImWchar chinese_ranges[] = {
		    0x0020,
		    0x00FF, // 基本拉丁字母 + 拉丁补充
		    0x0400,
		    0x052F, // 西里尔字母
		    0x3000,
		    0x30FF, // 中文标点符号 + 日文假名
		    0x4E00,
		    0x9FFF, // 中文统一表意文字
		    0xFF00,
		    0xFFEF, // 半角全角字符
		    0,
		};

		// 为所有字体指定中文字符集
		FontCfg.MergeMode = false;
		FontCfg.GlyphRanges = chinese_ranges;

		Menu::Font::g_DefaultFont = CreateFontWithCyrillicAndChineseSupport(IO, Menu::Font::g_DefaultFontSize);
		Menu::Font::g_OptionsFont = CreateFontWithCyrillicAndChineseSupport(IO, Menu::Font::g_OptionsFontSize);
		Menu::Font::g_ChildTitleFont = CreateFontWithCyrillicAndChineseSupport(IO, Menu::Font::g_ChildTitleFontSize);
		Menu::Font::g_ChatFont = CreateFontWithCyrillicAndChineseSupport(IO, Menu::Font::g_ChatFontSize);
		Menu::Font::g_OverlayFont = CreateFontWithCyrillicAndChineseSupport(IO, Menu::Font::g_OverlayFontSize);

		// 图标字体也需要合并中文字符（如果需要显示中文图标标签）
		FontCfg.MergeMode = true;
		FontCfg.GlyphRanges = chinese_ranges;
		Menu::Font::g_AwesomeFont = IO.Fonts->AddFontFromMemoryTTF(
		    const_cast<std::uint8_t*>(Fonts::IconFont),
		    sizeof(Fonts::IconFont),
		    Menu::Font::g_AwesomeFontSize,
		    &FontCfg,
		    chinese_ranges);

		UIManager::SetOptionsFont(Menu::Font::g_OptionsFont);
		Renderer::SetFontsUpdated();
	}
}