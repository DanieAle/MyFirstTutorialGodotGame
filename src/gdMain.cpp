#include "gdMain.h"

using namespace godot;

void GDMyMain::_register_methods() {
    register_method("_process", &GDMyMain::_process);
    register_method("_input", &GDMyMain::_input);

    register_property<GDMyMain, float>("speed", &GDMyMain::speed, 20.0);
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
    speed = 50.0;
    key_h = 0;
    key_v = 0;
    Godot::print("Finalizando init GDMyMain...");
}

void GDMyMain::_process(float delta) {
    //Godot::print("Entrando a _process...GDMyMain");
    Vector2 movement(0,0);

    if(key_h != 0 && key_v != 0){
        movement += Vector2(key_h,key_v);
    }
    else if(key_v != 0){
        movement.y += key_v;
    }
    else if(key_h != 0){
        movement.x += key_h;
    }

    movement = movement.normalized() * speed * delta;
    
    // Aplica el movimiento a la posición actual.
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
    }
}
void GDMyMain::myIsPressed(int key_code){
    switch(key_code){
                case 65:
                    Godot::print("Tecla 'A' presionada.");
                    key_h = -1;
                    break;
                case 83:
                    Godot::print("Tecla 'S' presionada.");
                    key_v = 1;
                    break;
                case 87:
                    Godot::print("Tecla 'W' presionada.");
                    key_v =-1;
                    break;
                case 68:
                    Godot::print("Tecla 'D' presionada.");
                    key_h = 1;
                    break;
            }
}
void GDMyMain::continuePressed(int key){
    switch (key != 0)
    {
    case false:
        break;
    
    default:
        break;
    }
}
