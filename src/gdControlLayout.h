#ifndef GDCONCTROLLAYOUT_H
#define GDCONCTROLLAYOUT_H

#include <Godot.hpp>
#include <Control.hpp>
#include <ColorRect.hpp>
#include <Timer.hpp>
#include <Label.hpp>
#include <Sprite.hpp>
#include <OS.hpp>
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
    void set_childs();
    void set_conections();
    bool checkOS();
    void initialize();
    void win();
    void startAll();
    void isMoving(Vector2 position);
    void reset();
    void levelpass(int time);

    template<typename T>
    T* get_child_as(NodePath nodeName){
        return Object::cast_to<T>(get_node(nodeName));
    }
};

}


#endif