/*************************************************************************
                           Route  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#ifndef TP2_C_ROUTE_H
#define TP2_C_ROUTE_H

class Route {

public:

    virtual char* getDeparture() const = 0;
    virtual char* getArrival() const = 0;
    virtual void display() = 0;

    virtual ~Route();

};

#endif //TP2_C_ROUTE_H
