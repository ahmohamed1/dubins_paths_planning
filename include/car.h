#include<iostream>
#include <math.h>

#include "circle.h"

# define M_PI           3.14159265358979323846 

class Car
{
    public:
        Car() = default;
        Car(float _x, float _y, float _heading, float _turning_radius);

        void set_position(float _x, float _y);
        void set_heading(float _heading);
        void set_turning_radius(float _turning_radius);

        float get_heading();
        float get_position_x();
        float get_position_y();
        float get_turning_radius();
        Cricle get_right_cricle();
        Cricle get_left_cricle();

    private:
        float x;
        float y;
        float heading;
        float turning_radius;

        Circle right_circle;
        Circle left_circle;

        Circle compute_adjacent_circle(int side);

};