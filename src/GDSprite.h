#ifndef GDSPRITE_H
#define GDSPRITE_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <AnimatedSprite.hpp>

namespace godot {

class GDSprite : public Sprite {
    GODOT_CLASS(GDSprite, Sprite)
private:
    AnimatedSprite *sprite_animated;
public:
    static void _register_methods();

    GDSprite() = default;
    ~GDSprite() = default;

    void _ready();
    void _init();

    void _is_movement(bool flip, int direcction,int value_rotation,String animation);
    void flipHorizontal(int direcction);
    void flipVertical(int direcction);
    void rotation(int rot);
    template<typename T>
    T* get_child_as(NodePath nodeName){
        return Object::cast_to<T>(get_node(nodeName));
    }
};

}

#endif