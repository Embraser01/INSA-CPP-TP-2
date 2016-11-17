/*************************************************************************
                           Catalog  -  Contient l'ensemble des trajets
                                        existants
                             -------------------
    début                : 14/11/2016
*************************************************************************/

#ifndef TP2_C_CATALOG_H
#define TP2_C_CATALOG_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include <iostream>
#include <cstring>

using namespace std;

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

    void addRoute(const Route *route);


    //--------------------------------------- Redéfinition d'opérateurs


    //--------------------------------------- Constructeurs - destructeur


    Catalog();

    virtual ~Catalog();


//--------------------------------------- Méthodes protégées ou privées

protected:
private:
    void display(ListRoute* listRoute, const char *departureCity, const char *arrivalCity);
    // Cette méthode affiche le contenu de listRoute, elle est privé
    // car doit afficher uniquement les routes lui appartenant


//--------------------------------------- Attributs et types protégés ou privés

protected:
private:
    ListRoute *routes; // Liste des trajets existants
};

#endif //TP2_C_CATALOG_H
