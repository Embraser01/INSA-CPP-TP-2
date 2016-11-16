//
// Created by gmarcelin on 14/11/16.
//


#include "ListRoute.h"

ListRoute::ListRoute(size_t sizeInit)
{
    this->cardMax = sizeInit;
    this->currentCard = 0;
    this->routes = new Route *[cardMax];
}

bool ListRoute::addRoute(Route *route)
{
    if (this->cardMax > this->currentCard)
    {
        routes[currentCard++] = route;
    }
    // TODO Faire en cas de tableau plein
    return false;

}

ListRoute *ListRoute::getDepartureFrom(const char *city)
{
    for (int i = 0; i++;);

    return NULL;
}

ListRoute *ListRoute::getArrivalTo(const char *city)
{
    return NULL;
}

size_t ListRoute::getSize() const
{
    return 0;
}

Route *ListRoute::getElement(size_t i)
{
    return NULL;

}

ListRoute::~ListRoute()
{

}