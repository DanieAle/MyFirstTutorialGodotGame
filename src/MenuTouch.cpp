#include "MenuTouch.h"

using namespace godot;

void GDMenuTouch::_register_methods(){
    register_method("_ready", &GDMenuTouch::_ready);
    register_method("_init", &GDMenuTouch::_init);
    register_method("_button_down", &GDMenuTouch::_button_down);
    register_method("_time_end", &GDMenuTouch::_time_end);
    register_method("_restart", &GDMenuTouch::_restart);
    register_method("win", &GDMenuTouch::win);
    
    register_signal<GDMenuTouch, bool>((char *)"_start", "play",GODOT_VARIANT_TYPE_BOOL);
}

void GDMenuTouch::_ready(){
    button = Object::cast_to<TouchScreenButton>(get_node("Button"));
    button->connect("released",this,"_button_down");
    myLabel = Object::cast_to<Label>(get_node("Titulo"));
    myTimer = Object::cast_to<Timer>(get_node("Timer"));
    myTimer->connect("timeout", this, "_time_end");
}
void GDMenuTouch::_init(){
}

void GDMenuTouch::_button_down(){
    myLabel->set_text(myTitles[1]);
    button->set_visible(false);
    myTimer->start();
}
void GDMenuTouch::_time_end(){
    myLabel->set_visible(false);
    emit_signal("_start", true);
}
void GDMenuTouch::_restart(){
    myLabel->set_text(myTitles[0]);
    myLabel->set_visible(true);
    button->set_visible(true);
}
void GDMenuTouch::win(){
    myLabel->set_text("Winner!");
}