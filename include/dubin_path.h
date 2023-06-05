#include <iostream>
#include <vector>
#include "circle.h"
#include "car.h"


class Dubin_path
{
    public:
        Dubin_path() = default;
        
        void compute_path(Car start, Car goal);
        //Outer tangent (LSL and RSR)
        void compute_tangent_outer(Circle c1, Circle c2, Point2& pt1, Point2& pt2);
        //Inner tangent (RSL and LSR)
        void compute_tangent_inner(Circle c1, Circle c2, Point2& pt1, Point2& pt2);
        //Get the RLR or LRL tangent points
        void compute_rlr_or_lrl_tangent(Circle c1, Circle c2, Point2& pt1, Point2& pt2, bool LRL = true);

        float get_arc_length(Circle circleCenterPos, Point2 startPos, Point2 goalPos, bool isLeftCircle);
        
        void add_coordinates_to_path(Point2 currentPos, float theta, std::vector<Point2>& finalPath, int segments, bool isTurning, bool isTurningRight);


        void Get_RSR_Length();
    private:
        Car start_pos;
        Car goal_pos;
        float turning_radius;
        //How far we are driving each update, the accuracy will improve if we lower the driveDistance
        //But not too low because rounding errors will appear
        //Is used to generate the coordinates of a path
        float driveDistance = 0.02f;

};

void Dubin_path::compute_path(Car start, Car goal)
{

}

//Outer tangent (LSL and RSR)
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

//Inner tangent (RSL and LSR)
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

//Get the RLR or LRL tangent points
void Dubin_path::compute_rlr_or_lrl_tangent(Circle c1, Circle c2, Point2& pt1, Point2& pt2, bool LRL = true)
{
    float x1 = c1.get_position_x();
    float x2 = c2.get_position_x();
    float y1 = c1.get_position_y();
    float y2 = c2.get_position_y();
    

    float D = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    float theta = cos(D /(4*c1.get_radius()));

    if (LRL)
        theta = atan2((y2-y1), (x2-x1)) + theta;
    else
        theta = atan2((y2-y1), (x2-x1)) - theta;
    
    //Calculate the position of the third circle
    float x = x1 + 2 * c1.get_radius() * cos(theta);
    float y = y1 + 2 * c1.get_radius() * sin(theta);

    Point2 pt3(x,y);
    Point2 v2 = (Point2(x1,y1) - pt3).normalized();
    Point2 v3 = (Point2(x2,y2) - pt3).normalized();
    pt1 = pt3 + v2*c1.get_radius();
    pt2 = pt3 + v3*c1.get_radius();

    // pt1.x = pt3.x + v2.x *c1.get_radius();
    // pt1.y = pt3.y + v2.y *c1.get_radius();

    // pt2.x = pt3.x + v3.x *c1.get_radius();
    // pt2.y = pt3.y + v3.y *c1.get_radius();
}

float Dubin_path::get_arc_length(Circle circleCenterPos, Point2 startPos, Point2 goalPos, bool isLeftCircle)
{
    Point2 V1 = startPos - Point2(circleCenterPos.get_position_x(), circleCenterPos.get_position_y());
    Point2 V2 = goalPos -  Point2(circleCenterPos.get_position_x(), circleCenterPos.get_position_y());

    float theta = std::atan2(V2.y, V2.x) - std::atan2(V1.y, V1.x);

    if (theta < 0 && isLeftCircle)
    {
        theta += 2 * M_PI;
    }
    else if (theta > 0 && !isLeftCircle)
    {
        theta -= 2 * M_PI;
    }

    float arcLength = abs(theta * circleCenterPos.get_radius());

    return arcLength;
}

//Loops through segments of a path and add new coordinates to the final path
void Dubin_path::add_coordinates_to_path(
    Point2 currentPos,
    float theta,
    std::vector<Point2>& finalPath,
    int segments,
    bool isTurning,
    bool isTurningRight)
{
    for (int i = 0; i < segments; i++)
    {
        //Update the position of the car
        currentPos.x += driveDistance * sin(theta);
        currentPos.y += driveDistance * cos(theta);

        //Don't update the heading if we are driving straight
        if (isTurning)
        {
            //Which way are we turning?
            float turnParameter = 1;

            if (!isTurningRight)
            {
                turnParameter = -1;
            }

            //Update the heading
            theta += (driveDistance / turning_radius) * turnParameter;
        }

        //Add the new coordinate to the path
        finalPath.push_back(currentPos);
    }
}


//RSR
void Dubin_path::Get_RSR_Length()
{
    //Find both tangent positons
    Point2 startTangent;
    Point2 goalTangent ;

    compute_tangent_outer(start_pos.get_right_cricle(), goal_pos.get_right_cricle(), startTangent, goalTangent);

    //Calculate lengths
    float length1 = get_arc_length(start_pos.get_right_cricle(), start_pos.get_point(), startTangent, false);

    float length2 = Point2(startTangent - goalTangent).magnitude();

    float length3 = get_arc_length(goal_pos.get_right_cricle(), goalTangent, goal_pos.get_point(), false);

    //Save the data
    

    //We also need this data to simplify when generating the final path


    //RSR


    //Add the path to the collection of all paths

}