#ifndef MAILLAGE_H
#define MAILLAGE_H

#include "Arbre.h"  // Inclure le fichier d'en-tête de la classe ABR
#include "Representation.h"  // Inclure le fichier d'en-tête de la classe ImagePPM
#include "Points.h"  // Inclure le fichier d'en-tête de la classe Points
#include "Point.h"

/**
 * class Maillage
 * \brief Classe permettant de créer un maillage à partir d'un arbre binaire de recherche
 * \details La classe permet de créer un maillage à partir d'un arbre binaire de recherche et de l'enregistrer dans un fichier image au format ppm (portable pixmap)
 * \author Arne Jacobs
 * \version 1.0
 * \date 2024 
 */
class Maillage {
    public:

        /**
         * \brief Construit un nouvel objet Maillage à partir d'un arbre binaire de recherche et d'une image ppm vide
         * 
         * \param arbre Arbre binaire de recherche contenant les triangles à afficher
         * \param repre ImagePPM dans laquelle le maillage sera enregistré
         * \param struct_points Points contenant les coordonnées et les valeurs d'altitude des points
         */
        Maillage(Arbre& arbre, Representation& repre, Points& struct_points);  // Constructor to initialize member objects

        /**
         * \brief Detruit l'objet Maillage
         * 
         */
        void coordPxl(int row, int col, double &x, double &y, int N, int M, Points& struct_points);

        /**
         * \brief Crée un maillage à partir d'un arbre binaire de recherche et l'enregistre dans une image ppm
         * 
         * \param arbre Arbre binaire de recherche contenant les triangles à afficher
         * \param repre ImagePPM dans laquelle le maillage sera enregistré
         * \param struct_points Points contenant les coordonnées et les valeurs d'altitude des points 
         */
        void executerMaillage(Arbre& arbre, Representation& repre, Points& struct_points);
};

#endif // MAILLAGE_H