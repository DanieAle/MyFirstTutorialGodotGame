#include "gdMain.h"

using namespace godot;

void GDMyMain::_register_methods() {
    register_method("_ready", &GDMyMain::_ready);
    register_method("_on_key_pressed", &GDMyMain::_on_key_pressed);


}

GDMyMain::GDMyMain() {
    
}

GDMyMain::~GDMyMain() {
    // add your cleanup here
}

void GDMyMain::_init() {
    // initialize any variables here
    Godot::print("Inicializando GDMyMain...");
    key_h = 0;
    key_v = 0;
    Godot::print("Finalizando init GDMyMain...");
}
void GDMyMain::_ready() {
    sprite_animated = Object::cast_to<AnimatedSprite>(get_child(get_child_count()-1));
    // Realiza inicializaciones aquí.
}


void GDMyMain::handleKeyH(int direction){
    if(direction > 0){
        sprite_animated->set_flip_h(false);
    }
    else{
        sprite_animated->set_flip_h(true);
    }
}
void GDMyMain::_on_key_pressed(bool isPressed,int direction){
    //Godot::print("Señal en MyMain obtenida");
    if(isPressed){
        sprite_animated->play("walk");
        handleKeyH(direction);
    }
    else{
        sprite_animated->play("up");
    }
}