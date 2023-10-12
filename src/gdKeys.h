#ifndef GDKEYS
#define GDKEYS

#include <Godot.hpp>
#include <GlobalConstants.hpp>
#include <InputEvent.hpp>
#include <InputEventKey.hpp>

namespace godot {

class GDKeys : public InputEvent {
    GODOT_CLASS(GDKeys, InputEvent)

private:
public:
    static void _register_methods();

    GDKeys();
    ~GDKeys();


    void _init(); // our initializer called by Godot
    void _input(const Ref<InputEvent>);
    void _process(float delta);
};

}

#endif