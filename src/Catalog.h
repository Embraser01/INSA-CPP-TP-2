/*************************************************************************
                           Catalog  -  Contient l'ensemble des trajets
                                        existants
                             -------------------
    début                : 14/11/2016
*************************************************************************/

#ifndef TP2_C_CATALOG_H
#define TP2_C_CATALOG_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "ListRoute.h"
#include "Route.h"

class Catalog
{

//--------------------------------------- Méthodes publiques

public:

    void display();
    // Mode d'emploi : cette méthode permet d'afficher sur la sortie standard les trajets existants
    //


    void query(const char *departureCity, const char *arrivalCity);

    void advanceQuery(const char *departureCity, const char *arrivalCity);

    bool addRoute(const Route *route);


    //--------------------------------------- Redéfinition d'opérateurs


    //--------------------------------------- Constructeurs - destructeur


    virtual ~Catalog();


//--------------------------------------- Méthodes protégées ou privées

protected:
private:

//--------------------------------------- Attributs et types protégés ou privés

protected:
private:
    ListRoute *routes; // Liste des trajets existants
};

#endif //TP2_C_CATALOG_H
