#include "GDSprite.h"

using namespace godot;

void GDSprite::_register_methods() {
    register_method("_ready", &GDSprite::_ready);
    register_method("_init", &GDSprite::_init);
    register_method("_is_movement", &GDSprite::_is_movement);


}
void GDSprite::_ready() {
    //sprite_animated = Object::cast_to<AnimatedSprite>(get_child(get_child_count()-1));
    // Realiza inicializaciones aquí.
    //set_refs();
    sprite_animated = get_child_as<AnimatedSprite>("AnimatedSpritePlayer");
}
void GDSprite::_init(){}
void GDSprite::_is_movement(bool flip,int direcction,int value_rotation,String animation){
    sprite_animated->play(animation);
    sprite_animated->set_flip_h(false);
    sprite_animated->set_flip_v(false);
    sprite_animated->set_rotation_degrees(0);
    if(flip){
        flipHorizontal(direcction);
    }
    else{
        flipVertical(direcction);
    }
    rotation(value_rotation);
}
void GDSprite::flipHorizontal(int direcction){
    if(direcction > 0){
        sprite_animated->set_flip_h(false);
    }
    else{
        sprite_animated->set_flip_h(true);
    }
}
void GDSprite::flipVertical(int direcction){
    if(direcction < 0){
        sprite_animated->set_flip_v(false);
    }
    else{
        sprite_animated->set_flip_v(true);
    }
}
void GDSprite::rotation(int value){
    if(value != 0){
        sprite_animated->set_rotation_degrees(value);
    }
}
