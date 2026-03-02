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
    Vector2 parent_pos;
    Vector2 parent_scale;
    bool button_release;
    bool enabled;
    Ref<InputEventScreenTouch> button;
    Ref<InputEventScreenDrag> mouse;
    Node2D *base;
    Ref<Texture> texture1;
    Ref<Texture> texture2;
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
    bool is_in_Range(float distance);
    int Operation(int value);
    bool valid();
    void send_signal();
    void set_enabled(bool value);
    void move();
    float convert_degree(float angle);
    Vector2 get_direction(Vector2 pos);
};
}

#endif