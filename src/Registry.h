//
// Created by Fabian on 18.02.2026.
//

#ifndef CFG_WATCHER_REGISTRY_H
#define CFG_WATCHER_REGISTRY_H

#include <vector>

struct ISetting;

std::vector<ISetting*>& settings_registry();

#endif //CFG_WATCHER_REGISTRY_H