/*************************************************************************
                           ComposedRoute  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#include "ComposedRoute.h"

char *ComposedRoute::getDeparture() const
{
    if (routes != NULL && routes->getSize() > 0)
    {
        return routes->getElement(0)->getDeparture();
    }
    return NULL;
}

char *ComposedRoute::getArrival() const
{
    if (routes != NULL && routes->getSize() > 0)
    {
        return routes->getElement(routes->getSize() - 1)->getArrival();
    }
    return NULL;
}


void ComposedRoute::display()
{
    // On affiche l'ensemble des trajets

    for (unsigned int i = 0; i < routes->getSize() - 1; ++i)
    { // Jusqu'à l'avant dernier
        routes->getElement(i)->display();
        cout << " — ";
    }

    routes->getElement(routes->getSize() - 1)->display();
}


bool ComposedRoute::addSimpleRoute(const SimpleRoute *simpleRoute)
{
    // On verifie que la derniere ville d'arrivée est celle de départ !

    if (strcasecmp(routes->getElement(routes->getSize() - 1)->getArrival(), simpleRoute->getDeparture()) == 0)
    {
        return routes->addRoute(simpleRoute);
    }

    return false;
}


ComposedRoute::ComposedRoute(const SimpleRoute *route)
{
    routes = new ListRoute();
    routes->addRoute(route);

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