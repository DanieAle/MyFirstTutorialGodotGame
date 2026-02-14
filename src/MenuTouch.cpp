#include "MenuTouch.h"

using namespace godot;

void GDMenuTouch::_register_methods(){
    register_method("_ready", &GDMenuTouch::_ready);
    register_method("_init", &GDMenuTouch::_init);
    register_method("_process", &GDMenuTouch::_process);
    register_method("_button_down", &GDMenuTouch::_button_down);
    register_method("_time_end", &GDMenuTouch::_time_end);
    register_method("_game_Over", &GDMenuTouch::_game_Over);
    register_method("_restart", &GDMenuTouch::_restart);
    
    register_signal<GDMenuTouch, bool>((char *)"_start", "play",GODOT_VARIANT_TYPE_BOOL);
    register_signal<GDMenuTouch>((char *)"_reset");
}

GDMenuTouch::GDMenuTouch(){

}

GDMenuTouch::~GDMenuTouch(){
    
}

void GDMenuTouch::_ready(){
    Godot::print("Menu Ready...");
    button = Object::cast_to<TouchScreenButton>(get_node("Button"));
    button->connect("pressed",this,"_button_down");
    myLabel = Object::cast_to<Label>(get_node("Titulo"));
    myTimer = Object::cast_to<Timer>(get_node("Timer"));
    myTimer->connect("timeout", this, "_time_end");
    connect("_reset",this,"_restart");
}
void GDMenuTouch::_init(){
    Godot::print("Menu Init...");
    tiempo_transcurrido = 0.0;
    start = false;
}
void GDMenuTouch::_process(float delta){
    if(start){
        tiempo_transcurrido += delta;
        int segundos = int(tiempo_transcurrido);
        myLabel2->set_text(String::num(segundos));
    }
}

void GDMenuTouch::_button_down(){
    Godot::print("Presionado");
    myLabel->set_text(myTitles[1]);
    button->set_visible(false);
    myTimer->start();
}
void GDMenuTouch::_time_end(){
    myLabel->set_visible(false);
    start = true;
    emit_signal("_start", true);
}
void GDMenuTouch::_game_Over(){
    myLabel2->set_text("0");
    start = false;
    tiempo_transcurrido = 0.0;
    myLabel->set_text(myTitles[2]);
    myLabel->set_visible(true);
    myTimer2->start();
}
void GDMenuTouch::_restart(){
    myLabel->set_text(myTitles[0]);
    button->set_visible(true);
    tiempo_transcurrido = 0.0;
    start = false;
}