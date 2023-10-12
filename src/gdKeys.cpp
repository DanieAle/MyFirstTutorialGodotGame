#include "gdKeys.h"

using namespace godot;

void GDKeys::_register_methods() {
    register_method("_process", &GDKeys::_process);
    register_method("_input", &GDKeys::_input);

}

GDKeys::GDKeys() {
}

GDKeys::~GDKeys() {
}

void GDKeys::_init() {
    // initialize any variables here
    Godot::print("Inicializando GDKeys...");

    Godot::print("Finalizando init GDKeys...");
}

void GDKeys::_process(float delta) {

    
}
void GDKeys::_input(const Ref<InputEvent> event) {
    if (event.is_valid() && event->is_class("InputEventKey")) {
        Ref<InputEventKey> key_event = event;
        
        if (key_event->is_pressed()) {
            int key_code = key_event->get_scancode();
            
            // Realiza acciones en función del código de tecla presionado
            // Realiza acciones específicas para la tecla 'A'
            switch(key_code){
                case 65:
                    Godot::print("Tecla 'A' presionada.");
                    break;
                case 83:
                    Godot::print("Tecla 'S' presionada.");
                    break;
                case 87:
                    Godot::print("Tecla 'W' presionada.");
                    break;
                case 68:
                    Godot::print("Tecla 'D' presionada.");
                    break;
            }
        }
    }
}
