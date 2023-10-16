#pragma once

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {
class GDNodeBase : public virtual Node {
    GODOT_CLASS(GDNodeBase, Node)

public:
    static void _register_methods();

    GDNodeBase();
    ~GDNodeBase();

    void _init();
    void _ready();
    
    void set_refs(Node *obj);
    void valid_obj_connect(Node *obj,String name_signal, String name_method);
};
}