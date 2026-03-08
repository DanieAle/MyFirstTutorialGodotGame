#include "gdControllertouch.h"

using namespace godot;

//Registro de methodos para godot
void GDControllerTouch::_register_methods(){
    register_method("_ready", &GDControllerTouch::_ready);
    register_method("_init", &GDControllerTouch::_init);
    register_method("_input", &GDControllerTouch::_input);
    register_method("_process", &GDControllerTouch::_process);

    //Registro de Signals
    register_signal<GDControllerTouch, bool>((char*)"move","pos",GODOT_VARIANT_TYPE_VECTOR2);

    register_property<GDControllerTouch,Ref<Texture>>("Texture_base",&GDControllerTouch::baseTexture,Ref<Texture>(),
GODOT_METHOD_RPC_MODE_DISABLED,GODOT_PROPERTY_USAGE_DEFAULT,GODOT_PROPERTY_HINT_RESOURCE_TYPE,"Texture");
    register_property<GDControllerTouch,Ref<Texture>>("Texture_press",&GDControllerTouch::pressTexture,Ref<Texture>(),
GODOT_METHOD_RPC_MODE_DISABLED,GODOT_PROPERTY_USAGE_DEFAULT,GODOT_PROPERTY_HINT_RESOURCE_TYPE,"Texture");
}
void GDControllerTouch::_ready(){
    Vector2 tope = Vector2(30,30);
    base = Object::cast_to<Control>(get_parent());
    ring = Object::cast_to<Sprite>(base->get_node("Ring"));
    android = checkOS();
}
void GDControllerTouch::_init(){}
void GDControllerTouch::_process(float delta){
    if(button_release){ 
        getSpriteback();
    }
    if(active){
        move();
    }
}
void GDControllerTouch::_input(Ref<InputEvent> event){
    if(android){
    if (event.is_valid() && event->is_class("InputEventScreenTouch")) {
        //toque en la pantalla
        Ref<InputEventScreenTouch> touch = event;
        if(touch->is_pressed()){
            isInRange(touch);
        }
        else if(!touch->is_pressed()){
            release();
        }
    }
}
}

bool GDControllerTouch::checkOS(){
    String os = OS::get_singleton()->get_name();
    return os == "Android";
}

int GDControllerTouch::Operation(int value){
    return value > 0 ? value - 0.2 : value + 0.2;
}

void GDControllerTouch::move(){
    if(!active) return;
    Vector2 mouse_local = base->get_local_mouse_position();

    if(mouse_local.length() > max_radius){
        mouse_local = mouse_local.normalized() * max_radius;
    }
    set_position(mouse_local);
    ring->set_visible(isMaxRange(mouse_local.length()));

    send_signal();
}
void GDControllerTouch::send_signal(){
    Vector2 pos = get_position().normalized();

    emit_signal("move",get_direction(pos));
}
Vector2 GDControllerTouch::get_direction(Vector2 pos){
    int direction_x = 0;
    int direction_y = 0;
    if(pos.x > 0.5) direction_x = 1;
    else if(pos.x < -0.1) direction_x = -1;

    if(pos.y > 0.5) direction_y = 1;
    else if(pos.y < -0.1) direction_y = -1;

    return Vector2(direction_x,direction_y);
}
void GDControllerTouch::isInRange(Ref<InputEventScreenTouch> touch){
    Vector2 center_stick = base->get_global_position() + base->get_size() / 1.0;
    Vector2 local_pos = touch->get_position() - center_stick;
    if(local_pos.length() <= max_radius){
        active = true;
        set_texture(pressTexture);
                
    }
    button_release = false;
}
void GDControllerTouch::release(){
    active = false;
    button_release = true;
    ring->set_visible(false);
    set_texture(baseTexture);
    emit_signal("move",Vector2(0,0));
}
void GDControllerTouch::getSpriteback(){
    int x = 0;
    int y = 0;
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
bool GDControllerTouch::isMaxRange(float_t value){
    return (value > max_radius-1) ? true : false;
}