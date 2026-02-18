//
// Created by Fabian on 18.02.2026.
//

#include "SettingsModel.h"
#include "Registry.h"
#include "ISetting.h"
#include "Setting.h"
#include "enums.h"

std::vector<UISetting> build_settings_model()
{
    std::vector<UISetting> result;

    for (auto* s : settings_registry())
    {
        UISetting ui;

        ui.key = s->key();
        ui.ui  = s->ui_type();

        // value conversion happens through traits later
        // (simplified example)
        ui.value = "";

        result.push_back(ui);
    }

    return result;
}