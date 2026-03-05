#ifndef GDMENUTOUCH_H
#define GDMENUTOUCH_H

#include <Godot.hpp>
#include <Control.hpp>
#include <TouchScreenButton.hpp>
#include <Label.hpp>
#include <Timer.hpp>
#include <InputEvent.hpp>

namespace godot {

class GDMenuTouch : public Control {
    GODOT_CLASS(GDMenuTouch, Control)
private:
    TouchScreenButton *button;
    Label *myLabel;
    String myTitles[3] = {"Dodge the creeps!","Get Ready!","Game Over"};
    Timer *myTimer;
public:
    static void _register_methods();

    GDMenuTouch();
    ~GDMenuTouch();

    void _ready();
    void _init();
    void _process(float delta);

    void _button_down();
    void _time_end();
    void _restart();
};

}


#endif