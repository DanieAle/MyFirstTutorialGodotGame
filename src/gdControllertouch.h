#ifndef GDCONTROLLERTOUCH_H
#define GDCONTROLLERTOUCH_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <InputEventScreenTouch.hpp>
#include <InputEventScreenDrag.hpp>
#include <ResourceLoader.hpp>
#include <Texture.hpp>

namespace godot{

class GDControllerTouch : public Sprite {
    GODOT_CLASS(GDControllerTouch, Sprite)
private:
    bool button_release = false;
    Node2D *base;
    Ref<Texture> baseTexture;
    Ref<Texture> pressTexture;
    bool active = false;
    float max_radius = 60.0;
public:
    static void _register_methods();

    GDControllerTouch() = default;
    ~GDControllerTouch() = default;

    //Defautl methods
    void _ready();
    void _init();
    void _input(Ref<InputEvent> event);
    void _process(float delta);
    //Event methods

    //New methods
    int Operation(int value);
    void send_signal();
    void move();
    Vector2 get_direction(Vector2 pos);
    void isInRange(Ref<InputEventScreenTouch> touch);
    void release();
    void getSpriteback();
};
}

#endif