#include "gdCollision.h"

using namespace godot;

//Registro de methodos para godot
void GDCollision::_register_methods(){
    register_method("_ready", &GDCollision::_ready);
    register_method("_init", &GDCollision::_init);
    register_method("_setEnabled", &GDCollision::_setEnabled);

    //Registro de Signals
    register_signal<GDCollision, String>((char*)"collision","name",GODOT_VARIANT_TYPE_STRING);
}
GDCollision::GDCollision(){
}
GDCollision::~GDCollision(){

}
void GDCollision::_ready(){
    Godot::print("Ready....GDCollision");
}
void GDCollision::_init(){
    
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
void GDCollision::set_refs(Sprite *&sprite) {
    int i = 0;
    int child_count = get_child_count();
    Godot::print(String::num(child_count));
    while (i < child_count) {
        //Node *node = get_child(i);
        if (get_child(i)->is_class("Sprite")) {
            sprite = Object::cast_to<Sprite>(get_child(i));
            break;
        }
        i++;
    }
}
void GDCollision::valid_obj_connect(Sprite *&sprite,String name_signal,String name_method){
    if(sprite){
        connect(name_signal, sprite,name_method);
    }

}