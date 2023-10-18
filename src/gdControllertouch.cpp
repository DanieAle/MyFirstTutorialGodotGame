#include "gdControllertouch.h"

using namespace godot;

//Registro de methodos para godot
void GDControllerTouch::_register_methods(){
    register_method("_ready", &GDControllerTouch::_ready);
    register_method("_init", &GDControllerTouch::_init);
    register_method("_input", &GDControllerTouch::_input);
    register_method("_process", &GDControllerTouch::_process);
    register_method("set_enabled", &GDControllerTouch::set_enabled);

    //Registro de Signals
    register_signal<GDControllerTouch>((char*)"move","pos",GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<GDControllerTouch,String>((char *)"stop","response",GODOT_VARIANT_TYPE_STRING);
}
GDControllerTouch::GDControllerTouch(){
}
GDControllerTouch::~GDControllerTouch(){

}
void GDControllerTouch::_ready(){
    Godot::print("Ready....GDControllerTouch");
    Vector2 tope = Vector2(30,30);
    max_position = get_position()+tope;
    min_position = get_position()-tope;
    enabled = true;
    Sprite *parent = Object::cast_to<Sprite>(get_parent());
    parent_pos = parent->get_position();
    range_x = parent_pos+tope;
    range_y = parent_pos-tope;
    button_release = false;
    texture1 = ResourceLoader::get_singleton()->load("res://assets/art/joy2.png");
    texture2 = ResourceLoader::get_singleton()->load("res://assets/art/joy2_2.png");
}
void GDControllerTouch::_init(){
    
}
void GDControllerTouch::_process(float delta){
    int x = 0;
    int y = 0;
    if(button_release){ 
        Vector2 position = get_position();
        Vector2 reducir;
        if(position.x != 0 || position.y != 0){
            x = Operation(position.x);
            y = Operation(position.y);
        }
        reducir = Vector2(x,y);
        set_position(reducir);
    }
    if(valid()){
        if(button->is_pressed()){
            move();
        }
        else if(!button->is_pressed()){
            button_release = true;
            set_texture(texture1);
            emit_signal("stop","release");
        }
    }

}
void GDControllerTouch::_input(Ref<InputEvent> event){
    if(true){ 
        if (event.is_valid() && event->is_class("InputEventScreenTouch")) {
        // Este evento es un toque en la pantalla
        button = event;
        }
        if(event.is_valid() && event->is_class("InputEventScreenDrag")){
        mouse = event;
        }
    }
}
//New methods
void GDControllerTouch::set_refs(Sprite *&sprite) {
    int i = 0;
    int child_count = get_child_count();
    while (i < child_count) {
        //Node *node = get_child(i);
        if (get_child(i)->is_class("Sprite")) {
            sprite = Object::cast_to<Sprite>(get_child(i));
            break;
        }
        i++;
    }
}
void GDControllerTouch::valid_obj_connect(Sprite *&sprite,String name_signal,String name_method){
    if(sprite){
        connect(name_signal, sprite,name_method);
    }

}
void GDControllerTouch::isOut(){
    Vector2 position = get_position();
    if(position.x > max_position.x || position.y > position.x || position.x < min_position.x  || position.y < min_position.y){
        enabled = false;
    }
}
bool GDControllerTouch::is_in_Range(Vector2 pos){
    bool inRange = false;
    if(pos.x < range_x.x && pos.x < range_x.y && pos.x > range_y.x && pos.y > range_y.y && pos.y < range_x.y  ){
        inRange = true;
    }
    return inRange;
}
void GDControllerTouch::new_position(Vector2 pos){
    set_position(pos-parent_pos);

}
int GDControllerTouch::Operation(int value){
    int response = 0;
    if(value > 0){
        response = value -0.2;
    }
    else if(value < 0){
        response = value +0.2;
    }
    return response;
}
bool GDControllerTouch::valid(){
    return button.is_valid() && mouse.is_valid();
}

void GDControllerTouch::send_signal(){
    Vector2 pos = get_position();
    int x = 0;
    int y = 0;
    if(pos.x > 10 && pos.y < 15){
        x = 1;
    }
    else if(pos.x < -10 && pos.y > -15){
        x = -1;
    }
    else{
        if(pos.y > 10 && pos.x < 15){
        y = 1;
    }
    else if(pos.y > -10 && pos.x < -15){
        y = -1;
    }
    else{
        if (abs(pos.x) < 30) {
        x = (pos.x > 0) ? 1 : -1;
        }
        if (abs(pos.y) > -30) {
        y = (pos.y > 0) ? 1 : -1;
        }
    }

    }
    emit_signal("move",Vector2(x,y));
}
int GDControllerTouch::normalize(int value){
    int response = 0;
    if(value <= 30 && value >= 15){
        response = 1;
    }
    else if(value >= -30 && value <= -15){
        response = -1;
    }
    else response = 0;
    return response;
}
void GDControllerTouch::set_enabled(bool value){
    enabled = true;
}
void GDControllerTouch::move(){
    Vector2 touch_position = mouse->get_position();
    if(is_in_Range(touch_position)){
        new_position(touch_position);
        button_release = false;
        set_texture(texture2);
        send_signal();
    }
}
