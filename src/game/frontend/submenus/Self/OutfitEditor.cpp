#include "OutfitEditor.hpp"

#include "core/frontend/manager/UIManager.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

#include <random>

// TODO: clean up more AI generated junk from this file

namespace YimMenu
{
	int GetMaxDrawable(int slot)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot);
	}

	int GetMaxTexture(int slot, int drawable)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot, drawable);
	}

	int GetMaxPropDrawable(int slot)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot);
	}

	int GetMaxPropTexture(int slot, int drawable)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot, drawable);
	}

	void GetOutfitSlot(int slot, int& drawable, int& texture)
	{
		auto ped = Self::GetPed();
		drawable = PED::GET_PED_DRAWABLE_VARIATION(static_cast<int>(ped.GetHandle()), slot);
		texture = PED::GET_PED_TEXTURE_VARIATION(static_cast<int>(ped.GetHandle()), slot);
	}

	void GetPropSlot(int slot, int& drawable, int& texture)
	{
		auto ped = Self::GetPed();
		drawable = PED::GET_PED_PROP_INDEX(static_cast<int>(ped.GetHandle()), slot, 0);
		if (drawable == -1)
		{
			drawable = 0;
			texture = 0;
			return;
		}
		texture = PED::GET_PED_PROP_TEXTURE_INDEX(static_cast<int>(ped.GetHandle()), slot);
	}

	void SetOutfitSlot(int slot, int drawable, int texture)
	{
		auto ped = Self::GetPed();
		PED::SET_PED_COMPONENT_VARIATION(static_cast<int>(ped.GetHandle()), slot, drawable, texture, 0);
	}

	void SetPropSlot(int slot, int drawable, int texture)
	{
		auto ped = Self::GetPed();
		PED::SET_PED_PROP_INDEX(static_cast<int>(ped.GetHandle()), slot, drawable, texture, true, 0);
	}

	// Helper function for underlined text
	static void TextUnderlined(const char* text)
	{
		ImGui::Text("%s", text);
		ImVec2 min = ImGui::GetItemRectMin();
		ImVec2 max = ImGui::GetItemRectMax();
		min.y = max.y;
		ImGui::GetWindowDrawList()->AddLine(min, max, ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Text]));
	}

	static void TextUnderlinedAt(const char* text, float y)
	{
		auto old_cursor = ImGui::GetCursorPos();
		ImGui::SetCursorPosY(y);
		TextUnderlined(text);
		ImGui::SetCursorPos(old_cursor);
	}

	std::shared_ptr<Category> CreateOutfitsMenu()
	{
		auto category = std::make_shared<Category>(TR("Outfit Editor"));

		category->AddItem(std::make_shared<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled(TR("Natives not cached yet"));
		//return ImGui::TextDisabled("Natives not cached yet");

			auto ped = Self::GetPed();

			if (!ped)
				return ImGui::TextDisabled(TR("Player ped not found"));
		//return ImGui::TextDisabled("Player ped not found");

			// Create two columns layout
			const float windowWidth = ImGui::GetContentRegionAvail().x;
			const float columnWidth = windowWidth * 0.5f;
			const float inputWidth = 150.0f; // Minimal width for number input

			ImGui::Columns(2, "OutfitColumns", false);
			ImGui::SetColumnWidth(0, columnWidth);

			// Components section (Left column)

			float header_y = ImGui::GetCursorPosY();
            

			TextUnderlined(TR("Components"));

const struct
			{
				const char* name;
				int slot;
			} componentSlots[] = {
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Top");
				     return s.c_str();
			     }(),
			        11},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Undershirt");
				     return s.c_str();
			     }(),
			        8},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Legs");
				     return s.c_str();
			     }(),
			        4},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Feet");
				     return s.c_str();
			     }(),
			        6},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Accessories");
				     return s.c_str();
			     }(),
			        7},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Bags");
				     return s.c_str();
			     }(),
			        5},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Mask");
				     return s.c_str();
			     }(),
			        1},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Gloves");
				     return s.c_str();
			     }(),
			        3},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Decals");
				     return s.c_str();
			     }(),
			        10},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Armor");
				     return s.c_str();
			     }(),
			        9}};

			bool first_iter = true;
			for (const auto& component : componentSlots)
			{
				ImGui::PushID(component.slot);

				int drawable, texture;
				GetOutfitSlot(component.slot, drawable, texture);

				ImGui::Text("%s", component.name);
				ImGui::SameLine();

				ImGui::SetCursorPosX(columnWidth - inputWidth * 2 - 10);

				ImGui::PushItemWidth(inputWidth);
				if (first_iter)
					TextUnderlinedAt(TR("Drawable"), header_y);
				if (ImGui::InputInt("##{}drawable", &drawable))
				{
					drawable = std::clamp(drawable, 0, GetMaxDrawable(component.slot) - 1);
					SetOutfitSlot(component.slot, drawable, texture);
				}
				ImGui::SameLine();
				if (first_iter)
					TextUnderlinedAt(TR ("Texture"), header_y); // TODO: this heading is slightly misaligned and I'm not sure why (caused by the above SameLine?)
				if (ImGui::InputInt("##{}texture", &texture))
				{
					texture = std::clamp(texture, 0, GetMaxTexture(component.slot, drawable) - 1);
					SetOutfitSlot(component.slot, drawable, texture);
				}
				ImGui::PopItemWidth();
				ImGui::PopID();

				first_iter = false;
			}

		// Props section (Right column)
			ImGui::NextColumn();

			TextUnderlined(TR("Props"));

			const struct
			{
				const char* name;
				int slot;
			} propSlots[] = {
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Hats");
				     return s.c_str();
			     }(),
			        0},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Glasses");
				     return s.c_str();
			     }(),
			        1},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Ears");
				     return s.c_str();
			     }(),
			        2},
			    {[]() {
				     static std::string s = YimMenu::Translator::Get("Watches");
				     return s.c_str();
			     }(),
			        6}};

			first_iter = true;
			for (const auto& prop : propSlots)
			{
				ImGui::PushID(prop.slot);

				int drawable, texture;
				GetPropSlot(prop.slot, drawable, texture);

				ImGui::Text("%s", prop.name);
				ImGui::SameLine();

				ImGui::SetCursorPosX(columnWidth + (columnWidth - inputWidth * 2 - 10));

				ImGui::PushItemWidth(inputWidth);
				if (first_iter)
					TextUnderlinedAt(TR("Drawable"), header_y);
				if (ImGui::InputInt("##pdrawable", &drawable))
				{
					drawable = std::clamp(drawable, 0, GetMaxPropDrawable(prop.slot) - 1);
					SetPropSlot(prop.slot, drawable, texture);
				}
				ImGui::SameLine();
				if (first_iter)
					TextUnderlinedAt(TR("Texture"), header_y);
				if (ImGui::InputInt("##ptexture", &texture))
				{
					texture = std::clamp(texture, 0, GetMaxPropTexture(prop.slot, drawable) - 1);
					SetPropSlot(prop.slot, drawable, texture);
				}
				ImGui::PopItemWidth();
				ImGui::PopID();

				first_iter = false;
			}

			ImGui::Columns(1);

			if (ImGui::Button(TR("Randomize Outfit")))
			{
				std::random_device rd;
				std::mt19937 gen(rd());

				// Randomize components
				for (int i = 0; i < 12; ++i)
				{
					int maxDrawable = GetMaxDrawable(i);
					if (maxDrawable > 0)
					{
						int drawable = std::uniform_int_distribution<>(0, maxDrawable - 1)(gen);
						int maxTexture = GetMaxTexture(i, drawable);
						int texture = maxTexture > 0 ? std::uniform_int_distribution<>(0, maxTexture - 1)(gen) : 0;
						SetOutfitSlot(i, drawable, texture);
					}
				}

				// Randomize props
				for (int i : {0, 1, 2, 6, 7})
				{
					int maxDrawable = GetMaxPropDrawable(i);
					if (maxDrawable > 0)
					{
						int drawable = std::uniform_int_distribution<>(0, maxDrawable - 1)(gen);
						int maxTexture = GetMaxPropTexture(i, drawable);
						int texture = maxTexture > 0 ? std::uniform_int_distribution<>(0, maxTexture - 1)(gen) : 0;
						SetPropSlot(i, drawable, texture);
					}
				}
			}
		}));

		return category;
	}
}
