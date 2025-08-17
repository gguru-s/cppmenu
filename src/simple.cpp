#include "gtkmm/application.h"
#include "MyButton.hpp"
#include "MyWindow.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("com.guru.simple");

    return app->make_window_and_run<MyWindow>(argc, argv);
}
