#include "gdCollision.h"

using namespace godot;

//Registro de methodos para godot
void GDCollision::_register_methods(){
    register_method("_setEnabled", &GDCollision::_setEnabled);

    //Registro de Signals
    register_signal<GDCollision, String>((char*)"collision","name",GODOT_VARIANT_TYPE_STRING);
}
GDCollision::GDCollision(){
}
GDCollision::~GDCollision(){

}

//SET
void GDCollision::_set_speed(int value){
    speed = value;
}
void GDCollision::_set_time_passed(int value){
    time_passed = value;
}
void GDCollision::_setEnabled(bool value){
    enabled = true;
}

//GET
int GDCollision::_get_speed(){
    return speed;
}
int GDCollision::_get_time_passed(){
    return time_passed;
}
bool GDCollision::_getEnabled(){
    return enabled;
}

//New methods
void GDCollision::set_refs(Node *obj){
    int i = 0;
    int child_count = get_child_count();
    while(i < child_count){
        Node *node = get_child(i);
        String type_of_class = obj->get_class();
        if(node->is_class(type_of_class)){
            obj = node;
            break;
        }
        i++;
    }
}
void GDCollision::valid_obj_connect(Node *obj,String name_signal,String name_method){
    if(obj){
        connect(name_signal, obj,name_method);
    }

}
void GDCollision::isEnabled_movement(bool value, void  (*func)(bool)){
    if(value){
        func(value);
    }
}