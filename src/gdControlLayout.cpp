#include <gdControlLayout.h>

using namespace godot;
void GDControlLayout::_register_methods(){
    register_method("_ready", GDControlLayout::_ready);
    register_method("_init", GDControlLayout::_init);
}
GDControlLayout::GDControlLayout(){}
GDControlLayout::~GDControlLayout(){}

void GDControlLayout::_init(){
}
void GDControlLayout::_ready(){
    size = get_viewport_rect();
    real_t value = 0.3F;
    menu = Object::cast_to<Control>(get_node("Menu"));
    background = Object::cast_to<ColorRect>(get_node("Fondo"));
    background->set_size(size.get_size());
    menu->set_size(size.get_size());
    Vector2 position = {
        size.size.x*value,
        size.size.y*value
    };
    menu->set_position(position);
    Godot::print(menu->get_position());
    Godot::print(size.size);
}