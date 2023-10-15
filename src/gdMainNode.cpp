#include "gdMainNode.h"

using namespace godot;

void GDMainNode::_register_methods(){
    register_method("_ready", &GDMainNode::_ready);
    register_method("_init", &GDMainNode::_init);
    register_method("_process", &GDMainNode::_process);
}

GDMainNode::GDMainNode(){

}

GDMainNode::~GDMainNode(){
    
}

void GDMainNode::_ready(){
    Godot::print("Main Ready...");
}
void GDMainNode::_init(){
    Godot::print("Main Init...");
}
void GDMainNode::_process(float delta){

}