#include "circle.h"


    Circle::Circle(float _x, float _y, float _radius);
    {
        x = _x;
        y = _y;
        radius = _radius;
    }

    void Circle::set_radius(float _r)
    {
        radius = _r;
    }

    void Circle::set_position(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    float Circle::get_radius()
    {
        return radius;
    }

    float Circle::get_position_x()
    {
        return x;
    }

    float Circle::get_position_y()
    {
        return y;
    }

    std::ostream& operator<<(std::ostream& os, const Circle& dt)
    {
        os << "(" << dt.x <<","<<dt.y<<") radius = "<<dt.radius<<std::endl;
    }