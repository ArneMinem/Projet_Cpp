#ifndef __POINT_H__
#define __POINT_H_

#include <fstream>
#include <iostream>

using namespace std;

/**
 * \class Point
 * \brief Cette classe permet de créer un point et de le manipuler (calculer si il est à gauche ou à droite d'un segment, si il est dans un triangle, ...)
 * \author Arne Jacobs
 * \date 2024
 */
class Point
{
    public:
    
        /**
         * \brief Constructeur de la classe Point
         * 
         * \param x Coordonnée x du point
         * \param y Coordonnée y du point
        */
        Point(double x, double y);

        /**
         * \brief Destructeur de la classe Point
        */
        ~Point();

        /**
         * \brief Permet de savoir si le point est à gauche ou à droite d'un segment
         * 
         * \param p1 Premier point du segment
         * \param p2 Deuxième point du segment
         * \return 1 si le point est à gauche du segment, -1 si il est à droite, 0 si il est sur le segment
        */
        float isLeft(const Point& p1, const Point& p2);

        /**
         * \brief Permet de savoir si le point est dans un triangle
         * 
         * \param p1 Premier sommet du triangle
         * \param p2 Deuxième sommet du triangle
         * \param p3 Troisième sommet du triangle
         * \return Vrai si le point est dans le triangle, faux sinon
        */
        bool isInTriangle(const Point& p1, const Point& p2, const Point& p3);

        double x, y;  // Coordonnées du point
        
};

#endif