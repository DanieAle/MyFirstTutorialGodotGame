#ifndef GDMYMAIN_H
#define GDMYMAIN_H

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

class GDMyMain : public Sprite {
    GODOT_CLASS(GDMyMain, Sprite)

private:
    float time_passed;

public:
    static void _register_methods();

    GDMyMain();
    ~GDMyMain();

    void _init(); // our initializer called by Godot

    void _process(float delta);
};

}

#endif
