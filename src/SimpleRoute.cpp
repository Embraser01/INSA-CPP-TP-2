#include <iostream>
#include <cstring>

using namespace std;

#include "SimpleRoute.h"

//------------------------------------------- Constantes, statiques et types privés

//#define MAP

//------------------------------------------- Méthodes protégées et privées

//------------------------------------------- METHODES PUBLIC

char *SimpleRoute::GetDeparture() const
{
    return departure;
}

char *SimpleRoute::GetArrival() const
{
    return arrival;
}

void SimpleRoute::Display() const
{
    cout << "De " << departure << " vers " << arrival << " en " << transport;
}


//------------------------------------------- Redefinition d'operateurs

//------------------------------------------- Constructeurs - destructeur

SimpleRoute::SimpleRoute(const char *departure,
                         const char *arrival,
                         const char *transport)
{
    this->departure = new char[strlen(departure) + 1];
    strcpy(this->departure, departure);

    this->arrival = new char[strlen(arrival) + 1];
    strcpy(this->arrival, arrival);

    this->transport = new char[strlen(transport) + 1];
    strcpy(this->transport, transport);

#ifdef MAP
    cout << "Appel au constructeur de <SimpleRoute>" << endl;
#endif
}


SimpleRoute::~SimpleRoute()
{
    delete[] departure;
    delete[] arrival;
    delete[] transport;

#ifdef MAP
    cout << "Appel au destructeur de <SimpleRoute>" << endl;
#endif
}