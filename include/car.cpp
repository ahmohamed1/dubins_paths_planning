#include"car.h"



Car::Car(float _x, float _y, float _heading, float _turning_radius)
{
    x = x;
    y = _y;
    heading = _heading;
    turning_radius = _turning_radius;
    right_circle = compute_adjacent_circle(1);
    left_circle = compute_adjacent_circle(-1);
}

void Car::set_position(float _x, float _y)
{
    x = x;
    y = _y;
}
void Car::set_heading(float _heading)
{
    heading = _heading;
}

void Car::set_turning_radius(float _turning_radius)
{
    turning_radius = _turning_radius;
}


float Car::get_heading()
{
    return heading;
}


float Car::get_position_x()
{
    return x;
}
float Car::get_position_y()
{
    return y;
}

float Car::get_turning_radius()
{
    return turning_radius;
}


Cricle Car::get_right_cricle()
{
    right_circle = compute_adjacent_circle(1);
    return right_circle;
}
Cricle Car::get_left_cricle()
{
    left_circle = compute_adjacent_circle(-1);
    return left_circle;
}


Circle Car::compute_adjacent_circle(int side)
{
    // Side sould be 1 for right cirlce or -1 for left
    float xc = x + side* sin(heading + (M_PI / 2));
    float yc = y + side* cos(heading + (M_PI / 2));

    return Circle(xc,yc, turning_radius);
}