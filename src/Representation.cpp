#include "Representation.h"

#include <cmath>
#include <iostream>

using namespace std;

vector<int> haxbyR = {10, 40, 20, 0, 0, 0, 26, 13, 25, 50, 68, 97, 106, 124, 138, 172, 205, 223, 240, 247, 255, 255, 244, 238, 255, 255, 255, 245, 255, 255, 255, 255};
vector<int> haxbyG = {0, 0, 5, 10, 25, 40, 102, 129, 175, 190, 202, 225, 235, 235, 236, 245, 255, 245, 236, 215, 189, 160, 117, 80, 90, 124, 158, 179, 196, 215, 235, 255};
vector<int> haxbyB = {121, 150, 175, 200, 212, 224, 240, 248, 255, 255, 255, 240, 225, 200, 174, 168, 162, 141, 121, 104, 87, 69, 75, 78, 90, 124, 158, 174, 196, 215, 235, 255};


Representation::Representation(int l, int h, double min_z, double max_z)
{
    this->l = l;
    this->h = h;

    creeRepre(min_z, max_z);
}

Representation::~Representation()
{
    suppRepre();
}

void Representation::creeRepre(double min_z, double max_z)
{
    if(image != nullptr){
        suppRepre();
    }

    image = new RGB*[h];

    for(int i = 0; i < h; i++){
        image[i] = new RGB[l];

        for(int j = 0; j < l; j++){
            image[i][j].r = 0;
            image[i][j].g = 0;
            image[i][j].b = 0;
        }
    }

    for (int i = 0; i < 32; i++){
        repart_z[i] = min_z + ((max_z - min_z) / (32 - 1)) * i;
    }
}

void Representation::suppRepre()
{
    if(image != nullptr){
        for(int i = 0; i < h; i++){
            delete[] image[i];
        }

        delete image;
    }
}

void Representation::infoRepre(int& l, int& h)
{
    l = this->l;
    h = this->h;
}

void Representation::calCoul(double z, int& r, int& g, int& b)
{
    for (int i = 0; i < 31; i++){
        if (repart_z[i] <= z && z <= repart_z[i + 1]){  // Affinement de la coloration du pixel
            r = (haxbyR[i + 1] - haxbyR[i]) / (repart_z[i + 1] - repart_z[i]) * (z - repart_z[i]) + haxbyR[i]; 
            g = (haxbyG[i + 1] - haxbyG[i]) / (repart_z[i + 1] - repart_z[i]) * (z - repart_z[i]) + haxbyG[i]; 
            b = (haxbyB[i + 1] - haxbyB[i]) / (repart_z[i + 1] - repart_z[i]) * (z - repart_z[i]) + haxbyB[i]; 
        }
    } 
}

void Representation::valPxl(int row, int col, double z)
{
    int r, g, b;
    calCoul(z, r, g, b);

    image[row][col].r = r;
    image[row][col].g = g;
    image[row][col].b = b;
}

double calculateDzDx(double c, double f, double i, double a, double d, double g, double cellsize) {
    return ((c + 2 * f + i) - (a + 2 * d + g)) / (8 * cellsize);
}

void Representation::enregistrement(string filename)
{
    string fullname = filename + ".ppm";
    cout << "Enregistrement de à cet endroit : " << fullname << endl;
    ofstream file(fullname, ios::out | ios::binary);

    file << "P6" << endl;
    file << l << endl;
    file << h << endl;
    file << "255" << endl;

    for (int i = 0; i < h; i++){
        for (int j = 0; j < l; j++){

            // ETAPE 7 : Création de l'ombrage

            if (i > 0 && i < h - 1 && j > 0 && j < l - 1){  // On ne calcule l'ombrage que pour les pixels qui ne sont pas sur les bords de l'image (sinon on sort de l'image
                int r, g, b;

                double Altitude = 15.0;
                double Zenith_deg = 90.0 - Altitude;
                double Zenith_rad = Zenith_deg * M_PI / 180.0;

                double Azimuth = 315.0;
                double Azimuth_math = abs(360.0 - Azimuth + 90.0);
                double Azimuth_rad = Azimuth_math * M_PI / 180.0;

                int cellsize = 5;
                int z_factor = 1;

                // cout << "alt[{h-2-i, j+1}] : " << alt[{h-2-i, j+1}] << endl;

                // Calculate dz/dx and dz/dy
                double dz_dx = calculateDzDx(alt[{h-2-i, j+1}], alt[{h-1-i, j+1}], alt[{h-i, j+1}], alt[{h-2-i, j-1}], alt[{h-1-i, j-1}], alt[{h-i, j-1}], cellsize);
                // cout << "dz_dx : " << dz_dx << endl;

                double dz_dy = calculateDzDx(alt[{h-i, j-1}], alt[{h-i, j}], alt[{h-i, j+1}], alt[{h-2-i, j-1}], alt[{h-2-i, j}], alt[{h-2-i, j+1}], cellsize);
                // cout << "dz_dy : " << dz_dy << endl;

                // Calculate slope
                double Slope_rad = atan(sqrt(pow(dz_dx, 2) + pow(dz_dy, 2)) * z_factor);
                // cout << "Slope_rad : " << Slope_rad << endl;

                // Calculate aspect
                double Aspect_rad;
                if (dz_dx != 0.) {
                    Aspect_rad = atan2(-dz_dy, dz_dx);
                    if (Aspect_rad < 0.) {
                        Aspect_rad = 2. * M_PI + Aspect_rad;
                    }
                }
                else if (dz_dx == 0.) {
                    if (dz_dy < 0.) {
                        Aspect_rad = 2 * M_PI - M_PI / 2.;
                    }
                    else if (dz_dy > 0.) {
                        Aspect_rad = M_PI / 2.;
                    }
                    else {
                        Aspect_rad = Aspect_rad;
                    }
                }
                // cout << "Aspect_rad : " << Aspect_rad << endl;

                double Hillshade = 255.0 * ((cos(Zenith_rad) * cos(Slope_rad)) + (sin(Zenith_rad) * sin(Slope_rad) * cos(Azimuth_rad - Aspect_rad)));
                // cout << "Hillshade : " << Hillshade << endl;

                int shade = floor(Hillshade); // Shade of grey
                r = min(255, max(0, image[h - 1 - i][j].r - shade)); // Clamp the result to the range [0, 255]
                g = min(255, max(0, image[h - 1 - i][j].g - shade)); // Clamp the result to the range [0, 255]
                b = min(255, max(0, image[h - 1 - i][j].b - shade)); // Clamp the result to the range [0, 255]

                image[h - 1 - i][j].r = r;
                image[h - 1 - i][j].g = g;
                image[h - 1 - i][j].b = b;
            }

            file.write((char*)&image[h - 1 - i][j], sizeof(RGB));  // Enregistrement des pixels de bas en haut et de gauche à droite
        }
    }

    cout << "Eregistrement final" << endl;
    file.close();
}