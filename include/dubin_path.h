#include <iostream>

#include "circle.h"
#include "car.h"


class Dubin_path
{
    public:
        Dubin_path() = default;
        
        void compute_path(Car start, Car goal);
        void compute_tangent_outer(Circle c1, Circle c2, Point2& pt1, Point2& pt2);
        void compute_tangent_inner(Circle c1, Circle c2, Point2& pt1, Point2& pt2);
        void compute_RSR();
    
    private:
        Car start_pos;
        Car goal_pos;

};

void Dubin_path::compute_path(Car start, Car goal)
{

}

void Dubin_path::compute_tangent_outer(Circle c1, Circle c2, Point2& pt1, Point2& pt2)
{
    float x1 = c1.get_position_x();
    float x2 = c2.get_position_x();
    float y1 = c1.get_position_y();
    float y2 = c2.get_position_y();

    float theta_1 = M_PI_2 + atan2(y2-y1, x2-x1);

    float bx = x1 + c1.get_radius()*cos(theta_1);
    float by = y1 + c1.get_radius()*sin(theta_1);

    float cx = bx + (x2 - x1);
    float cy = by + (y2 - y1);
    pt2.set_point(cx, cy);
    pt1.set_point(bx, by);
}

void Dubin_path::compute_tangent_inner(Circle c1, Circle c2, Point2& pt1, Point2& pt2)
{
    float x1 = c1.get_position_x();
    float x2 = c2.get_position_x();
    float y1 = c1.get_position_y();
    float y2 = c2.get_position_y();
    

    float D = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    float theta = cos(2 * c1.get_radius() / D);

    theta += atan2(y2-y1, x2-x1);

    float bx = x1 + c1.get_radius()*cos(theta);
    float by = y1 + c1.get_radius()*sin(theta);

    float bx_temp = x1 + 2 * c1.get_radius()*cos(theta);
    float by_temp = y1 + 2 * c1.get_radius()*sin(theta);


    float cx = bx + (x2 - bx_temp);
    float cy = by + (y2 - by_temp);
    
    pt2.set_point(cx, cy);
    pt1.set_point(bx, by);

}