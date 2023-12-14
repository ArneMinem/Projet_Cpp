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

    // Initialize the projection transformation
    PJ* P = proj_create_crs_to_crs(
        nullptr,
        "+proj=longlat +datum=WGS84",  // Source CRS definition (e.g., WGS84 geographic coordinates)
        "+proj=lcc +lat_1=49 +lat_2=44 +lat_0=46.5 +lon_0=3 +x_0=700000 +y_0=6600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",  // Target CRS definition (e.g., Lambert Conformal Conic projection)
        nullptr);

    if (infile.is_open()){
        double x, y, z;
        while (infile >> x >> y >> z) {
            infile.get();
            PJ_COORD geo_coord, projected_coord;
            geo_coord.lpzt.lam = y;  // Longitude
            geo_coord.lpzt.phi = x;  // Latitude
            geo_coord.lpzt.z = z;    // Altitude (if applicable)
            projected_coord = proj_trans(P, PJ_FWD, geo_coord);  // Forward projection from geographic to projected coordinates

            points[{projected_coord.xyz.x, projected_coord.xyz.y}] = projected_coord.xyz.z;
        }

        // Free the projection object after use
        proj_destroy(P);

        // Printing elements in the map
        for (auto const& [c, p]: points) {
            cout << "(" << c.first << ", " << c.second << ", " << p << ")" << endl;
        }
    }
    else {
        cout << "Problem while opening file !" << endl;
    }

    vector<double> keysVector;
    keysVector.reserve(points.size() * 2); // Reserve space for efficiency

    for (const auto& pair : points) {
        keysVector.push_back(pair.first.first);  // Push the first key
        keysVector.push_back(pair.first.second); // Push the second key
    }
    delaunator::Delaunator d(keysVector);

    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
        printf(
            "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
            d.coords[2 * d.triangles[i]],        //tx0
            d.coords[2 * d.triangles[i] + 1],    //ty0
            d.coords[2 * d.triangles[i + 1]],    //tx1
            d.coords[2 * d.triangles[i + 1] + 1],//ty1
            d.coords[2 * d.triangles[i + 2]],    //tx2
            d.coords[2 * d.triangles[i + 2] + 1] //ty2
            );
    }

    return 0;
}
