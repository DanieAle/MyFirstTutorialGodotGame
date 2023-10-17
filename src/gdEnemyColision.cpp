#include "gdEnemyColision.h"

using namespace godot;

void GDEnemyColision:: _register_methods(){
    register_method("_ready", &GDEnemyColision::_ready);
    register_method("_physics_process", &GDEnemyColision::_physics_process);
    register_method("_init", &GDEnemyColision::_init);
    register_method("_setEnabled", &GDEnemyColision::_setEnabled);
    

    register_signal<GDEnemyColision>((char *)"change_animation","direction"
        ,GODOT_VARIANT_TYPE_INT, "rotation",GODOT_VARIANT_TYPE_INT,"animation",GODOT_VARIANT_TYPE_STRING);
    register_signal<GDEnemyColision, String>((char*)"collision","name",GODOT_VARIANT_TYPE_STRING);
}
GDEnemyColision::GDEnemyColision(){
}
GDEnemyColision::~GDEnemyColision(){

}

void GDEnemyColision::_ready(){
    Godot::print("Ready...");
    set_physics_process(true);
    rec = get_viewport_rect();
    max_x = rec.size.x;
    max_y = rec.size.y;
    int64_t index = 0;
    sprite = Object::cast_to<Sprite>(get_child(index)); // Cambia "path_to_sprite" al camino real en tu escena
    if (sprite) {
        connect("change_animation", sprite, "_out_Of_Screen");
    }
    srand(time(0));
    confgEnemy();
    body_enabled = false;
    connect("collision", get_parent(),"_is_dead");
}

void GDEnemyColision::_physics_process(float delta){
    //Godot::print("Fisicas ....");
    if(body_enabled){
        Vector2 movement;
        if(isHorizontal){
        movement = Vector2(direccion,0);
        }
        else{
        movement = Vector2(0,direccion);
        }
        Vector2 position = movement * speed * delta;
    
        move_and_collide(position);
        Ref<KinematicCollision2D> collision = move_and_collide(position);
        if(collision.is_valid()){
    // Ahora puedes usar esta información según tus necesidades.
            String nombre = collision->get_collider()->get_class();
        //Godot::print("Colisión con: " + nombre);
            emit_signal("collision",nombre);
    // Por ejemplo, verifica el nombre del nodo con el que colisionó.
        }
        isOfScreen(get_position());
    }
}
void GDEnemyColision::_init(){
    Godot::print("Init ....");
    time_passed = 0.0;
    speed = 100.0;
}
void GDEnemyColision::confgEnemy(){
    int num = random(2);
    int num2 = random(1);
    int num3 = random(1);
    int num4 = random(3);
    speed = velocidades[num4];
    animation_selected = animations[num];
    direccion = direcciones1[num2];
    isHorizontal = direcciones2[num3];

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
    //sprite_animated->play(animation_selected);
}
int GDEnemyColision::new_pos_Inicial(int direccion,int min, int max,int limit){
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
            //sprite_animated->set_flip_h(true);
            break;
        }
    return pos;
}
void GDEnemyColision::HowWillMove(){
    int rotation = 0;
    if(isHorizontal){
        pos_inicial_x = new_pos_Inicial(direccion,60, 100,rec.size.x);
        pos_inicial_y = 10 + (std::rand() % (550 - 10 + 1));
    }
    else{
        pos_inicial_y = new_pos_Inicial(direccion,60,100,rec.size.y);
        pos_inicial_x = 10 + (std::rand() % (400 - 10 + 1));
        rotation = 90;
    }
    emit_signal("change_animation",direccion,rotation,animation_selected);
}
int GDEnemyColision::random(int n){
    int num = 0 + (std::rand() % (n - 0+1));

    return num;
}
void GDEnemyColision::isOfScreen(Vector2 position){
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
        confgEnemy();
    }
}
void GDEnemyColision::_setEnabled(bool value){
    body_enabled = value;
    confgEnemy();
}
