//
// Created by Fabian on 18.02.2026.
//

#ifndef CFG_WATCHER_SETTINGTRAITS_H
#define CFG_WATCHER_SETTINGTRAITS_H
#include <string>
#include <type_traits>
#include <vector>
#include <libconfig.h++>
#include "enums.h"

enum class SettingUI
{
    Checkbox,
    Slider,
    Dropdown,
    Text
};

/**
 * @brief Basic template for settings
 * @tparam T
 */

template<typename T>
struct SettingTraits
{
    static constexpr bool has_validation = false;

    static SettingUI ui()
    {
        return SettingUI::Dropdown;
    }

    static void save(libconfig::Setting& root,
                     const char* key,
                     const T& value)
    {
        root.add(key, libconfig::Setting::TypeString)
            = to_string(value);
    }

    static bool load(const libconfig::Setting& root,
                     const char* key,
                     T& out)
    {
        if (!root.exists(key))
            return false;

        out = from_string(
            static_cast<const char*>(root[key]));
        return true;
    }

    static std::string to_string(const T&);;
    static T from_string(const std::string&);
};

template<>
struct SettingTraits<bool>
{
    static constexpr bool has_validation = false;

    static SettingUI ui()
    {
        return SettingUI::Checkbox;
    }

    static void save(libconfig::Setting& root,
                     const char* key,
                     const bool value)
    {
        root.add(key, libconfig::Setting::TypeBoolean) = value;
    }

    static bool load(const libconfig::Setting& root,
                     const char* key,
                     bool& out)
    {
        if (!root.exists(key))
            return false;

        out = static_cast<bool>(root[key]);
        return true;
    }
};

template<>
struct SettingTraits<float>
{
    static constexpr bool has_validation = false;

    static SettingUI ui()
    {
        return SettingUI::Slider;
    }
    static void save(libconfig::Setting& root,
                     const char* key,
                     const float value)
    {
        root.add(key, libconfig::Setting::TypeFloat) = value;
    }

    static bool load(const libconfig::Setting& root,
                     const char* key,
                     float& out)
    {
        if (!root.exists(key))
            return false;

        out = static_cast<float>(root[key]);
        return true;
    }
};

template<typename T>
struct is_enum_setting
{
    static constexpr bool value = std::is_enum_v<T>;
};


template<>
struct SettingTraits<Quality>
{
    static constexpr bool has_validation = true;

    static SettingUI ui()
    {
        return SettingUI::Dropdown;
    }

    static bool validate(Quality)
    {
        return true; // enum already constrained
    }

    static std::string to_string(Quality q)
    {
        switch (q)
        {
            case Quality::Low: return "low";
            case Quality::Medium: return "medium";
            case Quality::High: return "high";
        }
        return "medium";
    }

    static Quality from_string(const std::string& s)
    {
        if (s == "low") return Quality::Low;
        if (s == "high") return Quality::High;
        return Quality::Medium;
    }

    static void save(libconfig::Setting& root,
                     const char* key,
                     Quality value)
    {
        root.add(key, libconfig::Setting::TypeString)
            = to_string(value);
    }

    static bool load(const libconfig::Setting& root,
                     const char* key,
                     Quality& out)
    {
        if (!root.exists(key))
            return false;

        out = from_string(
            static_cast<const char*>(root[key]));
        return true;
    }
};

#endif //CFG_WATCHER_SETTINGTRAITS_H