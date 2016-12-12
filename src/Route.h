#ifndef TP2_C_ROUTE_H
#define TP2_C_ROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include <string>

//------------------------------------------- Rôle de la classe
// Rôle : Route a pour rôle
//       de représenter un trajet
//       avec au moins une ville de départ
//       et une ville d'arrivée.
//       La classe est abstraite
//-------------------------------------------

class Route
{
//--------------------------------------- Méthodes publiques

public:

    virtual std::string GetDeparture() const = 0;
    // Mode d'emploi :
    //      Cette méthode permet de récupérer la ville de départ
    //      Méthode virtuelle pure

    virtual std::string GetArrival() const = 0;
    // Mode d'emploi :
    //      Cette méthode permet de récupérer la ville d'arrivée
    //      Méthode virtuelle pure

    virtual void Display() const = 0;
    // Mode d'emploi :
    //      Cette méthode permet d'afficher sur la sortie standard le trajet
    //      Méthode virtuelle pure


    virtual bool IsComposed() const = 0;

    bool PassBy(string departureCity, string arrivalCity);

    //--------------------------------------- Redéfinition d'opérateurs

    //--------------------------------------- Constructeurs - destructeur

    virtual ~Route();
    // Destructeur


//--------------------------------------- Méthodes protégées ou privées

protected:
private:

//--------------------------------------- Attributs et types protégés ou privés

protected:
private:

};

#endif //TP2_C_ROUTE_H
