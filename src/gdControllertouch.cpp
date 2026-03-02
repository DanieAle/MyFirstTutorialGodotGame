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
void GDControllerTouch::_ready(){
    Godot::print("Ready....GDControllerTouch");
    Vector2 tope = Vector2(30,30);
    Sprite *parent = Object::cast_to<Sprite>(get_parent());
    base = Object::cast_to<Node2D>(get_parent());
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
        if(active){
            move();
        }
        /*else if(!button->is_pressed()){
            button_release = true;
            set_texture(texture1);
            emit_signal("stop","release");
        }*/
    }

}
void GDControllerTouch::_input(Ref<InputEvent> event){
    if (event.is_valid() && event->is_class("InputEventScreenTouch")) {
        //toque en la pantalla
        Ref<InputEventScreenTouch> touch = event;
        if(touch->is_pressed()){
            Vector2 local_pos = base->to_local(touch->get_position());
            if(local_pos.length() <= 50){
                active = true;
                set_texture(texture2);
                
            }
        }
        else {
            active = false;
            button_release = true;
            set_texture(texture1);
            emit_signal("stop", "release");
        }
    }
    if(event.is_valid() && event->is_class("InputEventScreenDrag")){
        mouse = event;
    }
    
}
bool GDControllerTouch::is_in_Range(float distance){
    return distance < 60;
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
    if(!active) return;
    Vector2 mouse_local = base->get_local_mouse_position();

    float max_radius = 60.0;
    if(mouse_local.length() > max_radius){
        mouse_local = mouse_local.normalized() * max_radius;
    }
    if(mouse_local.length() < 30){
    set_position(mouse_local);

    //send_signal();
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
    int direction_x = pos.x < 0 ? -1 : 1;
    int direction_y = pos.y < 0 ? -1 : 1;

    return Vector2(direction_x,direction_y);
}