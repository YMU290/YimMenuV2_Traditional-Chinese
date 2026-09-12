#pragma once
#include <cstdint>

namespace YimMenu::Fonts
{
	// 原始英文字體
	extern const uint8_t MainFont[78948];
	extern const uint8_t IconFont[1049188];
	
	// 新增：中文字體（嵌入字體數據）
	extern const uint8_t ChineseFont[15728640]; // 約 15MB 的中文字體
	
	// 或者使用較小的字體子集
	extern const uint8_t ChineseFontSubset[2097152]; // 約 2MB
	
	// 字體配置選項
	enum FontType
	{
		FONT_ENGLISH_ONLY,
		FONT_ENGLISH_CHINESE_MERGED,
		FONT_CHINESE_ONLY
	};
	

}