/*  Author: simargl <https://github.org/simargl>
 *  License: GPL v3
 */

//g++ `fltk-config --cxxflags` wmlogout.cxx `fltk-config --ldflags` -o wmlogout; ./wmlogout

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <cstdlib>
Fl_Color bcolor = 0x2d2d2d00;
Fl_Color fcolor = 0x15539e00;

class Fl_HoverButton: public Fl_Button {
  public:
    Fl_HoverButton(int x, int y, int w, int h,
                   const char * label = 0): Fl_Button(x, y, w, h, label) {}

    int handle(int event) override {
        switch (event) {
        case FL_ENTER:
            color(fcolor);
            redraw();
            return 1;
        case FL_LEAVE:
            color(bcolor);
            redraw();
            return 1;
        }
        return Fl_Button::handle(event);
    }
};

void action_poweroff(Fl_Widget *, void * ) {
    system("wmpoweroff&");
    exit(0);
}

void action_logout(Fl_Widget *, void * ) {
    system("killall X&");
    system("killall Xorg.bin&");
    system("killall labwc&");
    system("killall sway&");
    system("killall weston&");
    exit(0);
}

void action_suspend(Fl_Widget *, void * ) {
    system("pm-suspend&");
    exit(0);
}

void action_reboot(Fl_Widget *, void * ) {
    system("wmreboot&");
    exit(0);
}

void action_quit(Fl_Widget *, void * ) {
    exit(0);
}

Fl_Double_Window * main_window = (Fl_Double_Window * ) 0;

Fl_Button * button_c = (Fl_Button * ) 0;
Fl_Button * button_l = (Fl_Button * ) 0;
Fl_Button * button_r = (Fl_Button * ) 0;
Fl_Button * button_p = (Fl_Button * ) 0;
Fl_Button * button_s = (Fl_Button * ) 0;

int main(int argc, char ** argv) {
    {
        main_window = new Fl_Double_Window(560, 60, "WM Logout");
        main_window -> color(bcolor);
        main_window -> align(Fl_Align(FL_ALIGN_CLIP | FL_ALIGN_INSIDE));
        {
            Fl_Group * o = new Fl_Group(10, 10, 540, 40);
            o -> selection_color((Fl_Color) 41);
            o -> labelsize(16);
            {
                button_c = new Fl_HoverButton(10, 10, 100, 40, "Cancel");
                button_c -> box(FL_FLAT_BOX);
                button_c -> color(bcolor);
                button_c -> labelsize(16);
                button_c -> labelcolor(FL_LIGHT2);
                button_c -> selection_color(bcolor);
                button_c -> callback((Fl_Callback * ) action_quit);
            } // Fl_Button* button_c
            {
                button_l = new Fl_HoverButton(120, 10, 100, 40, "Logout");
                button_l -> box(FL_FLAT_BOX);
                button_l -> color(bcolor);
                button_l -> labelsize(16);
                button_l -> labelcolor(FL_LIGHT2);
                button_l -> selection_color(bcolor);
                button_l -> callback((Fl_Callback * ) action_logout);
            } // Fl_Button* button_l
            {
                button_r = new Fl_HoverButton(230, 10, 100, 40, "Reboot");
                button_r -> box(FL_FLAT_BOX);
                button_r -> color(bcolor);
                button_r -> labelsize(16);
                button_r -> labelcolor(FL_LIGHT2);
                button_r -> selection_color(bcolor);
                button_r -> callback((Fl_Callback * ) action_reboot);
            } // Fl_Button* button_r
            {
                button_p = new Fl_HoverButton(340, 10, 100, 40, "Poweroff");
                button_p -> box(FL_FLAT_BOX);
                button_p -> color(bcolor);
                button_p -> labelsize(16);
                button_p -> labelcolor(FL_LIGHT2);
                button_p -> selection_color(bcolor);
                button_p -> callback((Fl_Callback * ) action_poweroff);
            } // Fl_Button* button_p
            {
                button_s = new Fl_HoverButton(450, 10, 100, 40, "Suspend");
                button_s -> box(FL_FLAT_BOX);
                button_s -> color(bcolor);
                button_s -> labelsize(16);
                button_s -> labelcolor(FL_LIGHT2);
                button_s -> selection_color(bcolor);
                button_s -> callback((Fl_Callback * ) action_suspend);
            } // Fl_Button* button_s
            o -> end();
        } // Fl_Group* o
        main_window -> clear_border();
        main_window -> end();
    } // Fl_Double_Window* main_window
    button_l -> clear_visible_focus();
    button_s -> clear_visible_focus();
    button_r -> clear_visible_focus();
    button_p -> clear_visible_focus();
    button_c -> clear_visible_focus();
    main_window -> show(argc, argv);
    return Fl::run();
}
