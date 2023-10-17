#include "gdCollisionPlayer.h"

using namespace godot;

void GDCollisionPlayer::_register_methods(){
    register_method("_ready", &GDCollisionPlayer::_ready);
    register_method("_physics_process", &GDCollisionPlayer::_physics_process);
    register_method("_init", &GDCollisionPlayer::_init);
    register_method("_input", &GDCollisionPlayer::_input);
    register_method("_setEnabled", &GDCollisionPlayer::_setEnabled);

    //SIGNAL
    register_signal<GDCollisionPlayer, bool,int,String>((char *)"key_pressed",
        "flip",GODOT_VARIANT_TYPE_BOOL,"direcction",GODOT_VARIANT_TYPE_INT,
        "value_rotation",GODOT_VARIANT_TYPE_INT,"animation", GODOT_VARIANT_TYPE_STRING);
}

GDCollisionPlayer::GDCollisionPlayer(){
}
GDCollisionPlayer::~GDCollisionPlayer(){

}
void GDCollisionPlayer::_ready(){
    Godot::print("Hola");
    set_physics_process(true);
    set_refs(sprite);
    valid_obj_connect(sprite,"key_pressed","_is_movement");
    start_position = get_position();
    enabled = false;
}
void GDCollisionPlayer::_physics_process(float delta){
    //Godot::print("Fisicas ....");
    if(enabled){
        move(delta);
    }
}
void GDCollisionPlayer::_init(){
    Godot::print("Init ....");
    _set_time_passed(0.0);
    _set_speed(200);
    key_h = 0;
    key_v = 0;
}
void GDCollisionPlayer::_input(const Ref<InputEvent> event){
    input_pc(event);
}

void GDCollisionPlayer::move(float delta){
    Vector2 movement(key_h,key_v);
    float speed = _get_speed();
    movement = movement * speed * delta;
    move_and_collide(movement);
}
void GDCollisionPlayer::_setEnabled(bool value){
    enabled = value;
    set_position(start_position);
    key_h = 0;
    key_v = 0;
}
void GDCollisionPlayer::isHorizontal(int num){
    if(num == 65 || num == 68){
        emit_signal("key_pressed", true,key_h,0,"walk");
    }
    else if(num == 83 || num == 87){
        emit_signal("key_pressed", false,key_v,0,"up");
    }
}
void GDCollisionPlayer::myIsPressed(int key_code){
    switch(key_code){
                case 65:
                    //Godot::print("Tecla 'A' presionada.");
                    handleKeyH(false);
                    break;
                case 83:
                    //Godot::print("Tecla 'S' presionada.");
                    handleKeyY(true);
                    break;
                case 87:
                    //Godot::print("Tecla 'W' presionada.");
                    handleKeyY(false);
                    break;
                case 68:
                    //Godot::print("Tecla 'D' presionada.");
                    handleKeyH(true);
                    break;
            }
}
void GDCollisionPlayer::handleKeyH(bool rightOrLeft){
    int left = -1;
    int right = 1;

    if(rightOrLeft){
        key_h = right;
    }
    else{
        key_h = left;
    }
}
void GDCollisionPlayer::handleKeyY(bool rightOrLeft){
    int left = -1;
    int right = 1;
    if(rightOrLeft){
        key_v = right;
    }
    else{
        key_v = left;
    }
}
void GDCollisionPlayer::input_pc(const Ref<InputEvent> event){
    if(enabled){
        if (event.is_valid() && event->is_class("InputEventKey")) {
            key_event = event;
            if (key_event->is_pressed()) {
            int key_code = key_event->get_scancode();
            // Realiza acciones en función del código de tecla presionado
            // Realiza acciones específicas para la tecla 'A'
            myIsPressed(key_code);
            isHorizontal(key_code);
            }
            else if(key_event->is_action_released("tl_h_liberada")){
            key_h = 0;
            }
            else if(key_event->is_action_released("tl_v_liberada")){
            key_v = 0;
            }
        }
    }
}
