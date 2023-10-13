#ifndef GDMYMAIN_H
#define GDMYMAIN_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <InputEvent.hpp>
#include <InputEventKey.hpp>
#include <AnimatedSprite.hpp>

namespace godot {

class GDMyMain : public Sprite {
    GODOT_CLASS(GDMyMain, Sprite)
private:
    float time_passed;
    float speed;
    int key_h;
    int key_v;
    Ref<InputEventKey> key_event;
    AnimatedSprite *sprite_animated;
    String name;
public:
    static void _register_methods();

    GDMyMain();
    ~GDMyMain();

    void _ready();
    void _init(); // our initializer called by Godot
    void _input(const Ref<InputEvent>);
    void _process(float delta);
    void handleKeyH(bool rightOrLeft);
    void handleKeyY(bool rightOrLeft);
    void myIsPressed(int key_code);
};

}

#endif
