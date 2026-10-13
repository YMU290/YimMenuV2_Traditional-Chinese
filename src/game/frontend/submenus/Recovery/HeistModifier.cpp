#include "HeistModifier.hpp"
#include "Heist/ApartmentHeist.hpp"
#include "Heist/DiamondCasinoHeist.hpp"
#include "Heist/CayoPericoHeist.hpp"
#include "Heist/DoomsdayHeist.hpp"
#include "Heist/KortzCenterHeist.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildHeistModifierMenu()
	{
		auto menu        = std::make_shared<Category>(TR("Heists"));
		auto heistTabBar = std::make_shared<TabBarItem>(TR("Heist Modifier"));

		heistTabBar->AddItem(RenderApartmentHeistMenu());
		heistTabBar->AddItem(RenderDiamondCasinoHeistMenu());
		heistTabBar->AddItem(RenderCayoPericoHeistMenu());
		heistTabBar->AddItem(RenderDoomsdayHeistMenu());
		heistTabBar->AddItem(RenderKortzCenterHeistMenu());

		menu->AddItem(std::move(heistTabBar));

		return menu;
	}
}