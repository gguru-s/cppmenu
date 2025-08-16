#include "gtkmm/application.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "gtkmm/image.h"
#include "gtkmm/object.h"
#include "gtkmm/window.h"
#include <gtk4-layer-shell/gtk4-layer-shell.h>
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
    Glib::RefPtr<Gtk::GestureClick> click_controller;

    void                            on_click(int n_press, double x, double y) {
        double gx, gy;
        if (!grid.translate_coordinates(*this, 0, 0, gx, gy)) {
            std::cerr << "Failed to translate coordinates!" << std::endl;
            return;
        }

        int gw = grid.get_allocation().get_width();
        int gh = grid.get_allocation().get_height();

        if (!(x >= gx && x <= gx + gw && y >= gy && y <= gy + gh)) {
            close();
        }
        // inside grid => do nothing, let widgets handle events
    }

  public:
    Gtk::Grid grid;
    MyWindow();
};

MyWindow::MyWindow() {
    set_title("cppmenu");
    set_opacity(1);
    set_default_size(500, 140);

    grid.set_margin(10);
    grid.set_size_request(BTN_WIDTH * 4, BTN_HEIGHT);
    grid.set_valign(Gtk::Align::CENTER);
    grid.set_halign(Gtk::Align::CENTER);

    gtk_layer_init_for_window(gobj());
    gtk_layer_set_layer(gobj(), GTK_LAYER_SHELL_LAYER_OVERLAY);
    gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
    gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);

    auto logoutBtn = Gtk::make_managed<MyButton>("./contents/icons/logout.png");
    auto lockBtn   = Gtk::make_managed<MyButton>("./contents/icons/lock.png");
    auto rebootBtn = Gtk::make_managed<MyButton>("./contents/icons/user.png");
    auto powerBtn  = Gtk::make_managed<MyButton>("./contents/icons/power.png");

    logoutBtn->signal_clicked().connect([&]() { logoutBtn->on_button_clicked(LOGOUT); });
    lockBtn->signal_clicked().connect([&]() { lockBtn->on_button_clicked(LOCK); });
    rebootBtn->signal_clicked().connect([&]() { rebootBtn->on_button_clicked(REBOOT); });
    powerBtn->signal_clicked().connect([&]() { powerBtn->on_button_clicked(POWER); });

    grid.attach(*powerBtn, 0, 0);
    grid.attach(*logoutBtn, 1, 0);
    grid.attach(*lockBtn, 2, 0);
    grid.attach(*rebootBtn, 3, 0);

    click_controller = Gtk::GestureClick::create();
    click_controller->signal_pressed().connect(sigc::mem_fun(*this, &MyWindow::on_click));
    add_controller(click_controller);
    set_child(grid);

    // Style: transparent window + semi-transparent overlay
    auto provider = Gtk::CssProvider::create();
    provider->load_from_data(R"(
            window {
                background-color: transparent;
            }
            .background {
                background-color: rgba(0, 0, 0, 0.4);
            }
        )");

    get_style_context()->add_provider_for_display(Gdk::Display::get_default(), provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("com.guru.simple");

    return app->make_window_and_run<MyWindow>(argc, argv);
}
