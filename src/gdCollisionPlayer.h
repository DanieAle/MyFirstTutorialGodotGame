#ifndef GDCOLLISIONPLAYER_H
#define GDCOLLISIONPLAYER_H

#include <Godot.hpp>
#include "gdCollision.h"
#include <KinematicCollision2D.hpp>
#include <InputEvent.hpp>
#include <InputEventKey.hpp>
#include <Sprite.hpp>
#include <GDNodeBase.h>

namespace godot{

class GDCollisionPlayer : public GDCollision {
    GODOT_CLASS(GDCollisionPlayer, GDCollision)

private:
    Vector2 start_position;
    int key_h;
    int key_v;
    Ref<InputEventKey> key_event;
    Sprite *sprite;
    GDNodeBase node;
public:
    static void _register_methods();

    GDCollisionPlayer();
    ~GDCollisionPlayer();

    void _ready();
    void _init();
    void _physics_process(float delta);
    void _input(Ref<InputEvent> event);

    void move(float delta);
    void _setEnabled(bool value);
    void isHorizontal(int num);
    void myIsPressed(int key_code);
    void handleKeyH(bool rightOrLeft);
    void handleKeyY(bool rightOrLeft);
    void input_pc(const Ref<InputEvent> event);
    };
}
#endif