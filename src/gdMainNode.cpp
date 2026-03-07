#include "gdMainNode.h"
#include "iostream"
using namespace godot;

void GDMainNode::_register_methods(){
    register_method("_ready", &GDMainNode::_ready);
    register_method("_init", &GDMainNode::_init);
    register_method("_is_dead", &GDMainNode::_is_dead);
    register_method("_start_game", &GDMainNode::_start_game);
    register_method("move", &GDMainNode::move);

    register_signal<GDMainNode>((char *)"_defeat");
    register_signal<GDMainNode>("move", "position", GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<GDMainNode,bool>("activatePlayer", "play", GODOT_VARIANT_TYPE_BOOL);

    register_property<GDMainNode,int>("N.Enemy",&GDMainNode::num_enemy, 1);
}

void GDMainNode::_ready(){\
    Godot::print("Main Ready...");
    myControl = get_child_as<Control>("ControlLayout");
    myControl->connect("start", this,"_start_game");
    myControl->connect("move", this, "move");
    connect("_defeat", myControl,"reset");
    myPlayer = get_child_as<KinematicBody2D>("PlayerBody2d");
    audio = get_child_as<AudioStreamPlayer>("Background");
    audio_defeat = get_child_as<AudioStreamPlayer>("Defeat");
    connect("move",myPlayer,"input_mouse");
    connect("activatePlayer",myPlayer, "_setEnabled");
    for(int i =0;i< num_enemy; i++){
        create_enemy();
    }
}
void GDMainNode::_init(){
    Godot::print("Main Init...");
}

void GDMainNode::_is_dead(String name){
    Godot::print(name);
    if(name == "KinematicBody2D"){
        _set_visibleAll(false);
        emit_signal("_defeat");
        audio->stop();
        audio_defeat->play();
    }
    emit_signal("activatePlayer",false);
    emit_signal("_defeat");
    myPlayer->set_visible(false);
}
void GDMainNode::create_enemy(){
    Ref<PackedScene> enemy_scene = ResourceLoader::get_singleton()->load("res://scenes/enemy/EnemyBody2d.tscn");

    Node2D *enemy_instance = Object::cast_to<Node2D>(enemy_scene->instance());
    enemy_instance->set_visible(false);
    enemy_instance->connect("collision",this, "_is_dead");
    enemy_instance->add_to_group("KinetmaticBody2D");
    add_child(enemy_instance);
}
void GDMainNode::_start_game(bool play){
    Godot::print("Play");
    audio_defeat->stop();
    audio->play();
    _set_visibleAll(play);
    myPlayer->set_visible(true);
    emit_signal("activatePlayer", true);
}
void GDMainNode::_set_visibleAll(bool value){
    SceneTree *tree = get_tree();
    tree->call_group("KinetmaticBody2D", "set_visible", value);
    tree->call_group("KinetmaticBody2D", "_setEnabled", value);
}
void GDMainNode::move(Vector2 position){
    emit_signal("move", position);
}