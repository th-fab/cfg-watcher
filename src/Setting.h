//
// Created by Fabian on 18.02.2026.
//

#ifndef CFG_WATCHER_SETTING_H
#define CFG_WATCHER_SETTING_H

#include <string>
#include <type_traits>
#include <libconfig.h++>

#include "ISetting.h"
#include "SettingTraits.h"
#include "Registry.h"

template<typename T>
class Setting : public ISetting
{
public:
    using value_type = T;

    Setting(const char* key, const T& default_value)
        : m_key(key),
          m_value(default_value),
          m_default(default_value)
    {
        // automatic global registration
        settings_registry().push_back(this);
    }

    /* ---------- ISetting interface ---------- */

    [[nodiscard]] const std::string& key() const override
    {
        return m_key;
    }

    [[nodiscard]] SettingUI ui_type() const override
    {
        return SettingTraits<T>::ui();
    }

    void reset() override
    {
        m_value = m_default;
    }

    /* ---------- Typed access ---------- */

    const T& get() const { return m_value; }

    void set(const T& v)
    {
        if constexpr (SettingTraits<T>::has_validation)
        {
            if (!SettingTraits<T>::validate(v))
                return;
        }
        m_value = v;
    }

    /* ---------- Serialization ---------- */

    void save(libconfig::Setting& root) const override
    {
        SettingTraits<T>::save(root, m_key.c_str(), m_value);
    }

    void load(const libconfig::Setting& root) override
    {
        if (T tmp{}; SettingTraits<T>::load(root, m_key.c_str(), tmp))
            set(tmp);
    }

private:
    std::string m_key;
    T m_value;
    T m_default;
};

#endif //CFG_WATCHER_SETTING_H