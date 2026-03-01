#ifndef STICK_H
#define STICK_H

#include <Godot.hpp>
#include <Vector2.hpp>

using namespace godot;

class Stick{
    private:
    real_t x;
    real_t y;
    Vector2 position;
    float max_radius;

    public:
    Stick() = default;
    Stick(real_t x, real_t y);
    Stick(Vector2 position);

    real_t getX();
    real_t getY();
    float get_radius();
    Vector2 get_position();
    void setX(real_t x);
    void setY(real_t y);
    void set_radius(float r);
    void set_position(Vector2 p);

    Vector2 normalize_pos();
};


#endif