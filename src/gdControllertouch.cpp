#include "gdControllertouch.h"

using namespace godot;

//Registro de methodos para godot
void GDControllerTouch::_register_methods(){
    register_method("_ready", &GDControllerTouch::_ready);
    register_method("_init", &GDControllerTouch::_init);
    register_method("_input", &GDControllerTouch::_input);
    register_method("_process", &GDControllerTouch::_process);

    //Registro de Signals
    register_signal<GDControllerTouch>((char*)"move","pos",GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<GDControllerTouch,String>((char *)"stop","response",GODOT_VARIANT_TYPE_STRING);
}
void GDControllerTouch::_ready(){
    Godot::print("Ready....GDControllerTouch");
    Vector2 tope = Vector2(30,30);
    Sprite *parent = Object::cast_to<Sprite>(get_parent());
    base = Object::cast_to<Node2D>(get_parent());
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
        if(position != Vector2(0,0)){
            Vector2 reducir;
            if(position.x != 0 || position.y != 0){
            x = Operation(position.x);
            y = Operation(position.y);
            }
            reducir = Vector2(x,y);
            set_position(reducir);
        }
        else button_release = false;
    }
    if(active){
        move();
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
            button_release = false;
        }
        else if(!touch->is_pressed()){
            active = false;
            button_release = true;
            set_texture(texture1);
            emit_signal("stop", "release");
        }
    }
    if(event.is_valid() && event->is_class("InputEventScreenDrag")){
       
    }
    
}

int GDControllerTouch::Operation(int value){
    return value > 0 ? value - 0.2 : value + 0.2;
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
    Vector2 pos = get_position().normalized();

    emit_signal("move",get_direction(pos));
}
Vector2 GDControllerTouch::get_direction(Vector2 pos){
    int direction_x = pos.x < 0 ? -1 : 1;
    int direction_y = pos.y < 0 ? -1 : 1;

    return Vector2(direction_x,direction_y);
}