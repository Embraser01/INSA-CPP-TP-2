/*************************************************************************
                           ListRoute  -  Modélise une liste de trajet
                             -------------------
    début                : 14/11/16
*************************************************************************/

#ifndef TP2_C_LISTROUTE_H
#define TP2_C_LISTROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include <iostream>
#include <cstring>

#include "Route.h"


class ListRoute
{

//--------------------------------------- Méthodes publiques

public:


    bool addRoute(/*const ?? Passe pas avec une compilation non permissive*/ Route *route);

    ListRoute *getDepartureFrom(const char *city);
    //Contrat: city est une chaine de caracteres

    ListRoute *getArrivalTo(const char *city);
    //Contrat: city est une chaine de caracteres

    size_t getSize() const;

    Route *getElement(size_t i);


    //--------------------------------------- Redéfinition d'opérateurs


    //--------------------------------------- Constructeurs - destructeur

    ListRoute(size_t sizeInit);

    virtual ~ListRoute();

//--------------------------------------- Méthodes protégées ou privées

protected:
private:

//--------------------------------------- Attributs et types protégés ou privés

protected:
private:
    Route **routes; // Tableau contenant les routes
    size_t cardMax; // Taille du tableau
    unsigned int currentCard; // Nombre d'élements dans le tableau
};

#endif //TP2_C_LISTROUTE_H
