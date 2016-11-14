/*************************************************************************
                           SimpleRoute  -  Représente un trajet simple
                             -------------------
    début                : 14/11/2016
*************************************************************************/

#ifndef TP2_C_SIMPLEROUTE_H
#define TP2_C_SIMPLEROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "Route.h"

class SimpleRoute : public Route
{

//--------------------------------------- Méthodes publiques

public:


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
    // Mode d'emploi : cette méthode permet d'afficher sur la sortie standard le trajet sous la forme suivante
    //                  Départ de <Gare départ> pour <Gare arrivée> par <Moyen de transport>


    //--------------------------------------- Redéfinition d'opérateurs


    //--------------------------------------- Constructeurs - destructeur

    SimpleRoute(const char *departure,
                const char *arrival,
                const char *transport);


    virtual ~SimpleRoute();


//--------------------------------------- Méthodes protégées ou privées

protected:
private:

//--------------------------------------- Attributs et types protégés ou privés

protected:
private:
    char *departure; // Gare de départ
    char *arrival; // Gare d'arrivée
    char *transport; // Moyen de transport
};

#endif //TP2_C_SIMPLEROUTE_H
