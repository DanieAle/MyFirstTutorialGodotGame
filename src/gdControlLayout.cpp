#include <gdControlLayout.h>

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
}

void GDControlLayout::_init(){
}
void GDControlLayout::_ready(){
    set_size(get_viewport_rect().get_size());
    menu = Object::cast_to<Control>(get_node("Menu"));
    contador = Object::cast_to<Label>(get_node("Contador"));
    tContador = Object::cast_to<Timer>(get_node("TContador"));
    myStick = Object::cast_to<Sprite>(get_node("Joypad")->get_node("Stick"));
    menu->connect("_start",this,"startAll");
    connect("reset", menu, "_restart");
    tContador->connect("timeout", this, "win");
    myStick->connect("move",this,"isMoving");
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
void GDControlLayout::initialize(){
    Godot::print("start contador");
    contador->set_visible(true);
    tContador->start();
}
void GDControlLayout::win(){
    contador->set_text("0");
}
void GDControlLayout::startAll(){
    emit_signal("start", true);
}
void GDControlLayout::isMoving(Vector2 pos){
    emit_signal("move",pos);
}
void GDControlLayout::reset(){
    win();
    tContador->stop();
    contador->set_visible(false);
    emit_signal("reset");
}
void GDControlLayout::levelpass(int time){
    Godot::print(String::num(time));
    if(time == 15){
        emit_signal("inc_dificulty",5);
    }
    else if(time == 35){
        emit_signal("inc_dificulty",7);
    }
    else if(time == 55) emit_signal("inc_dificulty",10);
}
