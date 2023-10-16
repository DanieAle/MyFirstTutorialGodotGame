#pragma once

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {
class GDNodeBase : public virtual Node {
    GODOT_CLASS(GDNodeBase, Node)

public:
    void set_refs(Node *obj);
};
}