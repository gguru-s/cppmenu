#include "gtkmm/button.h"
#include "gtkmm/image.h"

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
    MyButton(std::string src);
    void on_button_clicked(btnType type);
};
