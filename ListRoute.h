
/*************************************************************************
                           ListRoute  -  Modélise une liste de trajet
                             -------------------
    début                : 14/11/16
    copyright            : (C) 2016 par ...
    e-mail               :
*************************************************************************/

//---------- Interface du module <ListRoute> (fichier ListRoute.h) -------------------
#ifndef TP2_C_LISTROUTE_H
#define TP2_C_LISTROUTE_H

//Pas sur !!! :)
#include <iostream>
#include <cstring>


class ListRoute
{
public:
    bool addRoute(const Route* route);

    ListRoute* getDepartureFrom(const char* city);

    ListRoute* getArrivalTo(const char* city);

    size_t getSize() const;

    Route* getElement(size_t i);

private:
    Route** routes;
    size_t size;


};


#endif //TP2_C_LISTROUTE_H
