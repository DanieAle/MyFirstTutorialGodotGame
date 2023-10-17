#include "gdController1.h"

using namespace godot;

//Registro de methodos para godot
void GDController::_register_methods(){
    register_method("_ready", &GDController::_ready);
    register_method("_init", &GDController::_init);
    register_method("_input", &GDController::_input);
    register_method("_process", &GDController::_process);
    register_method("set_enabled", &GDController::set_enabled);

    //Registro de Signals
    register_signal<GDController>((char*)"move","pos",GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<GDController,String>((char *)"stop","response",GODOT_VARIANT_TYPE_STRING);
}
GDController::GDController(){
}
GDController::~GDController(){

}
void GDController::_ready(){
    Godot::print("Ready....GDController");
    Vector2 tope = Vector2(30,30);
    max_position = get_position()+tope;
    min_position = get_position()-tope;
    enabled = true;
    Sprite *parent = Object::cast_to<Sprite>(get_parent());
    parent_pos = parent->get_position();
    range_x = parent_pos+tope;
    range_y = parent_pos-tope;
    Godot::print(range_x);
    Godot::print(range_y);
    button_release = false;
    texture1 = ResourceLoader::get_singleton()->load("res://assets/art/joy2.png");
    texture2 = ResourceLoader::get_singleton()->load("res://assets/art/joy2_2.png");
}
void GDController::_init(){
    
}
void GDController::_process(float delta){
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
        if(valid() && button->is_action_pressed("Mouse_click")){
            Vector2 touch_position = mouse->get_position();
            if(is_in_Range(touch_position)){
            new_position(touch_position);
            button_release = false;
            set_texture(texture2);
            send_signal();
            }
        }
        else if(button->is_action_released("Mouse_click") && button->get_button_index() == 1){
            button_release = true;
            set_texture(texture1);
            emit_signal("stop","release");
        }
    }
}
void GDController::_input(Ref<InputEvent> event){
    if(enabled){ 
     if (event.is_valid() && event->is_class("InputEventMouse")) {
        // Este evento es un toque en la pantalla
        mouse = event;
        if(event->is_class("InputEventMouseButton")){
            button = event;

        }
    }
    }
}
//New methods
void GDController::set_refs(Sprite *&sprite) {
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
void GDController::valid_obj_connect(Sprite *&sprite,String name_signal,String name_method){
    if(sprite){
        connect(name_signal, sprite,name_method);
    }

}
void GDController::isOut(){
    Vector2 position = get_position();
    if(position.x > max_position.x || position.y > position.x || position.x < min_position.x  || position.y < min_position.y){
        enabled = false;
    }
}
bool GDController::is_in_Range(Vector2 pos){
    bool inRange = false;
    if(pos.x < range_x.x && pos.x < range_x.y && pos.x > range_y.x && pos.y > range_y.y && pos.y < range_x.y  ){
        inRange = true;
    }
    return inRange;
}
void GDController::new_position(Vector2 pos){
    set_position(pos-parent_pos);

}
int GDController::Operation(int value){
    int response = 0;
    if(value > 0){
        response = value -0.2;
    }
    else if(value < 0){
        response = value +0.2;
    }
    return response;
}
bool GDController::valid(){
    return mouse.is_valid() && button.is_valid();
}

void GDController::send_signal(){
    Vector2 pos = get_position();
    Godot::print(pos);
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
int GDController::normalize(int value){
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
void GDController::set_enabled(bool value){
    enabled = true;
}