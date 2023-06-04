#include <iostream>


class Circle{
public:
    Circle() = default;
    Circle(float _x, float _y, float _radius);

    void set_radius(float _r);
    void set_position(float _x, float _y);

    float get_radius();
    float get_position_x();
    float get_position_y();

    friend std::ostream& operator<<(std::ostream& os, const Circle& dt);

private:
    float radius = 0;
    float x = 0;
    float y = 0;
};