#ifndef GDENEMY_H
#define GDENEMY_H

#include <ctime>
#include <Godot.hpp>
#include <Sprite.hpp>
#include <AnimatedSprite.hpp>

namespace godot {

class GDEnemy : public Sprite {
    GODOT_CLASS(GDEnemy, Sprite)
private:
    int max_x;
    int max_y;
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
    AnimatedSprite *sprite_animated;
public:
    static void _register_methods();

    GDEnemy();
    ~GDEnemy();

    void _ready();
    void _init();
    void _process(float delta);

    void confgEnemy();
    int new_pos_Inicial(int direccion,int min, int max,int limit);
    void HowWillMove();
    int random(int n);
    void isOfScreen(Vector2 position);
    void resetAnimations();
};

}


#endif