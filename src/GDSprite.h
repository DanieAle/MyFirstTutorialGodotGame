#ifndef GDSPRITE_H
#define GDSPRITE_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <GDNodeBase.h>
#include <AnimatedSprite.hpp>

namespace godot {

class GDSprite : public Sprite {
    GODOT_CLASS(GDSprite, Sprite)
private:
    AnimatedSprite *sprite_animated;
    GDNodeBase *base;
public:
    static void _register_methods();

    GDSprite();
    ~GDSprite();

    void _ready();

    void _is_movement(bool flip, int direcction,int value_rotation);
    void flipHorizontal(int direcction);
    void flipVertical(int direcction);
    void rotation(int rot);
};

}

#endif