#pragma once
#include "Category.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu
{
	class Submenu
	{
	public:
		constexpr Submenu(std::string name, std::string icon = "") :
		    m_Name(name),
		    m_Icon(icon)
		{
		}

		std::shared_ptr<Category> GetActiveCategory() const
		{
			return m_ActiveCategory;
		}

		void AddCategory(std::shared_ptr<Category>&& category);
		void RemoveCategory(const std::shared_ptr<Category>& category);
		void DrawCategorySelectors();
		void SetActiveCategory(const std::shared_ptr<Category> category);
		void Draw();

		const std::string& GetDisplayName() const
		{
			return Translator::TranslateStored(m_Name);
		}

	private:
		std::shared_ptr<Category> m_ActiveCategory;

	public:
		std::vector<std::shared_ptr<Category>> m_Categories;
		std::string m_Name;
		std::string m_Icon; // currently unused
	};
}