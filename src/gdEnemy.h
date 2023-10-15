#ifndef GDENEMY_H
#define GDENEMY_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <AnimatedSprite.hpp>

namespace godot {

class GDEnemy : public Sprite {
    GODOT_CLASS(GDEnemy, Sprite)
private:
    AnimatedSprite *sprite_animated;
public:
    static void _register_methods();

    GDEnemy();
    ~GDEnemy();

    void _ready();
    void _init();

    void _out_Of_Screen(int direction, int rotation,String animation);
    void resetAnimations();
};
}

#endif