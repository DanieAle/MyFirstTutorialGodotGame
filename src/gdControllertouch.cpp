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
    Sprite *parent = Object::cast_to<Sprite>(get_parent());
    parent_pos = parent->get_position();
    parent_scale = parent->get_scale();
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
            //toque en la pantalla
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
bool GDControllerTouch::is_in_Range(float distance){
    return distance < 60;
}
void GDControllerTouch::new_position(Vector2 pos){
    Vector2 position = pos-parent_pos;
    float x = position.x/parent_scale.x;
    float y = position.y/parent_scale.y;
    set_position(Vector2(x,y));
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
void GDControllerTouch::set_enabled(bool value){
    enabled = true;
}

void GDControllerTouch::move(){
    Vector2 position = mouse->get_position();
    float x1 = parent_pos.x;
    float x2 = position.x;

    float y1 = parent_pos.y;
    float y2 = position.y;

    float distance = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    if(is_in_Range(distance)){
        new_position(position);
        button_release = false;
        set_texture(texture2);
        send_signal();
    }
}
void GDControllerTouch::send_signal(){
    Vector2 pos = get_position();
    int x = 0;
    int y = 0;
    float diagonal = sqrt(pow(pos.x,2)+pow(pos.y,2));
    float angle = acos(pos.y/diagonal);
    float angle_degree = convert_degree(angle);
    Vector2 direction = get_direction(pos);

    if(angle_degree < 115 && angle_degree > 90){
        x = 1;
        x = x *direction.x;
    }
    else if(angle_degree > 160 || angle_degree < 30){
        y = 1 * direction.y;

    }
    else{
        x = 1 * direction.x;
        y = 1 * direction.y;
    }
    emit_signal("move",Vector2(x,y));
}
float GDControllerTouch::convert_degree(float angle){
    //return angle * 180/M_PI;
    return angle * 180/3.14;
}
Vector2 GDControllerTouch::get_direction(Vector2 pos){
    int direction_x = 1;
    int direction_y = 1;
    if(pos.x < 0){
        direction_x = -1;
    }
    if(pos.y < 0){
        direction_y = -1;
    }
    return Vector2(direction_x,direction_y);
}