#include "slint-main.h"
#include <filesystem>
#include <libconfig.h++>
#include "Settings.h"

FILE load_app_settings();

namespace lc = libconfig;

int main(int argc, char **argv)
{
    Settings::AppSettings settings;
    try {
        settings = Settings::load_settings();
    } catch (std::exception &e) {
        std::cout << "No file found probably, creating a new one with default settings!";
        settings = Settings::create_default_settings();
    }

    try {
        Settings::save_settings(settings);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
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
    return 0;
}

