#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <string.h>
#include <map>
#include <utility>
#include <proj.h>

#include "delaunator.hpp"
#include "Point.h"

using namespace std;
using dico_points = map<pair<double, double>, double>;



int main()
{
    ifstream infile("../src/extract.txt");
    dico_points points;
    if (infile.is_open()){
        double x, y, z;
        while (infile >> x >> y >> z) {
            infile.get();
            points[{x, y}] = z;
        }

        // Accessing elements in the map
        // Point p1 = myMap[{1.0, 2.0}];
        // Point p2 = myMap[{5.0, 6.0}];

        // Printing elements in the map
        for (auto const& [c, p]: points) {
            cout << "{" << c.first << ", " << c.second << ", " << p << ")" << endl;
        }
    }
    else {
        cout << "Problem while opening file !" << endl;
    }

    // Initialize the projection transformation
    PJ* P = proj_create_crs_to_crs(
        nullptr,
        "+proj=longlat +datum=WGS84",  // Source CRS definition (e.g., WGS84 geographic coordinates)
        "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",  // Target CRS definition (e.g., Lambert Conformal Conic projection)
        nullptr);

    // Iterate through the points map and transform each geographic coordinate to projected coordinate
    for (const auto& [coord, value] : points) {
        double lon = coord.second;
        double lat = coord.first;
        double alt = value;

        PJ_COORD geo_coord, projected_coord;
        geo_coord.lpzt.lam = lon;  // Longitude
        geo_coord.lpzt.phi = lat;  // Latitude
        geo_coord.lpzt.z = alt;    // Altitude (if applicable)

        projected_coord = proj_trans(P, PJ_FWD, geo_coord);  // Forward projection from geographic to projected coordinates

        // Use the projected_coord.xy.x and projected_coord.xy.y for further processing
        cout << "(" << projected_coord.xyz.x << ", " << projected_coord.xyz.y << ", " << projected_coord.xyz.z << ")" << endl;
    }

    // Free the projection object after use
    proj_destroy(P);

    return 0;
}
