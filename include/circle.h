#include <iostream>


struct Point2
{
    float x;
    float y;
    Point2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    void set_point(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    
    Point2 normalized() {
        float magnitude = std::sqrt(x * x + y * y );
        return Point2(x / magnitude, y / magnitude);
    }

    float magnitude()
    {
        return std::sqrt(x * x + y * y );
    }

     Point2 operator-(const Point2& other) const {
        return Point2(x - other.x, y - other.y);
    }
    Point2 operator+(const Point2& other) const {
        return Point2(x + other.x, y + other.y);
    }

    Point2 operator*(const float& other) const {
        return Point2(x * other, y * other);
    }
};


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