#ifndef __REPRESENTATION_H__
#define __REPRESENTATION_H__

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

using dico_points = map<pair<double, double>, double>;
/**
 * struct RGB
 * \brief Structure permettant de représenter un pixel par ses valeurs rgb
 * 
 * \param r Valeur de rouge du pixel
 * \param g Valeur de vert du pixel
 * \param b Valeur de bleu du pixel 
 */
struct RGB
{
    unsigned char r, g, b;
};

/**
 * class Representation
 * \brief Classe permettant de représenter une image
 * \details La classe permet de représenter une image à partir 
 * d'un ensemble de points et de leurs valeurs d'altitude et de 
 * les enregistrer dans un fichier image au format ppm (portable pixmap)
 * \author Arne Jacobs
 * \version 1.0
 * \date 2024
 */
class Representation {

    public:

        /**
         * \brief Construit un nouvel objet Representation
         * 
         * \param l Largeur de l'image en pixels
         * \param h Hauteur de l'image en pixels
         * \param min_z Valeur minimale de z
         * \param max_z Valeur maximale de z
         */
        Representation(int l, int h, double min_z, double max_z);

        /**
         * \brief Detruit l'objet Representation
         * 
         */
        ~Representation();

        /**
         * \brief Crée une image à partir d'un ensemble de points et de leurs valeurs d'altitude
         * 
         * \param min_z Valeur minimale de z
         * \param max_z Valeur maximale de z
         */
        void creeRepre(double min_z, double max_z);

        /**
         * \brief Supprime l'image
         * 
         */
        void suppRepre();

        int l = 0, h = 0;  // Largeur et hauteur de l'image en pixels

        RGB** image = nullptr;  // Tableau représentant les pixels de l'image, chaque pixel est défini par ses valeurs rgb

        dico_points alt;  // Dictionnaire contenant les points et leurs valeurs d'altitude

        vector<double> repart_z = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // Répartition des valeurs de z pour la colormap haxby
    
        /**
         * \brief Crée une image à partir d'un ensemble de points et de leurs valeurs d'altitude
         * 
         * \param l Largeur de l'image en pixels
         * \param h Hauteur de l'image en pixels
         */
        void infoRepre(int& l, int& h);

        /**
         * \brief Calcule les valeurs rgb d'un pixel à partir de sa valeur d'altitude z
         * 
         * \param z Valeur d'altitude du pixel
         * \param r Valeur de rouge du pixel
         * \param g Valeur de vert du pixel
         * \param b Valeur de bleu du pixel
         */
        void calCoul(double z, int& r, int& g, int& b);

        /**
         * \brief Calcule les coordonnées du centre d'un pixel à partir de ses coordonnées de coin supérieur gauche (row, col)
         * 
         * \param row Numéro de la ligne du pixel
         * \param col Numéro de la colonne du pixel
         * \param z Valeur d'altitude du pixel
         */
        void valPxl(int row, int col, double z);

        /**
         * \brief Enregistre l'image dans un fichier image au format ppm (portable pixmap)
         * 
         * \param filename Nom du fichier image 
         */
        void enregistrement(string filename);
};


#endif