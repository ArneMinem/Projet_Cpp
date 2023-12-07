#include "Point.h" // Pour l'associer au fichier.h
#include <iostream> // Pour définir les flots de données en entrée et en sortie
#include <string> // Pour utiliser le type string
#include <fstream>

using namespace std;

Point::Point(void) : lat(0.0), lon(0.0), alt(0.0) {
    // Constructor for latitude, longitude and altitude
}

Point::Point(double lat, double lon, double alt) : lat(lat), lon(lon), alt(alt) {
    // Constructor for latitude, longitude and altitude
}

Point::~Point(){
    // Destructeur
}

istream& operator>>(istream& stream, Point& p)
{
  char dump;
  stream >> dump >> p.lat >> dump >> p.lon >> dump >> p.alt >> dump ;
  return stream; 
}