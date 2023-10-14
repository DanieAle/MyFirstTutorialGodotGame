#ifndef GDENEMY_H
#define GDENEMY_H

#include <ctime>
#include <Godot.hpp>
#include <Sprite.hpp>

namespace godot {

class GDEnemy : public Sprite {
    GODOT_CLASS(GDEnemy, Sprite)
private:
    float speed;
    Rect2 rec;
    int velocidades[4] = {300,500,600,800};
    int direcciones1[2] = {1,-1};
    bool direcciones2[2] = {true,false};
    String animations[3] = {"walk","swimming","flying"};
    int direccion;
    bool isHorizontal;
    String animation_selected;
    int pos_inicial_x;
    int pos_inicial_y;

public:
    static void _register_methods();

    GDEnemy();
    ~GDEnemy();

    void _ready();
    void _init();
    void _process(float delta);

    int new_pos_Inicial(int direccion,int min, int max,int limit);
    void HowWillMove();
    int random(int n);
};

}


#endif