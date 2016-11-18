//
// Created by gmarcelin on 14/11/16.
//


#include "ListRoute.h"


/*void ListRoute::addRoute(const Route *route)
{
    if (this->cardMax > this->currentCard)
    {
        // Ici on cast pour pouvoir copier la valeur du pointeur dans le tableau
        // Ceci n'est pas autorisé sans cast avec l'option -fpermissive

        routes[currentCard++] = (Route *) route;
    } else
    {

        Route **newList = new Route *[cardMax + DELTA_LIST_SIZE];
        for (int i = 0; i < cardMax; i++)
        {
            newList[i] = routes[i];
        }
        cardMax += DELTA_LIST_SIZE;
        newList[currentCard++] = (Route *) route;
        routes = newList;
    }
}*/

void ListRoute::addRoute(const Route *route)
{
    if (this->cardMax <= this->currentCard)
    { // Si pas assez de place

        cardMax += DELTA_LIST_SIZE;

        Route **newList = new Route *[cardMax];

        // On recopie le contenu de l'ancien tableau
        for (int i = 0; i < currentCard; i++)
        {
            newList[i] = routes[i];
        }

        delete [] routes;
        routes = newList;
    }

    // Ici on cast pour pouvoir copier la valeur du pointeur dans le tableau
    // Ceci n'est pas autorisé sans cast avec l'option -fpermissive

    routes[currentCard++] = (Route *) route;
}

ListRoute *ListRoute::getDepartureFrom(const char *city)
{
    ListRoute departure = ListRoute(DEFAULT_LIST_SIZE);
    for (int i = 0; i < cardMax; i++)
    {
        if (routes[i]->getDeparture() == city)
        {

        }

    }

    return NULL;
}

ListRoute *ListRoute::getArrivalTo(const char *city)
{
    return NULL;
}

size_t ListRoute::getSize() const
{
    return currentCard;
}

Route *ListRoute::getElement(size_t i)
{
    return routes[i];

}

ListRoute::ListRoute(size_t sizeInit)
{
    this->cardMax = sizeInit;
    this->currentCard = 0;
    this->routes = new Route *[cardMax];

#ifdef MAP
    cout << "Appel au constructeur de <ListRoute>" << endl;
#endif
}


ListRoute::~ListRoute()
{
#ifdef MAP
    cout << "Appel au destructeur de <ListRoute>" << endl;
#endif
}

