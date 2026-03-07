#ifndef GDCOLLISION_H
#define GDCOLLISION_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Sprite.hpp>

namespace godot{

class GDCollision : public KinematicBody2D {
    GODOT_CLASS(GDCollision, KinematicBody2D)
private:
    float time_passed;
    float speed;
    bool enabled;
public:
    static void _register_methods();

    GDCollision() = default;
    ~GDCollision() = default;

    //Defautl methods
    void _ready();
    void _init();
    //set_methods
    void _set_speed(int value);
    void _set_time_passed(int value);
    //get_methods
    int _get_speed();
    int _get_time_passed();
    bool _getEnabled();
    //Event methods

    //New methods
    void valid_obj_connect(Sprite *&sprite, String name_signal, String name_method);
    template<typename T>
    T* get_child_as(NodePath nodeName){
        return Object::cast_to<T>(get_node(nodeName));
    }
};
}

#endif