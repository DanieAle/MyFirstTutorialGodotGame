#ifndef GDCOLLISION_H
#define GDCOLLISION_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>

namespace godot{

class GDCollision : public KinematicBody2D {
    GODOT_CLASS(GDCollision, KinematicBody2D)
private:
    float time_passed;
    float speed;
    bool enabled;
public:
    static void _register_methods();

    GDCollision();
    ~GDCollision();

    //Defautl methods

    //set_methods
    void _set_speed(int value);
    void _set_time_passed(int value);
    void _setEnabled(bool value);
    //get_methods
    int _get_speed();
    int _get_time_passed();
    bool _getEnabled();
    //Event methods

    //New methods
    //void set_refs(Node *obj);
    //void valid_obj_connect(Node *obj,String name_signal, String name_method);
};
}

#endif