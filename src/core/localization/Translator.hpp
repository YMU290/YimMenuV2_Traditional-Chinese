#pragma once
#include <string>
#include <unordered_map>

#define TR(key, ...) YimMenu::Translator::Get(key).c_str()

namespace YimMenu
{
	class ListCommand;

	class Translator
	{
	private:
		static inline std::unordered_map<std::string, std::string> m_Translations;
		static inline std::unordered_map<std::string, std::string> m_ReverseTranslations;
		static inline bool m_Initialized = false;
		static inline int m_Language = 0;

		static std::string EnsureUTF8(const char* str);
		static void InitializeChineseTranslations();

	public:
		enum class Language : int
		{
			TraditionalChinese,
			English
		};

		static void Initialize();
		static const std::string& Get(const std::string& key);
		static const std::string& TranslateStored(const std::string& value);
		static const std::string& TranslateStored(const char* value);
		static void SetLanguage(Language language);
		static Language GetLanguage();
		static ListCommand& GetLanguageCommand();
	};
}



