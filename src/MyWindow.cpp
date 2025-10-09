#include "MyWindow.hpp"
#include <gtkmm.h>
#include "MyButton.hpp"
#include "gtk4-layer-shell.h"
#include <iostream>
#include "gtkmm/object.h"

void MyWindow::on_click(int n_press, double x, double y) {
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
    // clicks inside grid => do nothing, let widgets handle events
}

MyWindow::MyWindow() {
    set_title("cppmenu");
    set_opacity(1);
    set_default_size(500, 140);

    grid.set_margin(10);
    grid.set_size_request(BTN_WIDTH * 4, BTN_HEIGHT);
    grid.set_valign(Gtk::Align::CENTER);
    grid.set_halign(Gtk::Align::CENTER);

    // Makes the application full screen without border. Mod+q doesnt work for closing the app.
    // Allows clicking through the window and interact with apps behind this window
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
