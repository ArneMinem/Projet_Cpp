#include <algorithm>
#include "Arbre.h"


// Constructeur
Arbre::Arbre(const vector<double>& coords, int niv) : nbDivisions(niv), racine(0)
{
    inserer(coords);
    diviser(coords, 0);
}


// Destructeur
Arbre::~Arbre ()
{
    detruire(racine);
}


// Insérer un noeud
void Arbre::inserer(const vector<double>& coords)
{
    inserer(coords, racine, 0);
}


// Insérer un triangle
void Arbre::insererTri(Triangle* tri)
{
    insererTri(tri, racine, tri->Ax, tri->Ay);
    insererTri(tri, racine, tri->Bx, tri->By);
    insererTri(tri, racine, tri->Cx, tri->Cy);
}


// chercher un noeud
deque<Triangle*> Arbre::cherche(double x, double y) const
{
    Noeud* prev = 0;  
    return cherche(x, y, racine, prev, 0);
}


Noeud* Arbre::creeNoeud (const vector<double>& valeur, const vector<double>& coords){
    Noeud* temp = new Noeud;
    temp -> coordCentre = valeur;
    temp -> gauche = NULL;
    temp -> droit = NULL;
    temp->min_x = coords[0]; temp->max_x = coords[1]; temp->min_y = coords[2]; temp->max_y = coords[3];
    return temp;
}


// La fonction d'aide (Récursive) appelée par la fonction membre inserer
void Arbre::inserer(const vector<double>& coords, Noeud*& ptr, int n)
{
    int ind;
    vector<double> valeur = {(coords[0] + coords[1])/2, (coords[2] + coords[3])/2}; // On associe la valeur des coordonnées x et y du centre du noeud

    if(n%2 == 0){  // Si n pair, séparation verticale : on compare la valeur de x
        ind = 0;
    }
    else{  // Si n impair, séparation horitonzale : on compare la valeur de y
        ind = 1;
    }

    // si l'arbre est vide, insérer comme racine
    if (!ptr){
        ptr = creeNoeud(valeur, coords);
        return;
    }
    // si la valeur est inférieure à la valeur de racine, insérer le noeud dans le sous-arbre gauche
    else if (valeur[ind] < ptr -> coordCentre[ind]){
        inserer(coords, ptr -> gauche, ++n);
    }
    // Sinon, insérer le noeud dans le sous-arbre droit
    else{
        inserer(coords, ptr -> droit, ++n);
    }
}


// Fonction récursive de découpe de l'arbre appelée par le constructeur
void Arbre::diviser(const vector<double>& coords, int n)
{
    double min_x = coords[0], max_x = coords[1], min_y = coords[2], max_y = coords[3];
    vector<double> coords1 = {min_x, max_x, min_y, max_y};
    vector<double> coords2 = {min_x, max_x, min_y, max_y};

    if(n == nbDivisions){  // Défini le nombre de découpes à faire pour créer l'arbre binaire de cherche
        return;
    }

    if(n%2 == 0){  // Découpe verticale
        double xtmp = (min_x + max_x) / 2;
        coords1[1] = xtmp;
        coords2[0] = xtmp;
    }
    else{  // Découpe horizontale
        double ytmp = (min_y + max_y) / 2;
        coords1[3] = ytmp;
        coords2[2] = ytmp;
    }

    // Ajout des noeuds à l'arbre binaire de cherche
    inserer(coords1);
    inserer(coords2);

    // Récursivité
    n++;
    diviser(coords1, n);
    diviser(coords2, n);
}


// La fonction d'aide (Récursive) appelée par la fonction membre insererTri
void Arbre::insererTri(Triangle* tri, Noeud*& ptr, double x, double y)
{
    if(ptr->gauche == NULL){  // Le bout de l'arbre est atteint
        if(find(ptr->Triangles.begin(), ptr->Triangles.end(), tri) == ptr->Triangles.end())
            ptr->Triangles.push_back(tri);  // On ajoute le triangle s'il n'appartient pas déjà à la liste
        return;
    }

    if(x <= ptr->gauche->max_x && x >= ptr->gauche->min_x && 
       y <= ptr->gauche->max_y && y >= ptr->gauche->min_y){  // Si le sommet est dans le noeud de gauche
        insererTri(tri, ptr->gauche, x, y);  // On continue la cherche dans le sous-arbre gauche
    }
    else{
        insererTri(tri, ptr->droit, x, y);  // On continue la cherche dans le sous-arbre droit
    }
}

 
// Fonction d'aide (Récursive) appelée par la fonction membre cherche
deque<Triangle*> Arbre::cherche (double x, double y, Noeud* ptr, Noeud*& prev, int n) const
{
    if(ptr->gauche == NULL){  // Si le noeud n'a pas d'enfant, c'est un noeud terminal
        // L'extrémité de l'arbre est atteinte
        return ptr->Triangles;
    }

    if(x <= ptr->gauche->max_x && x >= ptr->gauche->min_x && 
       y <= ptr->gauche->max_y && y >= ptr->gauche->min_y){  // Si le sommet est dans le noeud de gauche
        prev = ptr;
        return cherche(x, y, ptr->gauche, prev, n);  // On continue la cherche dans le sous-arbre gauche
    }
    else{
        prev = ptr;
        return cherche(x, y, ptr->droit, prev, n);  // On continue la cherche dans le sous-arbre droit
    }
}


// La fonction d'aide (Récursive) appelée par le destructeur
void Arbre::detruire (Noeud* ptr)
{
    if (!ptr)
        return;
     
    detruire (ptr -> gauche); // détruire le sous-arbre gauche
    detruire (ptr -> droit); // détruire le sous-arbre droit
    delete ptr; // détruire la racine
}