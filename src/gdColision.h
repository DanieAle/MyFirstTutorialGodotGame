#ifndef GDCOLISION_H
#define GDCOLISION_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <InputEvent.hpp>
#include <InputEventKey.hpp>
#include <Sprite.hpp>

namespace godot {

class GDColision : public KinematicBody2D {
    GODOT_CLASS(GDColision, KinematicBody2D)
private:
    float time_passed;
    float speed;
    Vector2 start_position;
    bool player;
    int key_h;
    int key_v;
    Ref<InputEventKey> key_event;
    String name;
    Sprite *sprite;
    bool body_enabled;
public:
    static void _register_methods();

    GDColision();
    ~GDColision();

    void _ready();
    void _physics_process(float delta);
    void _init();
    void _input(const Ref<InputEvent>);
    
    void handleKeyH(bool rightOrLeft);
    void handleKeyY(bool rightOrLeft);
    void myIsPressed(int key_code);
    void isHorizontal(int num);
    void isEnabled_movement(float delta);
    void _setEnabled(bool value);

};

}


#endif