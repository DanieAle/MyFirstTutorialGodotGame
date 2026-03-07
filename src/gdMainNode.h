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
#include <AudioStreamPlayer.hpp>
#include <ColorRect.hpp>

namespace godot {

class GDMainNode : public Node2D {
    GODOT_CLASS(GDMainNode, Node2D)
private:
    Camera2D *camera;
    Control *menu;
    Viewport *view;
    Control *myControl;
    KinematicBody2D *myPlayer;
    AudioStreamPlayer *audio;
    AudioStreamPlayer *audio_defeat;
    ColorRect *rect;
    Control *layout;
    int num_enemy;
public:
    static void _register_methods();

    GDMainNode() = default;
    ~GDMainNode() = default;

    void _ready();
    void _init();
    
    void _is_dead(String name);
    void create_enemy();
    void _start_game(bool play);
    void _set_visibleAll(bool value);
    void _defeat();
    void move(Vector2 position);
    void stop();

    template<typename T>
    T* get_child_as(NodePath nodeName){
        return Object::cast_to<T>(get_node(nodeName));
    }
};

}


#endif