#ifndef GDBORDER_H
#define GDBORDER_H

#include <Godot.hpp>
#include <StaticBody2D.hpp>
#include <CollisionShape2D.hpp>
#include <SegmentShape2D.hpp>
#include <Sprite.hpp>
#include <OS.hpp>

namespace godot{

enum class Zone : int {
    TOP,BUTTON,LEFT,RIGHT,NONE
};
class GDBorder : public StaticBody2D {
    GODOT_CLASS(GDBorder, StaticBody2D)
private:
    Vector2 size;
    int zone = (int)Zone::NONE;
    CollisionShape2D *shape;
    String name1;
public:
    static void _register_methods();

    GDBorder() = default;
    ~GDBorder() = default;

    //Defautl methods
    void _ready();
    void _init();
    void setup();
    bool checkOS();

    //New methods
    void valid_obj_connect(Sprite *&sprite, String name_signal, String name_method);
    template<typename T>
    T* get_child_as(NodePath nodeName){
        return Object::cast_to<T>(get_node(nodeName));
    }
};
}
#endif