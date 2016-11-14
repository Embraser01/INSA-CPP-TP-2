/*************************************************************************
                           Catalog  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#ifndef TP2_C_CATALOG_H
#define TP2_C_CATALOG_H

#include "ListRoute.h"
#include "Route.h"

class Catalog
{

public:

    void display();

    void query(const char* departureCity,const char* arrivalCity);
    void advanceQuery(const char* departureCity,const char* arrivalCity);

    bool addRoute(const Route* route);

    virtual ~Catalog();

private:
    ListRoute* routes;
};

#endif //TP2_C_CATALOG_H
