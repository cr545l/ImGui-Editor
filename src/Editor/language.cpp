#include "Precompiled.h"
#include "editor/imgui_editor.h"

#include <simpleini/SimpleIni.h>

BEGIN_NS_IMGUI_EDITOR

// key, value texts
static std::unordered_map<std::string, std::string> s_texts;

const char* get_language_text(const char* key)
{
    if (!s_texts.contains(key))
    {
        s_texts[key] = key;
    }

    return s_texts[key].c_str();
}

static std::string s_current_language_key = "en";
void set_language(const char* language_key)
{
    // 언어팩 로드
    {
        s_current_language_key = language_key;
        const std::string path = "lang/" + s_current_language_key + ".ini";

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

        s_texts.clear();
        CSimpleIniA::TNamesDepend sections;
        ini.GetAllSections(sections);
        for (const auto& i : sections)
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

    // 마지막으로 사용한 언어 저장
    CSimpleIniA ini;
    ini.SetUnicode();
    SI_Error rc = ini.LoadFile("imgui_editor.ini");
    if (rc == 0)
    {
        ini.SetValue("common", "language", language_key);
        rc = ini.SaveFile("imgui_editor.ini");
        if (rc < 0)
        {
            LOG("failed to save imgui_editor.ini");
        }
    }
}

const std::string& get_language()
{
    return s_current_language_key;
}

END_NS_IMGUI_EDITOR
