#include "gdMain.h"

using namespace godot;

void GDMyMain::_register_methods() {
    register_method("_process", &GDMyMain::_process);
    register_method("_input", &GDMyMain::_input);
    register_method("_ready", &GDMyMain::_ready);

    register_property<GDMyMain, float>("speed", &GDMyMain::speed, 300.0);

    register_signal<GDMyMain>((char *)"key_pressed","node",GODOT_VARIANT_TYPE_OBJECT,"new_pose",GODOT_VARIANT_TYPE_VECTOR2);
}

GDMyMain::GDMyMain() {
    
}

GDMyMain::~GDMyMain() {
    // add your cleanup here
}

void GDMyMain::_init() {
    // initialize any variables here
    Godot::print("Inicializando GDMyMain...");
    time_passed = 0.0;
    speed = 300.0;
    key_h = 0;
    key_v = 0;
    //sprite_animated = get_node<AnimatedSprite>("/root/Main/Body2d/Sprite/AnimatedSpritePlayer");
    //Godot::print(name);
    Godot::print("Finalizando init GDMyMain...");
}
void GDMyMain::_ready() {
    sprite_animated = get_node<AnimatedSprite>("/root/Main/PlayerBody2d/Sprite/AnimatedSpritePlayer");
    // Realiza inicializaciones aquí.
}

void GDMyMain::_process(float delta) {
    //Godot::print("Entrando a _process...GDMyMain");
    //Godot::print(get_path());
    Vector2 movement(key_h,key_v);

    movement = movement * speed * delta;
    
    // Aplica el movimiento a la posición actual.
    if(key_v != 0){
        sprite_animated->play("up");
    }
    else if(key_h != 0){
        sprite_animated->play("walk");
    }
    
    set_position(get_position() + movement);
}

void GDMyMain::_input(const Ref<InputEvent> event) {
    if (event.is_valid() && event->is_class("InputEventKey")) {
        key_event = event;
        if (key_event->is_pressed()) {
            int key_code = key_event->get_scancode();
            // Realiza acciones en función del código de tecla presionado
            // Realiza acciones específicas para la tecla 'A'
            myIsPressed(key_code);
        }
        else if(key_event->is_action_released("tl_h_liberada")){
            key_h = 0;
        }
        else if(key_event->is_action_released("tl_v_liberada")){
            key_v = 0;
        }
    }
}
void GDMyMain::handleKeyH(bool rightOrLeft){
    int left = -1;
    int right = 1;

    if(rightOrLeft){
        key_h = right;
        sprite_animated->set_flip_h(false);
    }
    else{
        key_h = left;
        sprite_animated->set_flip_h(true);
    }
}
void GDMyMain::handleKeyY(bool rightOrLeft){
    int left = -1;
    int right = 1;
    if(rightOrLeft){
        key_v = right;
        sprite_animated->set_flip_v(true);
    }
    else{
        key_v = left;
        sprite_animated->set_flip_v(false);
    }
}
void GDMyMain::myIsPressed(int key_code){
    switch(key_code){
                case 65:
                    Godot::print("Tecla 'A' presionada.");
                    handleKeyH(false);
                    break;
                case 83:
                    Godot::print("Tecla 'S' presionada.");
                    handleKeyY(true);
                    break;
                case 87:
                    Godot::print("Tecla 'W' presionada.");
                    handleKeyY(false);
                    break;
                case 68:
                    Godot::print("Tecla 'D' presionada.");
                    handleKeyH(true);
                    break;
            }
}