#ifndef GDMAINNODE_H
#define GDMAINNODE_H

#include <Godot.hpp>
#include <Node2D.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <KinematicBody2D.hpp>
#include <Camera2D.hpp>
#include <Viewport.hpp>
#include <Control.hpp>
#include <SceneTree.hpp>

namespace godot {

class GDMainNode : public Node2D {
    GODOT_CLASS(GDMainNode, Node2D)
private:
    Camera2D camera;
    Viewport *view;
    Control *myControl;
    KinematicBody2D *myPlayer;
public:
    static void _register_methods();

    GDMainNode();
    ~GDMainNode();

    void _ready();
    void _process(float delta);
    void _init();
    
    void _is_dead(String name);
    void create_enemy();
    void _start_game(bool play);
    void _set_visibleAll(bool value);
    void _defeat();
};

}


#endif