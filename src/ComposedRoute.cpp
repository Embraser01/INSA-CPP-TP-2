/*************************************************************************
                           ComposedRoute  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#include "ComposedRoute.h"

char *ComposedRoute::GetDeparture() const
{
    if (routes != NULL && routes->GetSize() > 0)
    {
        return routes->GetElement(0)->GetDeparture();
    }
    return NULL;
}

char *ComposedRoute::GetArrival() const
{
    if (routes != NULL && routes->GetSize() > 0)
    {
        return routes->GetElement(routes->GetSize() - 1)->GetArrival();
    }
    return NULL;
}


void ComposedRoute::Display()
{
    // On affiche l'ensemble des trajets

    for (unsigned int i = 0; i < routes->GetSize() - 1; ++i)
    { // Jusqu'à l'avant dernier
        routes->GetElement(i)->Display();
        cout << " — ";
    }

    routes->GetElement(routes->GetSize() - 1)->Display();
}


bool ComposedRoute::AddSimpleRoute(const SimpleRoute *simpleRoute)
{
    // On verifie que la derniere ville d'arrivée est celle de départ !

    if (strcmp(routes->GetElement(routes->GetSize() - 1)->GetArrival(), simpleRoute->GetDeparture()) == 0)
    {
        routes->AddRoute(simpleRoute);
        return true;
    }

    return false;
}


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