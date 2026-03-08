#include "gdCollisionPlayer.h"

using namespace godot;

void GDCollisionPlayer::_register_methods(){
    register_method("_ready", &GDCollisionPlayer::_ready);
    register_method("_physics_process", &GDCollisionPlayer::_physics_process);
    register_method("_init", &GDCollisionPlayer::_init);
    register_method("_input", &GDCollisionPlayer::_input);
    register_method("_setEnabled", &GDCollisionPlayer::_setEnabled);
    register_method("input_mouse", &GDCollisionPlayer::input_mouse);
    register_method("input_mouse_stop", &GDCollisionPlayer::input_mouse_stop);

    //SIGNAL
    register_signal<GDCollisionPlayer, bool,int,String>((char *)"key_pressed",
        "flip",GODOT_VARIANT_TYPE_BOOL,"direcction",GODOT_VARIANT_TYPE_INT,
        "value_rotation",GODOT_VARIANT_TYPE_INT,"animation", GODOT_VARIANT_TYPE_STRING);
}

void GDCollisionPlayer::_ready(){
    set_physics_process(true);
    Vector2 pos = get_viewport_rect().get_size();
    set_position(pos / 2);
    sprite = get_child_as<Sprite>("Sprite");
    valid_obj_connect(sprite,"key_pressed","_is_movement");
    start_position = get_position();
    enabled = false;
}
void GDCollisionPlayer::_physics_process(float delta){
    if(enabled){
        move(delta);
    }
}
void GDCollisionPlayer::_init(){
    _set_time_passed(0.0);
    _set_speed(200);
    key_h = 0;
    key_v = 0;
}
void GDCollisionPlayer::_input(const Ref<InputEvent> event){
    if (event.is_valid() && event->is_class("InputEventKey")) {
        key_event = event;
        input_pc(key_event);
    }
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
    initStateKeys();
    emit_signal("key_pressed", true,0,0,"walk");
}
void GDCollisionPlayer::isHorizontal(){
    if(left_pressed || right_pressed){
        emit_signal("key_pressed", true,key_h,0,"walk");
    }
    else if(down_pressed || up_pressed){
        emit_signal("key_pressed", false,key_v,0,"up");
    }
}
void GDCollisionPlayer::myIsPressed(int key_code, bool isPressed){
    if(isPressed){
        switch (key_code)
        {
        case 65: left_pressed = true; //A
            break;
        case 68: right_pressed = true; //D
            break;
        case 87: up_pressed = true; //W
            break;
        case 83: down_pressed = true; //S
            break;
        }
    }
    else {
        switch (key_code)
        {
        case 65: left_pressed = false; //A
            break;
        case 68: right_pressed = false; //D
            break;
        case 87: up_pressed = false; //W
            break;
        case 83: down_pressed = false; //S
            break;
        }
    }
}
void GDCollisionPlayer::handleKey(){
    key_h = right_pressed - left_pressed;
    key_v = down_pressed - up_pressed;
}
void GDCollisionPlayer::input_pc(const Ref<InputEventKey> key_event){
    if(enabled){
        int key_code = key_event->get_scancode();
        myIsPressed(key_code, key_event->is_pressed());
        handleKey();
        isHorizontal();
    }
}
void GDCollisionPlayer::initStateKeys(){
    left_pressed = false;
    right_pressed = false;
    up_pressed = false;
    down_pressed = false;
}
void GDCollisionPlayer::input_mouse(Vector2 pos){
    key_h = pos.x;
    key_v = pos.y;
    if(key_h != 0){
        emit_signal("key_pressed", true,key_h,0,"walk");
    }
    else if(key_v != 0){
        emit_signal("key_pressed", false,key_v,0,"up");
    }
}
void GDCollisionPlayer::input_mouse_stop(String response){
    key_h = 0;
    key_v = 0;
}