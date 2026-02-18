//
// Created by Fabian on 18.02.2026.
//

#ifndef CFG_WATCHER_SETTINGSMODEL_HPP
#define CFG_WATCHER_SETTINGSMODEL_HPP


#include <vector>
#include <string>


#include "SettingTraits.h"

struct UISetting
{
    std::string key;
    SettingUI ui;
    std::string value;
    std::vector<std::string> options;
};

std::vector<UISetting> build_settings_model();

#endif //CFG_WATCHER_SETTINGSMODEL_HPP