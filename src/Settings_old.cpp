//
// Created by Fabian on 12.02.2026.
//

#include "Settings_old.h"

#include <iostream>
#include <stdexcept>

std::string group_header = "appsettings";
std::string cfg_filename = "settings.cfg";

namespace Settings_old {
    void write_value(lc::Setting& parent,
                     const std::string& key,
                     const AppSetting& value)
    {
        std::visit([&](auto&& v)
        {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T,int>)
                parent.add(key, lc::Setting::TypeInt) = v;

            else if constexpr (std::is_same_v<T,double>)
                parent.add(key, lc::Setting::TypeFloat) = v;

            else if constexpr (std::is_same_v<T,bool>)
                parent.add(key, lc::Setting::TypeBoolean) = v;

            else if constexpr (std::is_same_v<T,std::string>)
                parent.add(key, lc::Setting::TypeString) = v;

        }, value);
    }

    AppSetting read_value(const lc::Setting& setting)
    {
        using Type = lc::Setting::Type;

        switch (setting.getType())
        {
            case Type::TypeInt:
                return static_cast<int>(setting);

            case Type::TypeFloat:
                return static_cast<double>(setting);

            case Type::TypeBoolean:
                return static_cast<bool>(setting);

            case Type::TypeString:
                return std::string(setting.c_str());

            default:
                throw std::runtime_error("Unsupported config type");
        }
    }

    AppSettings load_settings() {
        std::cout << "loading settings..." << std::endl;
        AppSettings result;
        lc::Config cfg;

        cfg.readFile(cfg_filename);

        const auto& group = cfg.lookup(group_header);

        for (int i = 0; i < group.getLength(); ++i)
        {
            const lc::Setting& s = group[i];

            std::string key = s.getName();
            result[key] = read_value(s);
        }

        return result;
    }

    void save_settings(const AppSettings& settings) {
        std::cout << "saving settings" << std::endl;
        const lc::Config cfg;

        auto& root = cfg.getRoot();
        auto& group =
            root.add(group_header, lc::Setting::TypeGroup);

        for (const auto& [key, value] : settings)
            write_value(group, key, value);

        cfg.writeFile(cfg_filename);
    }

    AppSettings create_default_settings() {
        std::cout << "creating default settings.." << std::endl;
        AppSettings settings;


        settings["is_setup"]        = true;
        settings["userdata-path"]   = std::string("unknown");
        settings["use_path_env"]    = false;
        settings["dark_mode"]       = true;

        return settings;
    }
}



/*static auto output_file = "appconfig.cfg";
const lc::Config cfg;

lc::Setting &root = cfg.getRoot();
lc::Setting &address = root.add("app_settings", lc::Setting::TypeGroup);

address.add("is_setup", lc::Setting::TypeBoolean) = true;
address.add("userdata_path", lc::Setting::TypeString) = "San Jose";
address.add("use_path_env", lc::Setting::TypeBoolean) = false;
address.add("dark_mode", lc::Setting::TypeBoolean) = true;

try
{
    cfg.writeFile(output_file);
    std::cerr << "New configuration successfully written to: " << output_file
         << std::endl;

}
catch(const libconfig::FileIOException &fioex)
{
    std::cerr << "I/O error while writing file: " << output_file << std::endl;
    return(EXIT_FAILURE);

}*/