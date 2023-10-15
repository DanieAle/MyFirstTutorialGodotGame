#ifndef GDENEMYCOLISION_H
#define GDENEMYCOLISION_H

#include <ctime>
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <Sprite.hpp>

namespace godot {

class GDEnemyColision : public KinematicBody2D {
    GODOT_CLASS(GDEnemyColision, KinematicBody2D)
private:
    float time_passed;
    float speed;
    int max_x;
    int max_y;
    Rect2 rec;
    int velocidades[4] = {300,500,600,800};
    int direcciones1[2] = {1,-1};
    bool direcciones2[2] = {true,false};
    String animations[3] = {"walk","swimming","flying"};
    String animation_selected;
    int direccion;
    bool isHorizontal;
    int pos_inicial_x;
    int pos_inicial_y;
    Sprite *sprite;
public:
    static void _register_methods();
    
    GDEnemyColision();
    ~GDEnemyColision();

    void _ready();
    void _physics_process(float delta);
    void _init();

    void confgEnemy();
    int new_pos_Inicial(int direccion,int min, int max,int limit);
    void HowWillMove();
    int random(int n);
    void isOfScreen(Vector2 position);


};
}

#endif