#include "Category.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu
{
	void Category::Draw()
	{
		for (auto& item : m_Items)
			item->Draw();
	}

	int Category::GetLength()
	{
		const auto& categoryName = Translator::TranslateStored(m_Name);
		return std::max(ImGui::CalcTextSize(categoryName.c_str()).x + 25.0f, 75.0f);
	}
}