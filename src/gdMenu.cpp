#include "gdMenu.h"

using namespace godot;

void GDMenu::_register_methods(){
    register_method("_ready", &GDMenu::_ready);
    register_method("_init", &GDMenu::_init);
    register_method("_button_down", &GDMenu::_button_down);
    register_method("_time_end", &GDMenu::_time_end);
    register_method("_game_Over", &GDMenu::_game_Over);
    register_method("_restart", &GDMenu::_restart);
    
    register_signal<GDMenu, bool>((char *)"_start_game", "play",GODOT_VARIANT_TYPE_BOOL);
}

GDMenu::GDMenu(){

}

GDMenu::~GDMenu(){
    
}

void GDMenu::_ready(){
    Godot::print("Menu Ready...");
    button = Object::cast_to<BaseButton>(get_child(0));
    button->connect("pressed",this,"_button_down");
    myLabel = Object::cast_to<Label>(get_child(1));
    myTimer = Object::cast_to<Timer>(get_child(2));
    myTimer->connect("timeout", this, "_time_end");
    myTimer2 = Object::cast_to<Timer>(get_child(3));
    myTimer2->connect("timeout", this, "_restart");
    get_parent()->connect("_defeat", this, "_game_Over");
}
void GDMenu::_init(){
    Godot::print("Menu Init...");
}

void GDMenu::_button_down(){
    Godot::print("Presionado");
    myLabel->set_text(myTitles[1]);
    button->set_visible(false);
    myTimer->start();
}
void GDMenu::_time_end(){
    myLabel->set_visible(false);
    emit_signal("_start_game", true);
}
void GDMenu::_game_Over(){
    myLabel->set_text(myTitles[2]);
    myLabel->set_visible(true);
    myTimer2->start();
}
void GDMenu::_restart(){
    myLabel->set_text(myTitles[0]);
    button->set_visible(true);
}
