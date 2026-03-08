#include "gdMainNode.h"
#include "iostream"
using namespace godot;

//enemy GDMainNode::enemys;
void GDMainNode::_register_methods(){
    register_method("_ready", &GDMainNode::_ready);
    register_method("_init", &GDMainNode::_init);
    register_method("_is_dead", &GDMainNode::_is_dead);
    register_method("_start_game", &GDMainNode::_start_game);
    register_method("move", &GDMainNode::move);
    register_method("set_enemy_active", &GDMainNode::set_enemy_active);
    register_method("_set_initGame", &GDMainNode::_set_initGame);

    register_signal<GDMainNode>((char *)"_defeat");
    register_signal<GDMainNode>("move", "position", GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<GDMainNode,bool>("activatePlayer", "play", GODOT_VARIANT_TYPE_BOOL);
    register_signal<GDMainNode>("initMenu");

    register_property<GDMainNode,int>("N.Enemy",&GDMainNode::num_enemy, 27);
}

void GDMainNode::_ready(){\
    Godot::print("Main Ready...");
    enemy_scene = ResourceLoader::get_singleton()->load("res://scenes/enemy/EnemyBody2d.tscn");
    time = get_child_as<Timer>("Timer");
    time->connect("timeout",this, "_start_game");
    myControl = get_child_as<Control>("ControlLayout");
    myControl->connect("start", this,"_set_initGame");
    myControl->connect("move", this, "move");
    myControl->connect("inc_dificulty", this ,"set_enemy_active");
    connect("initMenu",myControl,"initialize");
    connect("_defeat", myControl,"reset");
    myPlayer = get_child_as<KinematicBody2D>("PlayerBody2d");
    Godot::print("mask");
    Godot::print(String::num(myPlayer->get_collision_mask()));
    myPlayer->set_collision_mask(0);
    audio = get_child_as<AudioStreamPlayer>("Background");
    audio_defeat = get_child_as<AudioStreamPlayer>("Defeat");
    connect("move",myPlayer,"input_mouse");
    connect("activatePlayer",myPlayer, "_setEnabled");
    if(num_enemy < 27) num_enemy =27;
    create_enemy(num_enemy);
    active_enemy = 5;
    set_enemy_active(0);
}
void GDMainNode::_init(){
    Godot::print("Main Init...");
}

void GDMainNode::_is_dead(String name){
    Godot::print(name);
    if(name == "KinematicBody2D"){
        _set_disableAll();
        emit_signal("_defeat");
        audio->stop();
        audio_defeat->play();
    }
    emit_signal("activatePlayer",false);
    emit_signal("_defeat");
    myPlayer->set_visible(false);
    myPlayer->set_collision_mask(0);
    active_enemy = 5;
    set_enemy_active(0);
}
void GDMainNode::create_enemy(int num){
    for(int i =0;i< num; i++){
        Node2D *enemy_instance = Object::cast_to<Node2D>(enemy_scene->instance());
        enemy_instance->set_visible(false);
        enemy_instance->connect("collision",this, "_is_dead");
        enemy_instance->add_to_group("KinetmaticBody2D");
        add_child(enemy_instance);
        enemys.push_back(enemy_instance);
    }

}
void GDMainNode::_start_game(bool play){
    Godot::print("Play");
    time->stop();
    emit_signal("initMenu");
    myPlayer->set_collision_mask(1 << 0 | 1 << 2);
    Godot::print("mask");
    Godot::print(String::num(myPlayer->get_collision_mask()));
    audio_defeat->stop();
    audio->play();
    set_enemy_active(0);
    myPlayer->set_visible(true);
    emit_signal("activatePlayer", true);
}
void GDMainNode::_set_disableAll(){
    for(int i =0;i < enemys.size();i++){
        Node2D *enemy = enemys[i];

        enemy->set_visible(false);
        enemy->call("_setEnabled", false);
    }
}
void GDMainNode::_set_initGame(){
    time->start();
    _set_disableAll();
}
void GDMainNode::move(Vector2 position){
    emit_signal("move", position);
}
void GDMainNode::set_enemy_active(int add){
    for(int i =0;i < active_enemy+add;i++){
        Node2D *enemy = enemys[i];

        enemy->set_visible(true);
        enemy->call("_setEnabled", true);
    }
}