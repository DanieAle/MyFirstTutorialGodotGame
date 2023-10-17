#include "gdCollisionEnemy.h"

using namespace godot;

void GDCollisionEnemy::_register_methods(){
    register_method("_ready", &GDCollisionEnemy::_ready);
    register_method("_physics_process", &GDCollisionEnemy::_physics_process);
    register_method("_init", &GDCollisionEnemy::_init);

    //SIGNAL
    register_signal<GDCollisionEnemy, bool,int,String>((char *)"in_movement",
        "flip",GODOT_VARIANT_TYPE_BOOL,"direcction",GODOT_VARIANT_TYPE_INT,
        "value_rotation",GODOT_VARIANT_TYPE_INT,"animation", GODOT_VARIANT_TYPE_STRING);
}

GDCollisionEnemy::GDCollisionEnemy(){
}
GDCollisionEnemy::~GDCollisionEnemy(){

}
void GDCollisionEnemy::_ready(){
    Godot::print("Hola");
    set_physics_process(true);
    set_refs(sprite);
    valid_obj_connect(sprite,"in_movement","_is_movement");
    //_setEnabled(false);
    rec = get_viewport_rect();
    max_x = rec.size.x;
    max_y = rec.size.y;
    rotation = 0;
    srand(time(0));
    confgEnemy();
}
void GDCollisionEnemy::_physics_process(float delta){
    //Godot::print("Fisicas ....");
    if(true){
        float speed = _get_speed();
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
void GDCollisionEnemy::_init(){
    Godot::print("Init ....");
    _set_time_passed(0.0);
    _set_speed(200);
}

void GDCollisionEnemy::confgEnemy(){
    int num = random(2);
    int num2 = random(1);
    int num3 = random(1);
    int num4 = random(3);
    _set_speed(velocidades[num4]);
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
int GDCollisionEnemy::new_pos_Inicial(int direccion,int min, int max,int limit){
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
            int new_max = (max + max) + limit;
            int new_min = limit;
            //Godot::print(String::num(new_min));
            pos = new_min - (std::rand() % (new_max - new_min + 1));
            break;
        }
    return pos;
}
void GDCollisionEnemy::HowWillMove(){
    rotation = 0;
    if(isHorizontal){
        pos_inicial_x = new_pos_Inicial(direccion,60, 100,rec.size.x);
        pos_inicial_y = 10 + (std::rand() % (550 - 10 + 1));
        emit_signal("in_movement",isHorizontal,direccion,rotation,animation_selected);
    }
    else{
        pos_inicial_y = new_pos_Inicial(direccion,60,100,rec.size.y);
        pos_inicial_x = 10 + (std::rand() % (400 - 10 + 1));
        if(direccion < 0){
            rotation = -90;
        }
        else rotation = 90;
        emit_signal("in_movement",isHorizontal,direccion,rotation,animation_selected);
    }
}
int GDCollisionEnemy::random(int n){
    int num = 0 + (std::rand() % (n - 0+1));

    return num;
}
void GDCollisionEnemy::isOfScreen(Vector2 position){
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
void GDCollisionEnemy::_setEnabled(bool value){
    _setEnabled(value);
    confgEnemy();
}