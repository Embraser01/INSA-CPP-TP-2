#include <iostream>
#include <string>

using namespace std;

#include "SimpleRoute.h"

//------------------------------------------- Constantes, statiques et types privés

//#define MAP

//------------------------------------------- Méthodes protégées et privées

//------------------------------------------- METHODES PUBLIC

string SimpleRoute::GetDeparture() const
{
    return departure;
}

string SimpleRoute::GetArrival() const
{
    return arrival;
}

void SimpleRoute::Display() const
{
    cout << "De " << departure << " vers " << arrival << " en " << transport;
}


//------------------------------------------- Redefinition d'operateurs

//------------------------------------------- Constructeurs - destructeur

SimpleRoute::SimpleRoute(const string departure,
                         const string arrival,
                         const string transport)
{
    this->departure = departure;
    this->arrival = arrival;
    this->transport = transport;

#ifdef MAP
    cout << "Appel au constructeur de <SimpleRoute>" << endl;
#endif
}


SimpleRoute::~SimpleRoute()
{

#ifdef MAP
    cout << "Appel au destructeur de <SimpleRoute>" << endl;
#endif
}