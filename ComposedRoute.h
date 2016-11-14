/*************************************************************************
                           ComposedRoute  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#ifndef TP2_C_COMPOSEDROUTE_H
#define TP2_C_COMPOSEDROUTE_H

#include "Route.h"
#include "ListRoute.h"

class ComposedRoute: public Route {

public:

    virtual char* getDeparture() const;
    virtual char* getArrival() const;
    virtual void display();

    bool addSimpleRoute(const SimpleRoute* simpleRoute);

private:
    ListRoute* routes;
};

#endif //TP2_C_COMPOSEDROUTE_H
