#include "MyButton.hpp"
#include "iostream"

MyButton::MyButton(std::string src) {
    myImage = Gtk::Image(src);
    set_margin(10);
    set_size_request(BTN_WIDTH, BTN_HEIGHT);
    set_child(myImage);
};

void MyButton::on_button_clicked(btnType type) {
    switch (type) {
        case POWER:
            std::cout << "power button clicked" << std::endl;
            // system("shutdown -h now");
            break;

        case LOGOUT:
            std::cout << "logout button clicked" << std::endl;
            // system("hyprctl dispatch exit 0");
            break;

        case LOCK:
            std::cout << "lock button clicked" << std::endl;
            // system("playerctl pause");
            // system("swaylock -f -i /home/guru/Pictures/Wallpapers/Sekiro/lockscreen.jpg");
            break;

        case REBOOT:
            std::cout << "reboot button clicked" << std::endl;
            // system("reboot");
            break;
    }
};
