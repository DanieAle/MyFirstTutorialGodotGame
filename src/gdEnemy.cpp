#include "gdEnemy.h"

using namespace godot;

void GDEnemy:: _register_methods(){
    register_method("_ready", &GDEnemy::_ready);
    register_method("_init", &GDEnemy::_init);
    register_method("_out_Of_Screen", &GDEnemy::_out_Of_Screen);

}

GDEnemy::GDEnemy(){
}
GDEnemy::~GDEnemy(){

}

void GDEnemy::_ready(){
    Godot::print("Ready");
    sprite_animated = Object::cast_to<AnimatedSprite>(get_child(get_child_count()-1));
}

void GDEnemy::_init(){
    Godot::print("Init");
}

void GDEnemy::_out_Of_Screen(int direccion, int rotation,String animation){
    resetAnimations();
    sprite_animated->set_rotation_degrees(rotation);
    if(direccion < 0){
        sprite_animated->set_flip_h(true);
    }
    sprite_animated->play(animation);
}
void GDEnemy::resetAnimations(){
    sprite_animated->set_flip_h(false);
    sprite_animated->set_flip_v(false);
    sprite_animated->set_rotation_degrees(0);
}