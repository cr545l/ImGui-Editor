#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <simpleini/SimpleIni.h>

namespace imgui_editor
{
	// key, value texts
	static std::unordered_map<std::string, std::string> s_texts;

	const char* get_language_text(const char* key)
	{
		if(s_texts.contains(key))
		{
			return s_texts[key].c_str();
		}
		return "";
	}

	void set_language(const char* language_key)
	{
		const std::string path = "lang/" + std::string(language_key) + ".ini";

		CSimpleIniA ini;
		ini.SetUnicode();
		SI_Error error = ini.LoadFile(path.c_str());
		if (error < 0)
		{
			error = ini.SaveFile("imgui_editor.ini");
			if (error < 0)
			{
				LOG("failed to save imgui_editor.ini");
				return;
			}
		}
		CSimpleIniA::TNamesDepend sections;
		ini.GetAllSections(sections);
		for(const auto& i : sections)
		{
			// print
			LOG(i.pItem);

			CSimpleIniA::TNamesDepend keys;
			ini.GetAllKeys(i.pItem, keys);

			for (const auto& j : keys)
			{
				const std::string key = std::format("{}.{}", i.pItem, j.pItem);
				s_texts[key] = ini.GetValue(i.pItem, j.pItem);
			}
		}
	}
}