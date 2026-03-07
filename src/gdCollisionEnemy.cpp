#include "gdCollisionEnemy.h"

using namespace godot;

void GDCollisionEnemy::_register_methods(){
    register_method("_ready", &GDCollisionEnemy::_ready);
    register_method("_physics_process", &GDCollisionEnemy::_physics_process);
    register_method("_init", &GDCollisionEnemy::_init);
    register_method("_setEnabled", &GDCollisionEnemy::_setEnabled);

    //SIGNAL
    register_signal<GDCollisionEnemy, bool,int,String>((char *)"in_movement",
        "flip",GODOT_VARIANT_TYPE_BOOL,"direcction",GODOT_VARIANT_TYPE_INT,
        "value_rotation",GODOT_VARIANT_TYPE_INT,"animation", GODOT_VARIANT_TYPE_STRING);
    register_signal<GDCollisionEnemy, String>((char*)"collision","name",GODOT_VARIANT_TYPE_STRING);
}

void GDCollisionEnemy::_ready(){
    Godot::print("Hola");
    set_physics_process(true);
    sprite = get_child_as<Sprite>("Sprite");
    valid_obj_connect(sprite,"in_movement","_is_movement");
    rec = get_viewport_rect();
    max_x = rec.size.x;
    max_y = rec.size.y;
    rotation = 0;
    srand(time(0));
    confgEnemy();
    enabled = false;
}
void GDCollisionEnemy::_physics_process(float delta){
    //Godot::print("Fisicas ....");
    if(enabled){
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
            String nombre = collision->get_collider()->get_class();
            emit_signal("collision",nombre);
        }
        isOfScreen(get_position());
    }
}
void GDCollisionEnemy::_init(){
    Godot::print("Init ....");
    _set_time_passed(0.0);
    _set_speed(50);
}

void GDCollisionEnemy::confgEnemy(){
    int animation = random(2);
    int direction = random(1);
    int sense = random(1);
    int velocity = random(3);
    _set_speed(velocidades[velocity]);
    animation_selected = animations[animation];
    direccion = direcciones1[direction];
    isHorizontal = direcciones2[sense];

    HowWillMove();
    set_position(Vector2(pos_inicial_x,pos_inicial_y));
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
            int new_max = (limit/2) + limit;
            int new_min = limit + max;
            pos = new_min - (std::rand() % (new_max - new_min + 1));
            break;
        }
    return pos;
}
void GDCollisionEnemy::HowWillMove(){
    rotation = 0;
    if(isHorizontal){
        pos_inicial_x = new_pos_Inicial(direccion,100, 120,rec.size.x);
        pos_inicial_y = 10 + (std::rand() % (max_y - 10 + 1));
        emit_signal("in_movement",isHorizontal,direccion,rotation,animation_selected);
    }
    else{
        pos_inicial_y = new_pos_Inicial(direccion,100,120,rec.size.y);
        pos_inicial_x = 10 + (std::rand() % (max_x - 10 + 1));
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
    enabled = value;
    confgEnemy();
}