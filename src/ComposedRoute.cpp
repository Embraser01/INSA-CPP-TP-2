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
    cout << "WIP" << endl;
}


bool ComposedRoute::addSimpleRoute(const SimpleRoute *simpleRoute)
{
    return false;
}


ComposedRoute::ComposedRoute()
{

}

ComposedRoute::~ComposedRoute()
{

}