#include "Maillage.h"

#include "delaunator.hpp"

Maillage::Maillage(Arbre& arbre, Representation& repre, Points& struct_points) {
    executerMaillage(arbre, repre, struct_points);
}

void Maillage::coordPxl(int row, int col, double &x, double &y, int N, int M, Points& struct_points) {
    x = (col + 0.5) * (struct_points.coords[1] - struct_points.coords[0]) / M + struct_points.coords[0];
    y = (row + 0.5) * (struct_points.coords[3] - struct_points.coords[2]) / N + struct_points.coords[2];
}

void Maillage::executerMaillage(Arbre& arbre, Representation& repre, Points& struct_points) {
    int l, h;
    double x, y;
    double x1, y1, x2, y2, x3, y3;
    double z1, z2, z3;
    vector<double> coords_delaunay;
    dico_points _points = struct_points.points;

    /* Triangulation de Delaunay */
    cout << "Triangulation en cours..." << endl;

    cout << "Number of points in struct_points: " << struct_points.points.size() << endl;

    // Enregistrement
    for(map<pair<double,double>,double>::iterator it = struct_points.points.begin(); it != struct_points.points.end(); ++it){
        coords_delaunay.push_back(it->first.first);
        coords_delaunay.push_back(it->first.second);
    }

    //triangulation happens here
    delaunator::Delaunator d(coords_delaunay);

    cout << "Triangulation terminée" << endl;
    /* ...Fin de la triangulation... */

    cout << "Nombre de triangles : " << d.triangles.size()/3 << endl;  // Debug  
    cout << "Nombre de noeuds terminaux : " << pow(2, arbre.nbDivisions) << endl;  // Debug  

    /* Enregistrement des triangles dans les différentes zones de l'arbre binaire de cherche */
    cout << "Enregistrement des triangles..." << endl;

    for(size_t i = 0; i < d.triangles.size(); i+=3){
        x1 = d.coords[2 * d.triangles[i]];
        y1 = d.coords[2 * d.triangles[i] + 1];
        x2 = d.coords[2 * d.triangles[i + 1]];
        y2 = d.coords[2 * d.triangles[i + 1] + 1];
        x3 = d.coords[2 * d.triangles[i + 2]];
        y3 = d.coords[2 * d.triangles[i + 2] + 1];
        Triangle* tri = new Triangle(x1, y1, x2, y2, x3, y3);
        arbre.insererTri(tri);
    }

    cout << "Enregistrement terminé" << endl;
    /* ...Fin de l'enregistrement... */

    /* Attribution des valeurs de niveau de gris des pixels */
    cout << "Attribution des valeurs de couleur des pixels..." << endl;

    repre.infoRepre(l, h);  // Récupération des infos de l'image

    cout << "> Progression de l'attribution : " << flush;

    // Parcours des pixels
    for(int i=0; i<h; i++){
        if(i%(h/10) == 0 && i != 0) 
            cout << "#" << flush;  // Affichage d'une barre de progression
        for(int j=0; j<l; j++){
            coordPxl(i, j, x, y, h, l, struct_points);  // Coordonnées du centre du pixel (i, j)
            Point p(x, y);
            deque<Triangle*> listeTriangles = arbre.cherche(x, y);  // cherche de la zone d'appartenance du pixel dans l'arbre binaire de cherche
            for(auto tri : listeTriangles){
                Point p1(tri->Ax, tri->Ay);
                Point p2(tri->Bx, tri->By);
                Point p3(tri->Cx, tri->Cy);
                if(p.isInTriangle(p1, p2, p3)){  // Si le pixel est dans le triangle
                    z1 = _points.find({p1.x, p1.y})->second;
                    z2 = _points.find({p2.x, p2.y})->second;
                    z3 = _points.find({p3.x, p3.y})->second;
                    repre.alt[{i,j}] = (z1+z2+z3)/3;  // On enregistre la valeur d'altitude du pixel dans le dictionnaire alt de la représentation
                    repre.valPxl(i, j, (z1+z2+z3)/3); // On attribue la valeur de niveau de gris du pixel
                    break;  // On sort de la boucle dès qu'on a trouvé le triangle pour passer au pixel suivant
                }             
            }
        }
    }
    cout << endl;

    cout << "Number of points in alt: " << repre.alt.size() << endl;

    cout << "Attribution terminée" << endl;   
}