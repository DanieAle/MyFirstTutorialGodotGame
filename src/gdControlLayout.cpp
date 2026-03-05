#include <gdControlLayout.h>

using namespace godot;
void GDControlLayout::_register_methods(){
    register_method("_ready", &GDControlLayout::_ready);
    register_method("_init", &GDControlLayout::_init);
    register_method("_process", &GDControlLayout::_process);
    register_method("initialize", &GDControlLayout::initialize);
    register_method("win", &GDControlLayout::win);

}
GDControlLayout::GDControlLayout(){}
GDControlLayout::~GDControlLayout(){}

void GDControlLayout::_init(){
}
void GDControlLayout::_ready(){
    set_size(get_viewport_rect().get_size());
    menu = Object::cast_to<Control>(get_node("Menu"));
    contador = Object::cast_to<Label>(get_node("Contador"));
    tContador = Object::cast_to<Timer>(get_node("TContador"));
    menu->connect("_start",this,"initialize");
    tContador->connect("timeout", this, "win");
    lastTime = int(tContador->get_time_left());
}
void GDControlLayout::_process(float delta){
   int time = int(tContador->get_time_left());
   if(lastTime != time){
   int segundos = int(100 - time);
   contador->set_text(String::num(segundos));
   lastTime = time;
   }
}
void GDControlLayout::initialize(bool play){
    Godot::print("start contador");
    contador->set_visible(play);
    tContador->start();
}
void GDControlLayout::win(){
    contador->set_text("0");
}