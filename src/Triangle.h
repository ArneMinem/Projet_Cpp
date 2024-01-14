#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

/**
 * \class Triangle
 * \brief Cette classe permet de créer un triangle et de le manipuler 
 * \details La classe permet de créer un triangle à partir de trois points et de le manipuler (calculer son aire, ...)
 * \author Arne Jacobs
 * \date 2024
 */
class Triangle
{
    public:

        /**
         * \brief Constructeur de la classe Triangle
         * 
         * \param Ax Coordonnée x du premier sommet du triangle
         * \param Ay Coordonnée y du premier sommet du triangle
         * \param Bx Coordonnée x du deuxième sommet du triangle
         * \param By Coordonnée y du deuxième sommet du triangle
         * \param Cx Coordonnée x du troisième sommet du triangle
         * \param Cy Coordonnée y du troisième sommet du triangle
         */
        Triangle(double Ax, double Ay, double Bx, double By, double Cx, double Cy);

        /**
         * \brief Destructeur de la classe Triangle
         */
        ~Triangle();

        double Ax, Ay, Bx, By, Cx, Cy;
};

#endif