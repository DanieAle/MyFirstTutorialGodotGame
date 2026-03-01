#include "stick.h"

Stick::Stick(real_t x, real_t y)
:x(x),
y(y)
{}
Stick::Stick(Vector2 position):
position(position){}

real_t Stick::getX(){ return x; }
real_t Stick::getY(){ return y; }
float Stick::get_radius(){ return max_radius; }
Vector2 Stick::get_position(){ return position; }

void Stick::setX(real_t x){ x=x; }
void Stick::setY(real_t y){ y=y; }
void Stick::set_radius(float r){ max_radius=r; }
void Stick::set_position(Vector2 p){ position=p; }

Vector2 Stick::normalize_pos(){
    Vector2 normalized;
    if(position.length() > max_radius){
        normalized = position.normalized() * max_radius;
    }
    return normalized;
}