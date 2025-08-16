#include "gtkmm/application.h"
#include "gtkmm/button.h"
#include "gtkmm/grid.h"
#include "gtkmm/image.h"
#include "gtkmm/overlay.h"
#include "gtkmm/window.h"
#include <gtkmm.h>
#include "iostream"

using namespace std;

const int BTN_WIDTH  = 100;
const int BTN_HEIGHT = 100;

enum btnType {
    POWER,
    LOCK,
    LOGOUT,
    REBOOT
};

class MyButton : public Gtk::Button {
  private:
    Gtk::Image myImage;

  public:
    MyButton(string src) {
        myImage = Gtk::Image(src);
        set_margin(10);
        set_size_request(BTN_WIDTH, BTN_HEIGHT);
        set_child(myImage);
    };

    void on_button_clicked(btnType type) {
        switch (type) {
            case POWER:
                cout << "power button clicked" << endl;
                // system("shutdown -h now");
                break;

            case LOGOUT:
                cout << "logout button clicked" << endl;
                // system("hyprctl dispatch exit 0");
                break;

            case LOCK:
                cout << "lock button clicked" << endl;
                // system("playerctl pause");
                // system("swaylock -f -i /home/guru/Pictures/Wallpapers/Sekiro/lockscreen.jpg");
                break;

            case REBOOT:
                cout << "reboot button clicked" << endl;
                // system("reboot");
                break;
        }
    };
};

class MyWindow : public Gtk::Window {
  private:
  public:
    MyWindow();
};

MyWindow::MyWindow() {
    set_title("cppmenu");
    set_opacity(1);
    set_default_size(500, 140);

    Gtk::Grid grid = Gtk::Grid();
    grid.set_margin(10);
    grid.set_size_request(BTN_WIDTH * 4, BTN_HEIGHT);

    MyButton logoutBtn("./contents/icons/logout.png");
    MyButton lockBtn("./contents/icons/lock.png");
    MyButton rebootBtn("./contents/icons/user.png");
    MyButton powerBtn("./contents/icons/power.png");

    logoutBtn.signal_clicked().connect([&]() { logoutBtn.on_button_clicked(LOGOUT); });
    lockBtn.signal_clicked().connect([&]() { lockBtn.on_button_clicked(LOCK); });
    rebootBtn.signal_clicked().connect([&]() { rebootBtn.on_button_clicked(REBOOT); });
    powerBtn.signal_clicked().connect([&]() { powerBtn.on_button_clicked(POWER); });

    grid.attach(powerBtn, 0, 0);
    grid.attach(logoutBtn, 1, 0);
    grid.attach(lockBtn, 2, 0);
    grid.attach(rebootBtn, 3, 0);

    Gtk::Overlay overlay;
    overlay.add_overlay(grid);
    set_child(overlay);
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("com.guru.simple");
    return app->make_window_and_run<MyWindow>(argc, argv);
}
