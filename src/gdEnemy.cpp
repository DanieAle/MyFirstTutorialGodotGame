#include "gdEnemy.h"

using namespace godot;

void GDEnemy:: _register_methods(){
    register_method("_ready", &GDEnemy::_ready);
    register_method("_init", &GDEnemy::_init);
    register_method("_process", &GDEnemy::_process);

    register_property<GDEnemy, float>("speed", &GDEnemy::speed,20.0);

    register_signal<GDEnemy>((char *)"Out_of_Screen","isOut",GODOT_VARIANT_TYPE_BOOL);
}

GDEnemy::GDEnemy(){
}
GDEnemy::~GDEnemy(){

}

void GDEnemy::_ready(){
    Godot::print("Ready");
    sprite_animated = Object::cast_to<AnimatedSprite>(get_child(get_child_count()-1));
    rec = get_viewport_rect();
    max_x = rec.size.x;
    max_y = rec.size.y;
    srand(time(0));
    confgEnemy();
}

void GDEnemy::_init(){
    Godot::print("Init");
    //speed = 20.0;
}

void GDEnemy::_process(float delta){
    //Godot::print("Process");
    Vector2 movement;
    if(isHorizontal){
        movement = Vector2(direccion,0);
    }
    else{
        movement = Vector2(0,direccion);
    }
    Vector2 position = get_position();
    set_position(position+(movement * speed * delta));
    isOfScreen(position);
}
void GDEnemy::confgEnemy(){
    int num = random(2);
    int num2 = random(1);
    int num3 = random(1);
    int num4 = random(3);
    speed = velocidades[num4];
    animation_selected = animations[num];
    direccion = direcciones1[num2];
    isHorizontal = direcciones2[num3];

    resetAnimations();
    HowWillMove();
    /*Godot::print("Posicion x:");
    Godot::print(String::num(pos_inicial_x));
    Godot::print("Posicion y:");
    Godot::print(String::num(pos_inicial_y));
    Godot::print("Horizontal:");
    String prueba = isHorizontal ? "true" : "false";
    Godot::print(prueba);
    Godot::print("Direccion:");
    Godot::print(String::num(direccion));*/
    set_position(Vector2(pos_inicial_x,pos_inicial_y));
    sprite_animated->play(animation_selected);
}
int GDEnemy::new_pos_Inicial(int direccion,int min, int max,int limit){
    int minimo = min;
    int maximo = max;
    int pos = 0;
    switch (direccion)
        {
        case 1:
            pos = min + (std::rand() % (max - min + 1));
            pos *= -1;
            break;
        case -1:
            int new_max = max + limit;
            int new_min = limit;
            //Godot::print(String::num(new_min));
            pos = new_min - (std::rand() % (new_max - new_min + 1));
            sprite_animated->set_flip_h(true);
            break;
        }
    return pos;
}
void GDEnemy::HowWillMove(){
    if(isHorizontal){
        pos_inicial_x = new_pos_Inicial(direccion,60, 100,rec.size.x);
        pos_inicial_y = 10 + (std::rand() % (550 - 10 + 1));
    }
    else{
        pos_inicial_y = new_pos_Inicial(direccion,10,100,rec.size.y);
        pos_inicial_x = 10 + (std::rand() % (900 - 10 + 1));
        sprite_animated->set_rotation_degrees(90);
    }
}
int GDEnemy::random(int n){
    int num = 0 + (std::rand() % (n - 0+1));

    return num;
}
void GDEnemy::isOfScreen(Vector2 position){
    bool isOut = false;
    switch (direccion)
    {
    case 1:
        if(position.x > max_x+50 || position.y > max_y+50){
            isOut = true;
        }
        break;
    
    case -1:
        if(position.x < -50 || position.y < -50){
            isOut = true;
        }
        break;
    }
    if(isOut){
        emit_signal("Out_of_Screen",true);
        confgEnemy();
    }
}
void GDEnemy::resetAnimations(){
    sprite_animated->set_flip_h(false);
    sprite_animated->set_flip_v(false);
    sprite_animated->set_rotation_degrees(0);
}