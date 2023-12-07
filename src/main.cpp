#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <string.h>
#include <map>
#include <utility>

#include "Point.h"

using namespace std;
using dico_points = map<pair<double, double>, Point>;



int main()
{
    ifstream infile("../src/extract.txt");
    dico_points points;
    if (infile.is_open()){
        double x, y, z;
        while (infile >> x >> y >> z) {
            infile.get();
            points[{x, y}] = Point(x, y, z);
        }

        // Accessing elements in the map
        // Point p1 = myMap[{1.0, 2.0}];
        // Point p2 = myMap[{5.0, 6.0}];

        // Printing elements in the map
        for (auto const& [c, p]: points) {
            //cout << "{" << c.first << ", " << c.second << "}: ";
            cout << "(" << p.lat << ", " << p.lon << ", " << p.alt << ")" << endl;
        }
    }
    else {
        cout << "Problem while opening file !" << endl;
    }
    return 0;
}