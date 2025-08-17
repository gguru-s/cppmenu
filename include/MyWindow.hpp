#include "gtkmm/gestureclick.h"
#include "gtkmm/grid.h"
#include "gtkmm/window.h"
class MyWindow : public Gtk::Window {
  private:
    Glib::RefPtr<Gtk::GestureClick> click_controller;

    void                            on_click(int n_press, double x, double y);

  public:
    Gtk::Grid grid;
    MyWindow();
};
