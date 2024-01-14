#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <proj.h>

#include "Maillage.h"

using namespace std;
using dico_points = map<pair<double, double>, double>;

/**
 * @brief Fonction principale du programme
 * 
 * @details Fonction principale du programme. Elle prend en entrée le nom du fichier contenant les points et le nombre de pixels voulus.
 * 
 * @param argc Nombre d'arguments
 * @param argv Tableau contenant les arguments d'entrée du programme (nom du fichier contenant les points, nombre de pixels voulus)
 * @return int 
 */
int main(int argc, char *argv[])
{
    // ETAPE 1 : Récupérer les arguments d'entrée

    if(argc != 3){
        cout << "Usage: ./main <filename> <nbPixel>" << endl;
        return EXIT_FAILURE;
    }

    string fileName = string(argv[1]); // Nom du fichier
    fileName = "../" + fileName;
    int nbPixel = atoi(argv[2]); // Nombre de pixels voulus

    int nbPixelX = nbPixel;

    // ETAPE 2 : ouvrir et récupérer les données du fichier .txt

    Points points(fileName);

    cout << "Number of points read from file: " << points.getSize() << endl;

    // ETAPE 3 : initialiser l'image

    int nbPixelY = nbPixelX * (points.coords[3] - points.coords[2]) / (points.coords[1] - points.coords[0]);
    cout << points.coords[0] << " " << points.coords[1] << " " << points.coords[2] << " " << points.coords[3] << " " << points.coords[4] << " " << points.coords[5] << endl;
    cout << nbPixelX << " " << nbPixelY << endl;
    Representation repre(nbPixelX, nbPixelY, points.coords[4], points.coords[5]);

    cout << repre.h << endl;

    // ETAPE 4 : création de l'arbre binaire

    Arbre arbre(points.coords, 16);

    cout << arbre.nbDivisions << endl;

    // ETAPE 5 : Création du maillage

    Maillage maillage(arbre, repre, points);

    // ETAPE 6 : Enregistrement de la représentation

    repre.enregistrement(fileName);

    return EXIT_SUCCESS;
}