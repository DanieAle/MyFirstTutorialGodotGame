#ifndef GDMAINNODE_H
#define GDMAINNODE_H

#include <Godot.hpp>
#include <Node2D.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <KinematicBody2D.hpp>
#include <Control.hpp>
#include <AudioStreamPlayer.hpp>
#include <Timer.hpp>
namespace godot {
class GDMainNode : public Node2D {
    GODOT_CLASS(GDMainNode, Node2D)
private:
    Ref<PackedScene> enemy_scene;
    Timer *time;
    Control *menu;
    Control *myControl;
    KinematicBody2D *myPlayer;
    AudioStreamPlayer *audio;
    AudioStreamPlayer *audio_defeat;
    int num_enemy;
    Array enemys;
    int active_enemy = 5;
    
public:
    static void _register_methods();

    GDMainNode() = default;
    ~GDMainNode() = default;

    void _ready();
    void _init();
    void set_childs();
    void set_conections();
    void _is_dead(String name);
    void create_enemy(int num);
    void _start_game(bool play);
    void _set_disableAll();
    void _set_initGame();
    void move(Vector2 position);
    void set_enemy_active(int active_enemy);

    template<typename T>
    T* get_child_as(NodePath nodeName){
        return Object::cast_to<T>(get_node(nodeName));
    }
};

}


#endif