//
// Created by gmarcelin on 14/11/16.
//


#include "ListRoute.h"


void ListRoute::AddRoute(const Route *route)
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

ListRoute *ListRoute::GetDepartureFrom(const char *city)
{
    ListRoute *departureRoutes = new ListRoute(DEFAULT_LIST_SIZE, false);
    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (strcmp(routes[i]->GetDeparture(), city) == 0)
        {
            departureRoutes->AddRoute(routes[i]);
        }
    }

    return departureRoutes;
}

ListRoute *ListRoute::GetArrivalTo(const char *city)
{
    ListRoute *arrivalRoutes = new ListRoute(DEFAULT_LIST_SIZE, false);
    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (strcmp(routes[i]->GetArrival(), city) == 0)
        {
            arrivalRoutes->AddRoute(routes[i]);
        }

    }

    return arrivalRoutes;

}

size_t ListRoute::GetSize() const
{
    return currentCard;
}

Route *ListRoute::GetElement(size_t i) const
{
    return routes[i];
}


bool ListRoute::DeleteRoute(Route *route)
{
    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (routes[i] == route)
        {
            if (deleteRoutesOnDestruct)
            {
                delete route;
            }

            currentCard--;
            for (; i < currentCard; i++)
            {
                routes[i] = routes[i + 1];
            }
            routes[currentCard] = NULL;
            return true;
        }
    }
    return false;

}

bool ListRoute::Has(Route *route)
{
    for (unsigned int i = 0; i < GetSize(); i++)
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

