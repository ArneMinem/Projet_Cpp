#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <iostream>
#include <deque>
#include <vector>

#include "Triangle.h"

using namespace std;

/**
 * struct Noeud
 * \brief Structure permettant de représenter un noeud de l'arbre binaire de recherche
 * \details La structure permet de représenter un noeud de l'arbre binaire de recherche à partir de ses coordonnées xmin, xmax, ymin et ymax et de ses coordonnées de centre (x, y)
 * \param coordCentre Vecteur contenant les coordonnées du centre du noeud
 * \param gauche Pointeur vers le noeud fils gauche
 * \param droit Pointeur vers le noeud fils droit
 * \param min_x Coordonnée x minimale du noeud
 * \param max_x Coordonnée x maximale du noeud
 * \param min_y Coordonnée y minimale du noeud
 * \param max_y Coordonnée y maximale du noeud
 * \param Triangles Liste des triangles contenus dans le noeud 
 */
struct Noeud
{
    vector<double> coordCentre;
    Noeud* gauche;
    Noeud* droit;
    double min_x, max_x, min_y, max_y;
    deque<Triangle*> Triangles;
};

/**
 * class Arbre
 * \brief Classe permettant de créer un arbre binaire de recherche
 * \details La classe permet de créer un arbre binaire de recherche à partir d'un ensemble de points
 *         et de rechercher les triangles contenus dans le noeud de l'arbre auquel appartient un point (x, y)
 *        en utilisant la méthode de recherche dichotomique.
 *       La classe permet également d'insérer un triangle dans un noeud de l'arbre.
 * \author Arne Jacobs
 * \version 1.0
 * \date 2024
 */
class Arbre {

    public:
        /**
         * \brief Construit un nouvel objet Arbre
         * 
         * \param coords Vecteur contenant les coordonnées xmin, xmax, ymin et ymax du noeud à créer
         * \param niv Le niveau de l'arbre binaire de recherche (cad le nombre de divisions de l'arbre binaire de recherche)
         */
        Arbre(const vector<double>& coords, int niv);

        /**
         * \brief Detruit l'objet Arbre
         * 
         */
        ~Arbre();

        /**
         * \brief utilise la fonction inserer(const vector<double>& coords, Noeud*& ptr, int n) pour insérer un noeud dans l'arbre binaire de recherche
         * 
         * \param coords Vecteur contenant les coordonnées xmin, xmax, ymin et ymax du noeud à insérer
        */
        void inserer(const vector<double>& coords);

        /**
         * \brief Utilise la fonction insererTri(Triangle* tri, Noeud*& ptr, double x, double y) pour insérer un triangle dans un noeud de l'arbre
         * 
         * \param tri Triangle à insérer
        */
        void insererTri(Triangle* tri);

        /**
         * \brief Permet de rechercher les triangles contenus dans le noeud de l'arbre auquel appartient le point (x, y)
         * 
         * \param x Coordonnée x du point à rechercher
         * \param y Coordonnée y du point à rechercher
         * \return deque<Triangle*> Liste des triangles contenus dans le noeud
         */
        deque<Triangle*> cherche(double x, double y) const;

        int nbDivisions;  // Profondeur de l'arbre binaire de recherche

    private:
        /**
         * \brief Permet de créer un noeud de l'arbre binaire de recherche
         * \param valeur Vecteur contenant les coordonnées du centre du noeud à créer
         * \param coords Vecteur contenant les coordonnées xmin, xmax, ymin et ymax du noeud à créer
         * \return Noeud* Pointeur vers le noeud créé
        */
        Noeud* creeNoeud(const vector<double>& valeur, const vector<double>& coords);

        /**
         * \brief Permet d'insérer un noeud dans l'arbre binaire de recherche (fonction appelée par inserer(const vector<double>& coords))
         * \param coords Vecteur contenant les coordonnées xmin, xmax, ymin et ymax du noeud à insérer
         * \param ptr Pointeur vers le noeud parent dans lequel on veut insérer le nouveau noeud
         * \param n Compteur permettant de savoir si la séparation doit se faire verticalement ou horizontalement
        */
        void inserer(const vector<double>& coords, Noeud*& ptr, int n);

        /**
         * \brief Permet de découper récursivement l'arbre binaire de recherche afin de lui associer ses noeuds
         * \details La fonction découpe l'arbre binaire de recherche en deux parties égales à chaque appel récursif 
         *          en alternant les découpe verticales et horizontales.
         * \param coords Vecteur contenant les coordonnées xmin, xmax, ymin et ymax du noeud à découper
         * \param n Compteur permettant de savoir si on doit découper verticalement ou horizontalement
        */
        void diviser(const vector<double>& coords, int n);

        /**
         * \brief Permet d'insérer un triangle dans un noeud de l'arbre (fonction appelée par insererTriangle(Triangle* tri))
         * \param tri Triangle à insérer
         * \param ptr Pointeur vers le noeud dans lequel on veut insérer le triangle
         * \param x Coordonnée x du centre du triangle
         * \param y Coordonnée y du centre du triangle
        */
        void insererTri(Triangle* tri, Noeud*& ptr, double x, double y);
        
        /**
         * \brief Permet de rechercher les triangles contenus dans le noeud de l'arbre auquel appartient le point (x, y) (fonction appelée par recherche(double x, double y) const)
         * \param x Coordonnée x du point à rechercher
         * \param y Coordonnée y du point à rechercher
         * \param ptr Pointeur vers le noeud dans lequel on veut rechercher le point
         * \param prev Pointeur vers le noeud parent du noeud dans lequel on veut rechercher le point
         * \param n Compteur permettant de savoir si la séparation doit se faire verticalement ou horizontalement
         * \return Liste des triangles contenus dans le noeud
        */
        deque<Triangle*> cherche(double x, double y, Noeud* ptr, Noeud*& prev, int n) const;

        /**
         * \brief Permet de détruire un noeud (fonction appelée par le destructeur)
         * \param ptr Pointeur vers le noeud à détruire
        */
        void detruire(Noeud* ptr);

        Noeud* racine;  // Racine de l'arbre binaire de recherche
};

#endif