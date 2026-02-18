//
// Created by Fabian on 18.02.2026.
//

#ifndef CFG_WATCHER_ISETTINGS_H
#define CFG_WATCHER_ISETTINGS_H

#include <libconfig.h++>
#include "enums.h"
#include "SettingTraits.h"

struct ISetting
{
public:
    virtual ~ISetting() = default;

    [[nodiscard]] virtual const std::string& key() const = 0;
    [[nodiscard]] virtual SettingUI ui_type() const = 0;
    virtual void reset() = 0;
    virtual void save(libconfig::Setting&) const = 0;
    virtual void load(const libconfig::Setting&) = 0;
};

#endif //CFG_WATCHER_ISETTINGS_H