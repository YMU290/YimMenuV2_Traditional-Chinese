#include "Items.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"

namespace YimMenu
{
	ListCommandItem::ListCommandItem(joaat_t id, std::optional<std::string> label_override) :
		m_CommandId(id),
		m_Command(nullptr),
	    m_LabelOverride(label_override)
	{
	}

	void ListCommandItem::Draw()
	{
		m_Command = Commands::GetCommand<ListCommand>(m_CommandId);
		if (!m_Command)
		{
			ImGui::Text("%s", TR("Unknown list!"));
			return;
		}

		int current_val = m_Command->GetState();
		if (m_Command->GetName() == "language")
			Translator::SetLanguage(static_cast<Translator::Language>(current_val));

		auto& list = m_Command->GetList();
		m_SelectedItem.reset();
		std::string largestString;
		std::size_t largest_string_len = 0;

		for (auto& item : list)
		{
			const auto translatedItem = Translator::TranslateStored(item.second);
			if (item.first == current_val)
				m_SelectedItem = translatedItem;

			int length = static_cast<int>(translatedItem.size());
			if (length > largest_string_len)
			{
				largestString = translatedItem;
				largest_string_len = length;
			}
		}

		if (!m_SelectedItem.has_value())
			m_SelectedItem = "";

		m_ItemWidth = static_cast<int>(ImGui::CalcTextSize(largestString.c_str()).x + 40.0f);

		ImGui::SetNextItemWidth(m_ItemWidth.value());
		if (ImGui::BeginCombo(TranslateItemLabel(m_LabelOverride, m_Command->GetLabel()).c_str(), m_SelectedItem.value().c_str()))
		{
			for (auto& el : list)
			{
				const auto translatedItem = Translator::TranslateStored(el.second);
				if (ImGui::Selectable(translatedItem.c_str(), el.first == current_val))
				{
					current_val = el.first;
					if (m_Command->GetName() == "language")
						m_Command->SetStateImmediate(el.first);
					else
						m_Command->SetState(el.first);
				}

				if (el.first == current_val)
				{
					m_SelectedItem = translatedItem;
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
}