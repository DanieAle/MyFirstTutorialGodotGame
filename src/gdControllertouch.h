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
    Vector2 max_position;
    Vector2 min_position;
    Vector2 parent_pos;
    Vector2 range_x;
    Vector2 range_y;
    bool button_release;
    bool enabled;
    Ref<InputEventScreenTouch> button;
    Ref<InputEventScreenDrag> mouse;
    Ref<Texture> texture1;
    Ref<Texture> texture2;
public:
    static void _register_methods();

    GDControllerTouch();
    ~GDControllerTouch();

    //Defautl methods
    void _ready();
    void _init();
    void _input(Ref<InputEvent> event);
    void _process(float delta);
    //Event methods

    //New methods
    void set_refs(Sprite *&sprite);
    void valid_obj_connect(Sprite *&sprite, String name_signal, String name_method);
    void isOut();
    bool is_in_Range(Vector2 pos);
    void new_position(Vector2 pos);
    int Operation(int value);
    bool valid();
    void send_signal();
    int normalize(int value);
    void set_enabled(bool value);
    void move();
};
}

#endif