#ifndef GDCONTROLLERTOUCH_H
#define GDCONTROLLERTOUCH_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <InputEventScreenTouch.hpp>
#include <InputEventScreenDrag.hpp>
#include <ResourceLoader.hpp>
#include <Texture.hpp>
#include <Control.hpp>
#include <OS.hpp>

namespace godot{

class GDControllerTouch : public Sprite {
    GODOT_CLASS(GDControllerTouch, Sprite)
private:
    bool button_release = false;
    Control *base;
    Sprite *ring;
    String dirBaseTexture;
    String dirPressTexture;
    Ref<Texture> baseTexture;
    Ref<Texture> pressTexture;
    bool active = false;
    float max_radius = 40.0;
    float_t lastpos = 0;
    bool android = false;
    int64_t touch_index = -1;
    Ref<InputEventScreenDrag> dragTouch;
    Ref<InputEventScreenTouch> touchplayer;
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
    bool checkOS();
    int Operation(int value);
    void send_signal();
    void move();
    Vector2 get_direction(Vector2 pos);
    void isInRange(Ref<InputEventScreenTouch> touch);
    void release();
    void getSpriteback();
    bool isMaxRange(real_t value);
};
}

#endif