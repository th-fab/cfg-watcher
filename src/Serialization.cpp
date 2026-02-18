//
// Created by Fabian on 18.02.2026.
//

#include "Registry.h"
#include "ISetting.h"
#include <libconfig.h++>
#include "Serialization.h"

#include <iostream>
#include <ostream>

void save_all_settings(const char* file)
{
    const libconfig::Config cfg;

    auto& root =
        cfg.getRoot().add("settings",
            libconfig::Setting::TypeGroup);

    for (const auto* s : settings_registry())
        s->save(root);

    cfg.writeFile(file);
}

void load_all_settings(const char* file)
{
    libconfig::Config cfg;

    try
    {
        cfg.readFile(file);
    }
    catch(...)
    {
        std::cout << "Error reading settings, applying default!" << std::endl;
        return;
    }

    const auto& root = cfg.lookup("settings");

    for (auto* s : settings_registry())
        s->load(root);
}