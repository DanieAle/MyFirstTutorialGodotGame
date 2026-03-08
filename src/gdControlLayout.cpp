#include "gdControlLayout.h"

using namespace godot;
void GDControlLayout::_register_methods(){
    register_method("_ready", &GDControlLayout::_ready);
    register_method("_init", &GDControlLayout::_init);
    register_method("_process", &GDControlLayout::_process);
    register_method("initialize", &GDControlLayout::initialize);
    register_method("win", &GDControlLayout::win);
    register_method("startAll", &GDControlLayout::startAll);
    register_method("isMoving", &GDControlLayout::isMoving);
    register_method("reset", &GDControlLayout::reset);
    register_method("levelPass", &GDControlLayout::levelpass);
    
    register_signal<GDControlLayout, bool>((char *)"start", "play",GODOT_VARIANT_TYPE_BOOL);
    register_signal<GDControlLayout>("move", "position", GODOT_VARIANT_TYPE_VECTOR2);
    register_signal<GDControlLayout>("reset");
    register_signal<GDControlLayout>("inc_dificulty","number",GODOT_VARIANT_TYPE_INT);
    register_signal<GDControlLayout>("win");
}

void GDControlLayout::_init(){
}
void GDControlLayout::_ready(){
    set_size(get_viewport_rect().get_size());
    set_childs();
    Control *joypad = get_child_as<Control>("Joypad");
    myStick = Object::cast_to<Sprite>(joypad->get_node("Stick"));
    if(!checkOS()){
        joypad->set_visible(false);
    }
    set_conections();
    lastTime = int(tContador->get_time_left());
}
void GDControlLayout::_process(float delta){
   int time = int(tContador->get_time_left());
   if(lastTime != time){
   int segundos = int(100 - time);
   levelpass(segundos);
   contador->set_text(String::num(segundos));
   lastTime = time;
   }
}
void GDControlLayout::set_childs(){
    menu = get_child_as<Control>("Menu");
    contador = get_child_as<Label>("Contador");
    tContador = get_child_as<Timer>("TContador");
}
void GDControlLayout::set_conections(){
    menu->connect("_start",this,"startAll");
    connect("reset", menu, "_restart");
    connect("win", menu, "win");
    tContador->connect("timeout", this, "win");
    myStick->connect("move",this,"isMoving");
}
bool GDControlLayout::checkOS(){
    String os = OS::get_singleton()->get_name();

    return os == "Android";
}
void GDControlLayout::initialize(){
    contador->set_visible(true);
    tContador->start();
}
void GDControlLayout::win(){
    reset();
    emit_signal("win");
}
void GDControlLayout::startAll(){
    emit_signal("start", true);
}
void GDControlLayout::isMoving(Vector2 pos){
    emit_signal("move",pos);
}
void GDControlLayout::reset(){
    contador->set_text("0");
    tContador->stop();
    contador->set_visible(false);
    emit_signal("reset");
}
void GDControlLayout::levelpass(int time){
    if(time == 15){
        emit_signal("inc_dificulty",5);
    }
    else if(time == 35){
        emit_signal("inc_dificulty",7);
    }
    else if(time == 55) emit_signal("inc_dificulty",10);
}
