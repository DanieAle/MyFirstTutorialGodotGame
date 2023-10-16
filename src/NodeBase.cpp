#include "GDNodeBase.h"

using namespace godot;

void GDNodeBase::_register_methods(){
    register_method("_init", &GDNodeBase::_init);
    register_method("_ready", &GDNodeBase::_ready);
    register_method("set_refs", &GDNodeBase::set_refs);
    register_method("valid_obj_connect", &GDNodeBase::valid_obj_connect);

}

GDNodeBase::GDNodeBase(){
}
GDNodeBase::~GDNodeBase(){

}
void GDNodeBase::_init(){

}
void GDNodeBase::_ready(){

}
void GDNodeBase::set_refs(Node *obj) {
    int i = 0;
    int child_count = get_child_count();
    while (i < child_count) {
        Node *node = get_child(i);
        String type_of_class = obj->get_class();
        if (node->is_class(type_of_class)) {
            obj = node;
            break;
        }
        i++;
    }
}
void GDNodeBase::valid_obj_connect(Node *obj,String name_signal,String name_method){
    if(obj){
        connect(name_signal, obj,name_method);
    }

}