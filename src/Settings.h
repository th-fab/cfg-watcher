//
// Created by Fabian on 12.02.2026.
//
#ifndef CFG_WATCHER_SETTINGS_H
#define CFG_WATCHER_SETTINGS_H

#include <string>
#include <libconfig.h++>
#include <unordered_map>
#include <variant>
namespace lc = libconfig;
namespace Settings {



    using AppSetting = std::variant<
        int,
        bool,
        double,
        std::string
    >;

    using AppSettings = std::unordered_map<std::string, AppSetting>;

    AppSettings load_settings();
    void save_settings(const AppSettings& settings);
    AppSettings create_default_settings();

}


#endif //CFG_WATCHER_SETTINGS_H
