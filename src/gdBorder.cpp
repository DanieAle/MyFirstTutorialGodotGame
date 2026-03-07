#include "gdBorder.h"

using namespace godot;

void GDBorder::_register_methods(){
    register_method("_init", &GDBorder::_init);
    register_method("_ready", &GDBorder::_ready);
    register_method("setup", &GDBorder::setup);

    register_property<GDBorder,int>("Zone",&GDBorder::zone,(int) Zone::NONE,
GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_ENUM,
"TOP,BUTTON,LEFT,RIGHT,NONE");
    register_property<GDBorder,String>("name", &GDBorder::name1 , "n");
}
void GDBorder::_init(){
    Godot::print("Border");
}
void GDBorder::_ready(){
    call_deferred("setup");
}

void GDBorder::setup(){
    Ref<SegmentShape2D> myShape;
    myShape.instance();
    shape = get_child_as<CollisionShape2D>("CollisionShape2D");
    Vector2 size = get_viewport_rect().get_size();
    Vector2 vertical = Vector2(size.x,0);
    Vector2 Horizontal = Vector2(0,size.y);
    int y = size.y * 0.27;
    switch (Zone(zone))
    {
    case Zone::TOP:
        set_position(Vector2(0,0));
        myShape->set_a(vertical);
        break;
    case Zone::BUTTON:
        set_position(Vector2(0,size.y - y));
        myShape->set_a(vertical);
        break;
    case Zone::LEFT:
        set_position(Vector2(0,0));
        shape->set_position(Vector2(size.x,0));
        myShape->set_a(Horizontal);
        break;
    case Zone::RIGHT:
        set_position(Vector2(0,0));
        myShape->set_a(Horizontal);
        break;
    default:
        break;
    }

    shape->set_shape(myShape);
}