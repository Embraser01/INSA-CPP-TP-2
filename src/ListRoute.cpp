//
// Created by gmarcelin on 14/11/16.
//


#include "ListRoute.h"


void ListRoute::addRoute(const Route *route)
{
    if (this->cardMax <= this->currentCard)
    { // Si pas assez de place

        cardMax += DELTA_LIST_SIZE;

        Route **newList = new Route *[cardMax];

        // On recopie le contenu de l'ancien tableau
        for (unsigned int i = 0; i < currentCard; i++)
        {
            newList[i] = routes[i];
        }

        delete[] routes;
        routes = newList;
    }

    // Ici on cast pour pouvoir copier la valeur du pointeur dans le tableau
    // Ceci n'est pas autorisé sans cast avec l'option -fpermissive

    routes[currentCard++] = (Route *) route;
}

ListRoute *ListRoute::getDepartureFrom(const char *city)
{
    ListRoute *departure = new ListRoute();
    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (strcasecmp(routes[i]->getDeparture(), city) == 0)
        {
            departure->addRoute(routes[i]);
        }

    }

    return departure;
}

ListRoute *ListRoute::getArrivalTo(const char *city)
{
    ListRoute *arrival = new ListRoute();
    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (strcasecmp(routes[i]->getArrival(), city) == 0)
        {
            arrival->addRoute(routes[i]);
        }

    }

    return arrival;

}

size_t ListRoute::getSize() const
{
    return currentCard;
}

Route *ListRoute::getElement(size_t i) const
{
    return routes[i];
}


bool ListRoute::deleteRoute(Route *route)
{
    for (unsigned int i = 0; i < getSize(); i++)
    {
        if (routes[i] == route)
        {
            if (deleteRoutesOnDestruct) delete route;

            currentCard--;
            for (; i < getSize(); i++)
            {
                routes[i] = routes[i + 1];
            }
            routes[getSize()] = NULL;
            return true;

        }
    }
    return false;

}

bool ListRoute::has(Route *route)
{
    for (unsigned int i = 0; i < getSize(); i++)
    {
        if (routes[i] == route)
        {
            return true;
        }
    }
    return false;
}


ListRoute::ListRoute(size_t sizeInit, bool deleteRoutesOnDestruct)
{
    this->cardMax = sizeInit;
    this->currentCard = 0;
    this->routes = new Route *[cardMax];
    this->deleteRoutesOnDestruct = deleteRoutesOnDestruct;

#ifdef MAP
    cout << "Appel au constructeur de <ListRoute>" << endl;
#endif
}


ListRoute::~ListRoute()
{
    if (deleteRoutesOnDestruct)
    {
        for (unsigned int i = 0; i < currentCard; ++i)
        {
            delete routes[i];
        }
    }

    delete[]routes;

#ifdef MAP
    cout << "Appel au destructeur de <ListRoute>" << endl;
#endif
}

