#include <cstring>
#include <iostream>

using namespace std;

#include "ComposedRoute.h"

//------------------------------------------- Constantes, statiques et types privés

//#define MAP

//------------------------------------------- Méthodes protégées et privées

//------------------------------------------- METHODES PUBLIC

char *ComposedRoute::GetDeparture() const
{
    // <routes> est déjà initialisée avec au moins une routes
    return routes->GetElement(0)->GetDeparture();
}

char *ComposedRoute::GetArrival() const
{
    // <routes> est déjà initialisée avec au moins une routes
    return routes->GetElement(routes->GetSize() - 1)->GetArrival();
}

void ComposedRoute::Display() const
{
    // On affiche l'ensemble des trajets

    for (unsigned int i = 0; i < routes->GetSize() - 1; ++i)
    { // Jusqu'à l'avant dernier
        routes->GetElement(i)->Display();
        cout << " — ";
    }

    // On affiche le dernier
    routes->GetElement(routes->GetSize() - 1)->Display();
}

bool ComposedRoute::AddSimpleRoute(const SimpleRoute *simpleRoute)
{
    // On verifie que la dernière ville d'arrivée est celle de départ !

    if (strcmp(routes->GetElement(routes->GetSize() - 1)->GetArrival(), simpleRoute->GetDeparture()) == 0)
    {
        routes->AddRoute(simpleRoute);
        return true;
    }

    return false;
}

void ComposedRoute::out(std::ostream &os) const
{
    for (unsigned int i = 0; i < routes->GetSize() - 1; ++i)
    { // Jusqu'à l'avant dernier
        routes->GetElement(i)->out(os);
        os<< ";";
    }

    // On affiche le dernier
    routes->GetElement(routes->GetSize() - 1)->out(os);
}

//------------------------------------------- Redefinition d'operateurs

//------------------------------------------- Constructeurs - destructeur

ComposedRoute::ComposedRoute(const SimpleRoute *route)
{
    routes = new ListRoute();
    routes->AddRoute(route);

#ifdef MAP
    cout << "Appel au constructeur de <ComposedRoute>" << endl;
#endif
}

ComposedRoute::~ComposedRoute()
{
    delete routes;

#ifdef MAP
    cout << "Appel au destructeur de <ComposedRoute>" << endl;
#endif
}