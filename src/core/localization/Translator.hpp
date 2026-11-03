#pragma once
#include <string>
#include <unordered_map>
#define TR(key, ...) YimMenu::Translator::Get(key).c_str()

namespace YimMenu
{
	class Translator
	{
	private:
		static inline std::unordered_map<std::string, std::string> m_Translations;
		static inline bool m_Initialized = false;

		static std::string EnsureUTF8(const char* str);
		static void InitializeChineseTranslations();

	public:
		static void Initialize();
		static std::string Get(const std::string& key);
	};
}



