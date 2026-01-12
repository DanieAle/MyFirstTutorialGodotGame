#include "gdMainNode.h"

using namespace godot;

void GDMainNode::_register_methods(){
    register_method("_ready", &GDMainNode::_ready);
    register_method("_init", &GDMainNode::_init);
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
    myControl = Object::cast_to<Control>(get_child(8));
    if(myControl){
        myControl->connect("_start",this,"_start_game");
    }
    audio = Object::cast_to<AudioStreamPlayer>(get_child(9));
    audio_defeat = Object::cast_to<AudioStreamPlayer>(get_child(10));
    rect = Object::cast_to<ColorRect>(get_child(6));
    Rect2 mySize = get_viewport_rect();
    rect->set_size(mySize.get_size());
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
}
void GDMainNode::create_enemy(){
    Ref<PackedScene> enemy_scene = ResourceLoader::get_singleton()->load("res://gdData/Scenas/EnemyBody2d.tscn");

    Node2D *enemy_instance = Object::cast_to<Node2D>(enemy_scene->instance());
    enemy_instance->add_to_group("KinetmaticBody2D");
    add_child(enemy_instance);
}
void GDMainNode::_start_game(bool play){
    Godot::print("Play");
    audio_defeat->stop();
    audio->play();
    _set_visibleAll(play);

}
void GDMainNode::_set_visibleAll(bool value){
    SceneTree *tree = get_tree();
    tree->call_group("KinetmaticBody2D", "set_visible", value);
    tree->call_group("KinetmaticBody2D", "_setEnabled", value);
}