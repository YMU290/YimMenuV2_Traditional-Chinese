#include "Items.hpp"

namespace YimMenu
{
	CollapsingHeaderItem::CollapsingHeaderItem(const std::string& name) :
	    m_Name(name)
	{
	}

	void CollapsingHeaderItem::Draw()
	{
		if (ImGui::CollapsingHeader(Translator::TranslateStored(m_Name).c_str()))
		{
			for (auto& item : m_Items)
			{
				if (item->CanDraw())
					item->Draw();
			}
		}
	}
}