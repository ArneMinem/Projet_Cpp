#ifndef POINTS_H
#define POINTS_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <proj.h>

using namespace std;

using dico_points = map<pair<double, double>, double>;

/**
 * \class Points
 * \brief Cette classe permet de créer un ensemble de points et de les manipuler
 * \details La classe permet de créer un ensemble de points à partir d'un fichier contenant les coordonnées et les valeurs d'altitude des points et de les manipuler (calculer la distance entre deux points, ...)
 * \author Arne Jacobs
 * \date 2024
 */
class Points {
public:

    /**
     * \brief Constructeur de la classe Points
     * 
     * \param filename Nom du fichier contenant les coordonnées et les valeurs d'altitude des points
     */
    Points(const string& filename);

    vector<double> coordsVectorBasic; //Utilisé pour la triangulation de Delaunay
    vector<double> coords_xBasic;
    vector<double> coords_yBasic;
    vector<double> coords_z;

    double dmax_glob;
    
    dico_points points;
    vector<double> coords;
    
    size_t getSize() const {
        return points.size();
    }

};

#endif // POINTS_H
