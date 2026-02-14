#ifndef GDCONCTROLLAYOUT_H
#define GDCONCTROLLAYOUT_H

#include <Godot.hpp>
#include <Control.hpp>
#include <ColorRect.hpp>
namespace godot {

class GDControlLayout : public Control {
    GODOT_CLASS(GDControlLayout, Control)
private:
Rect2 size;
ColorRect *background;
Control *menu;
public:
    static void _register_methods();

    GDControlLayout();
    ~GDControlLayout();

    void _ready();
    void _init();


};

}


#endif