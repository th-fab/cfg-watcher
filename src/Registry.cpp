//
// Created by Fabian on 18.02.2026.
//

#include "Registry.h"
#include "ISetting.h"

std::vector<ISetting*>& settings_registry()
{
    static std::vector<ISetting*> registry;
    return registry;
}