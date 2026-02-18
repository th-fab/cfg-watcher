#include "slint-main.h"
#include <filesystem>
#include <libconfig.h++>

#include "Serialization.h"
#include "Setting.h"
#include "Settings_old.h"

FILE load_app_settings();

namespace lc = libconfig;

Setting<bool>       USE_DARKMODE("use_darkmode", true);
Setting<float>      VOLUME("volume", 0.5f);
Setting<Quality>    QUALITY("quality", Quality::Medium);
Setting<bool>       USE_REL_PATH("use_rel_path", false);

int main(int argc, char **argv)
{
    load_all_settings("settings2.cfg");

    std::cout << "loaded all settings!" << std::endl;


    for (auto* s : settings_registry())
    {
        std::cout << "Key: " << s->key() << " | ";

        switch (s->ui_type())
        {
            case SettingUI::Checkbox:
                // safe cast to Setting<bool>
                std::cout << "Value: "
                          << static_cast<Setting<bool>*>(s)->get()
                          << " (bool)\n";
                break;

            case SettingUI::Slider:
                std::cout << "Value: "
                          << static_cast<Setting<float>*>(s)->get()
                          << " (float)\n";
                break;

            case SettingUI::Dropdown:
                // Here we assume enum, could use templates or traits
                std::cout << "Value: "
                          << SettingTraits<Quality>::to_string(
                                static_cast<Setting<Quality>*>(s)->get()
                             )
                          << " (enum)\n";
                break;

            default:
                std::cout << "Unknown type\n";
        }
    }




    //load_all_settings("settings2.cfg");

    auto ui = AppWindow::create();

    //ui->hide();
    auto splash = SplashScreen::create();
    //splash->show();
    splash->on_splash_button_pressed([&] {
        ui->show();
        splash->hide();

    });


    ui->on_request_increase_value([&]{
        ui->set_counter(ui->get_counter() + 10);
    });


    //slint::run_event_loop();
    ui->run();

    save_all_settings("settings2.cfg");
    std::cout << "Saving settings before exiting!" << std::endl;
    return 0;
}

