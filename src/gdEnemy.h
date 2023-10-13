#ifndef GDENEMY_H
#define GDENEMY_H

#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

class GDEnemy : public Sprite {
    GODOT_CLASS(GDEnemy, Sprite)
private:
    float speed;
public:
    static void _register_methods();

    GDEnemy();
    ~GDEnemy();

    void _ready();
    void _init();
    void _process(float delta);
};

}


#endif