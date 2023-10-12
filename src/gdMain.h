#ifndef GDMYMAIN_H
#define GDMYMAIN_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <InputEvent.hpp>
#include <InputEventKey.hpp>
#include "Tools.h"

namespace godot {

class GDMyMain : public Sprite {
    GODOT_CLASS(GDMyMain, Sprite)

private:
    float time_passed;
    float speed;
    int key_h;
    int key_v;
    Ref<InputEventKey> key_event;
    struct pila *pressed;
public:
    static void _register_methods();
    void myIsPressed(int key_code);
    void continuePressed(int key);

    GDMyMain();
    ~GDMyMain();

    void _init(); // our initializer called by Godot
    void _input(const Ref<InputEvent>);
    void _process(float delta);
};

}

#endif
