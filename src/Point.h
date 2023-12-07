#ifndef __POINT_H__
#define __POINT_H__

#include <cstdlib>
#include <fstream>

class Point {

    public:
        Point();
        Point(double lat, double lon, double alt); // Constructor
        ~Point(); // Destructor

        double lat;
        double lon;
        double alt;

        // friend std::ostream& operator<<(std::ostream& stream, const Point& c);
        friend std::istream& operator>>(std::istream& stream, Point& p);
} ;

#endif