#include "gdEnemy.h"

using namespace godot;

void GDEnemy:: _register_methods(){
    register_method("_ready", &GDEnemy::_ready);
    register_method("_init", &GDEnemy::_init);
    register_method("_process", &GDEnemy::_process);

    register_property<GDEnemy, float>("speed", &GDEnemy::speed,300.0);
}

GDEnemy::GDEnemy(){

}
GDEnemy::~GDEnemy(){

}

void GDEnemy::_ready(){

    set_position(Vector2(0,250));
}

void GDEnemy::_init(){

}

void GDEnemy::_process(float delta){
    Vector2 posicion = Vector2(get_position().x+1,250);
    set_position(posicion);
}