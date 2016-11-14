//
// Created by gmarcelin on 14/11/16.
//


#include "ListRoute.h"

ListRoute::ListRoute(size_t sizeInit)
{
    this->cardMax=sizeInit;
    this->currentCard=0;
    this->routes = new Route*[cardMax];
}

bool ListRoute::addRoute(const Route* route)
{
    if (this->cardMax > this->currentCard){
        routes [currentCard++]= route;
    }
    else {

    }

}

ListRoute* ListRoute::getDepartureFrom(const char* city)
{
    for (int i=0;i++;)
}

ListRoute* ListRoute::getArrivalTo(const char* city)
{
}

size_t ListRoute::getSize() const
{
}

Route* ListRoute::getElement(size_t i)
{

}