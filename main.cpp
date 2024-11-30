/*  Author: simargl <https://github.org/simargl>
 *  License: GPL v3
 */

//g++ `fltk-config --cxxflags` main.cpp `fltk-config --ldflags` -o wmlogout; ./wmlogout

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <cstdlib>
#include <iostream>

Fl_Color bcolor = 0x1f1f1f00;
Fl_Color fcolor = 0x36363500;

class Fl_HoverButton: public Fl_Button {
public:
    Fl_HoverButton(int x, int y, int w, int h, const char* label = 0): Fl_Button(x, y, w, h, label) {}
    int handle(int event) override {
        if (event == FL_ENTER || event == FL_LEAVE) {
            color(event == FL_ENTER ? fcolor : bcolor);
            redraw();
            return 1;
        }
        return Fl_Button::handle(event);
    }
};

void executeCommand(const char* command) {
    int result = std::system(command);
    if (result == -1) {
        std::cerr << "Failed to execute command: " << command << std::endl;
    }
    exit(0);
}

void action_poweroff(Fl_Widget*, void*) {
    executeCommand("wmpoweroff&");
}

void action_logout(Fl_Widget*, void*) {
    executeCommand("killall X & killall Xorg & killall Xorg.bin & killall labwc & killall sway & killall weston &");
}

void action_suspend(Fl_Widget*, void*) {
    executeCommand("pm-suspend&");
}

void action_reboot(Fl_Widget*, void*) {
    executeCommand("wmreboot&");
}

void action_quit(Fl_Widget*, void*) {
    exit(0);
}

int main(int argc, char** argv) {
    int screenWidth = Fl::w();
    int screenHeight = Fl::h();
    int windowWidth = 560;
    int windowHeight = 60;
    Fl_Double_Window* main_window = new Fl_Double_Window((screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, "WM Logout");
    main_window->color(bcolor);
    Fl_Group* group = new Fl_Group(10, 10, 540, 40);
    group->selection_color((Fl_Color)41);
    group->labelsize(16);
    Fl_HoverButton* buttons[] = {
        new Fl_HoverButton(10, 10, 100, 40, "Cancel"),
        new Fl_HoverButton(120, 10, 100, 40, "Logout"),
        new Fl_HoverButton(230, 10, 100, 40, "Reboot"),
        new Fl_HoverButton(340, 10, 100, 40, "Poweroff"),
        new Fl_HoverButton(450, 10, 100, 40, "Suspend")
    };
    const Fl_Callback* callbacks[] = {action_quit, action_logout, action_reboot, action_poweroff, action_suspend};
    for (int i = 0; i < 5; ++i) {
        buttons[i]->box(FL_FLAT_BOX);
        buttons[i]->color(bcolor);
        buttons[i]->labelsize(16);
        buttons[i]->labelcolor(FL_LIGHT2);
        buttons[i]->selection_color(bcolor);
        buttons[i]->callback((Fl_Callback*)callbacks[i]);
        buttons[i]->clear_visible_focus();
    }
    group->end();
    main_window->clear_border();
    main_window->show(argc, argv);
    return Fl::run();
}
