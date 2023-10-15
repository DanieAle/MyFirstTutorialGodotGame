#ifndef GDMAINNODE_H
#define GDMAINNODE_H

#include <Godot.hpp>
#include <Node2D.hpp>
namespace godot {

class GDMainNode : public Node2D {
    GODOT_CLASS(GDMainNode, Node2D)
private:
public:
    static void _register_methods();

    GDMainNode();
    ~GDMainNode();

    void _ready();
    void _process(float delta);
    void _init();
    

};

}


#endif