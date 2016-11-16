/*************************************************************************
                           Route  -  Représente un trajet (classe abstraite)
                             -------------------
    début                : 14/11/2016
*************************************************************************/

#ifndef TP2_C_ROUTE_H
#define TP2_C_ROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

class Route {

//--------------------------------------- Méthodes publiques

public:

    virtual char *getDeparture() const = 0;

    virtual char *getArrival() const = 0;

    virtual void display() = 0;
    // Mode d'emploi : cette méthode permet d'afficher sur la sortie standard le trajet
    //      Méthode virtuelle pure


    //--------------------------------------- Redéfinition d'opérateurs


    //--------------------------------------- Constructeurs - destructeur

    virtual ~Route();


//--------------------------------------- Méthodes protégées ou privées

protected:
private:

//--------------------------------------- Attributs et types protégés ou privés

protected:
private:

};

#endif //TP2_C_ROUTE_H
