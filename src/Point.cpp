#include "Point.h"


Point::Point(double x, double y) : x(x), y(y) {}


Point::~Point()
{

}


float Point::isLeft(const Point& p1, const Point& p2)
{
    return ((p2.x - p1.x)*(y - p1.y) - (x - p1.x)*(p2.y - p1.y));
}


bool Point::isInTriangle(const Point& p1, const Point& p2, const Point& p3)
{
    float d1, d2, d3;
    bool left, right;

    d1 = isLeft(p1, p2);
    d2 = isLeft(p2, p3);
    d3 = isLeft(p3, p1);

    left = (d1 < 0) && (d2 < 0) && (d3 < 0);
    right = (d1 > 0) && (d2 > 0) && (d3 > 0);

    return (left || right);
}