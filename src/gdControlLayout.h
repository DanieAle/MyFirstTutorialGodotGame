#ifndef GDCONCTROLLAYOUT_H
#define GDCONCTROLLAYOUT_H

#include <Godot.hpp>
#include <Control.hpp>
#include <ColorRect.hpp>
#include <Timer.hpp>
#include <Label.hpp>
#include <Sprite.hpp>

namespace godot {

class GDControlLayout : public Control {
    GODOT_CLASS(GDControlLayout, Control)
private:
Rect2 size;
ColorRect *background;
Control *menu;
Sprite *myStick;
Label *contador;
Timer *tContador;
int lastTime = 0;
public:
    static void _register_methods();

    GDControlLayout() = default;
    ~GDControlLayout() = default;

    void _ready();
    void _init();
    void _process(float delta);
    void initialize(bool play);
    void win();
    void isMoving(Vector2 position);
    void reset();
};

}


#endif