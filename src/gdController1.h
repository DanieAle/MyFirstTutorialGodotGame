#ifndef GDCONTROLLER1_H
#define GDCONTROLLER1_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseButton.hpp>
#include <ResourceLoader.hpp>
#include <Texture.hpp>

namespace godot{

class GDController : public Sprite {
    GODOT_CLASS(GDController, Sprite)
private:
    Vector2 max_position;
    Vector2 min_position;
    Vector2 parent_pos;
    Vector2 range_x;
    Vector2 range_y;
    bool button_release;
    bool enabled;
    Ref<InputEventMouseButton> button;
    Ref<InputEventMouse> mouse;
    Ref<Texture> texture1;
    Ref<Texture> texture2;
public:
    static void _register_methods();

    GDController();
    ~GDController();

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
};
}

#endif