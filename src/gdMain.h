#ifndef GDMYMAIN_H
#define GDMYMAIN_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <AnimatedSprite.hpp>

namespace godot {

class GDMyMain : public Sprite {
    GODOT_CLASS(GDMyMain, Sprite)
private:
    int key_h;
    int key_v;
    AnimatedSprite *sprite_animated;
    String name;
public:
    static void _register_methods();

    GDMyMain();
    ~GDMyMain();

    void _ready();
    void _init(); // our initializer called by Godot
    void handleKeyH(int direction);
    void _on_key_pressed(bool isPressed,int direction);
};

}

#endif
