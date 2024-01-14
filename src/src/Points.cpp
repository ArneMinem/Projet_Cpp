#include "Points.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

Points::Points(const string& filename) {
    
    ifstream infile(filename);
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
            geo_coord.lpzt.z = z;    // Altitude
            projected_coord = proj_trans(P, PJ_FWD, geo_coord);  // Forward projection from geographic to projected coordinates

            points[{projected_coord.xyz.x, projected_coord.xyz.y}] = abs(projected_coord.xyz.z);

            coordsVectorBasic.push_back(projected_coord.xyz.x);
            coordsVectorBasic.push_back(projected_coord.xyz.y);

            coords_xBasic.push_back(projected_coord.xyz.x);
            coords_yBasic.push_back(projected_coord.xyz.y);
            coords_z.push_back(abs(projected_coord.xyz.z));
        }

        // Free the projection object after use
        proj_destroy(P);

        // Printing elements in the map
        // for (auto const& [c, p]: points) {
        //     cout << "(" << c.first << ", " << c.second << ", " << p << ")" << endl;
        // }
    }
    else {
        cout << "Problem while opening file !" << endl;
    }

    // On note les dimensions minimales maximales pour l'affichage de l'image
    double max_x = *max_element(coords_xBasic.begin(), coords_xBasic.end());
    double min_x = *min_element(coords_xBasic.begin(), coords_xBasic.end());
    double max_y = *max_element(coords_yBasic.begin(), coords_yBasic.end());
    double min_y = *min_element(coords_yBasic.begin(), coords_yBasic.end());
    double max_z = *max_element(coords_z.begin(), coords_z.end());
    double min_z = *min_element(coords_z.begin(), coords_z.end());

    dmax_glob = max_x-min_x >= max_y-min_y ? max_x-min_x : max_y-min_y;

    this->points = points;
    coords = {min_x, max_x, min_y, max_y, min_z, max_z};

    cout << coords[0] << endl;
}