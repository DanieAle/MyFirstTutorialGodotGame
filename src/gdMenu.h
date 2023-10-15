#ifndef GDMENU_H
#define GDMENU_H

#include <Godot.hpp>
#include <Control.hpp>
#include <Button.hpp>
#include <Label.hpp>
#include <Timer.hpp>

namespace godot {

class GDMenu : public Control {
    GODOT_CLASS(GDMenu, Control)
private:
    BaseButton *button;
    Label *myLabel;
    String myTitles[3] = {"Dodge the creeps!","Get Ready!","Game Over"};
    Timer *myTimer;
    Timer *myTimer2;
public:
    static void _register_methods();

    GDMenu();
    ~GDMenu();

    void _ready();
    void _init();
    
    void _button_down();
    void _time_end();
    void _game_Over();
    void _restart();
};

}


#endif