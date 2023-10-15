#include "gdMainNode.h"

using namespace godot;

void GDMainNode::_register_methods(){
    register_method("_ready", &GDMainNode::_ready);
    register_method("_init", &GDMainNode::_init);
    register_method("_process", &GDMainNode::_process);
    register_method("_is_dead", &GDMainNode::_is_dead);
    register_method("_start_game", &GDMainNode::_start_game);

    register_signal<GDMainNode>((char *)"_defeat");

}

GDMainNode::GDMainNode(){

}

GDMainNode::~GDMainNode(){
    
}

void GDMainNode::_ready(){
    Godot::print("Main Ready...");
    for(int i =0;i< 4; i++){
        create_enemy();
    }
    view = get_viewport();
    view->set_size_override(true,Vector2(800, 600)); 
    myControl = Object::cast_to<Control>(get_child(8));
    if(myControl){
        myControl->connect("_start_game",this,"_start_game");
    }
}
void GDMainNode::_init(){
    Godot::print("Main Init...");
}
void GDMainNode::_process(float delta){

}

void GDMainNode::_is_dead(String name){
    Godot::print(name);
    if(name == "KinematicBody2D"){
        _set_visibleAll(false);
        emit_signal("_defeat");
    }
}
void GDMainNode::create_enemy(){
    Ref<PackedScene> enemy_scene = ResourceLoader::get_singleton()->load("res://gdData/Scenas/EnemyBody2d.tscn");

    Node2D *enemy_instance = Object::cast_to<Node2D>(enemy_scene->instance());
    enemy_instance->add_to_group("KinetmaticBody2D");
    add_child(enemy_instance);
}
void GDMainNode::_start_game(bool play){
    Godot::print("Play");
    _set_visibleAll(play);

}
void GDMainNode::_set_visibleAll(bool value){
    SceneTree *tree = get_tree();
    tree->call_group("KinetmaticBody2D", "set_visible", value);
    tree->call_group("KinetmaticBody2D", "_setEnabled", value);
}