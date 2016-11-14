/*************************************************************************
                           SimpleRoute  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#ifndef TP2_C_SIMPLEROUTE_H
#define TP2_C_SIMPLEROUTE_H

#include "Route.h"

class SimpleRoute : public Route
{

public:

    SimpleRoute(const char *departure,
                const char *arrival,
                const char *transport);

    char *getTransport() const
    {
        return transport;
    }

    virtual char *getDeparture() const
    {
        return departure;
    }

    virtual char *getArrival() const
    {
        return arrival;
    }

    virtual void display();

    virtual ~SimpleRoute();

private:
    char *departure;
    char *arrival;
    char *transport;
};

#endif //TP2_C_SIMPLEROUTE_H
