#include "gdColision.h"

using namespace godot;

void GDColision:: _register_methods(){
    register_method("_ready", &GDColision::_ready);
    register_method("_physics_process", &GDColision::_physics_process);
    register_method("_init", &GDColision::_init);
    register_method("_input", &GDColision::_input);
    register_method("_setEnabled", &GDColision::_setEnabled);
    
    register_property<GDColision, bool>("player", &GDColision::player, false);

    register_signal<GDColision, bool>((char *)"key_pressed",
        "isPressed",GODOT_VARIANT_TYPE_BOOL,"direction",GODOT_VARIANT_TYPE_INT);
    register_signal<GDColision, String>((char*)"collision","name",GODOT_VARIANT_TYPE_STRING);
}

GDColision::GDColision(){
}
GDColision::~GDColision(){

}

void GDColision::_ready(){
    Godot::print("Ready...GDColision");
    set_physics_process(true);
    int64_t index = 0;
    sprite = Object::cast_to<Sprite>(get_child(index)); // Cambia "path_to_sprite" al camino real en tu escena
    if (sprite) {
        connect("key_pressed", sprite, "_on_key_pressed");
    }
    /*myParent = get_parent();
    if(myParent){
        //connect("collision",myParent,"_is_dead");
    }*/
    connect("collision",get_parent(), "_is_dead");
    start_position = get_position();
    body_enabled = false;
}

void GDColision::_physics_process(float delta){
    //Godot::print("Fisicas ....");
    isEnabled_movement(delta);
}
void GDColision::_init(){
    Godot::print("Init ....");
    time_passed = 0.0;
    speed = 300.0;
    key_h = 0;
    key_v = 0;
}
void GDColision::_input(const Ref<InputEvent> event) {
    if(body_enabled){
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
void GDColision::handleKeyH(bool rightOrLeft){
    int left = -1;
    int right = 1;

    if(rightOrLeft){
        key_h = right;
        //sprite_animated->set_flip_h(false);
    }
    else{
        key_h = left;
        //sprite_animated->set_flip_h(true);
    }
}
void GDColision::handleKeyY(bool rightOrLeft){
    int left = -1;
    int right = 1;
    if(rightOrLeft){
        key_v = right;
        //sprite_animated->set_flip_v(true);
    }
    else{
        key_v = left;
        //sprite_animated->set_flip_v(false);
    }
}
void GDColision::myIsPressed(int key_code){
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
void GDColision::isHorizontal(int num){
    if(num == 65 || num == 68){
        emit_signal("key_pressed", true,key_h);
    }
    else if(num == 83 || num == 87){
        emit_signal("key_pressed", false);
    }
}
void GDColision::isEnabled_movement(float delta){
    if(body_enabled){
        Vector2 movement(key_h,key_v);
        movement = movement * speed * delta;
        Ref<KinematicCollision2D> collision = move_and_collide(movement);
        if(collision.is_valid()){
    // Ahora puedes usar esta información según tus necesidades.
            String nombre = collision->get_collider()->get_class();
        //Godot::print("Colisión con: " + nombre);
            emit_signal("collision",nombre);
    // Por ejemplo, verifica el nombre del nodo con el que colisionó.
        }
    }

}
void GDColision::_setEnabled(bool value){
    body_enabled = value;
    set_position(start_position);
}