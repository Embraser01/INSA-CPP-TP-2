#ifndef TP2_C_COMPOSEDROUTE_H
#define TP2_C_COMPOSEDROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "ListRoute.h"
#include "Route.h"
#include "SimpleRoute.h"


//------------------------------------------- Rôle de la classe
// Rôle : ComposedRoute a pour rôle
//       de représenter un trajet composé
//       contenant une liste de <Route>
//-------------------------------------------

class ComposedRoute : public Route
{
//--------------------------------------- Méthodes publiques

  public:

    virtual char *GetDeparture() const;
    // Mode d'emploi :
    //      Cette méthode permet de récupérer la ville de départ du premier trajet de <routes>

    virtual char *GetArrival() const;
    // Mode d'emploi :
    //      Cette méthode permet de récupérer la ville d'arrivée du dernier trajet de <routes>

    virtual void Display() const;
    // Mode d'emploi :
    //      Cette méthode permet d'afficher sur la sortie standard le trajet
    //      en utilisant la fonction Display() de chaque route et en séparant chaque route par un '-'


    bool AddSimpleRoute(const SimpleRoute *simpleRoute);
    // Paramètre <simpleRoute> : SimpleRoute à insérer dans routes
    // Mode d'emploi :
    //      Cette méthode ajoute une SimpleRoute à <routes> en vérifiant
    //      que la ville de départ de la nouvelle route correspond à la ville d'arrivée actuelle.


    //--------------------------------------- Redéfinition d'opérateurs

    //--------------------------------------- Constructeurs - destructeur

    ComposedRoute(const SimpleRoute *route);
    // Paramètre <route> : Première route composant l'objet
    // Mode d'emploi :
    //      Ce constructeur crée une nouvelle ListRoute
    //      et ajoute <route> à cette liste


    virtual ~ComposedRoute();
    // Destructeur


//--------------------------------------- Méthodes protégées ou privées

  protected:
  private:

//--------------------------------------- Attributs et types protégés ou privés

  protected:
  private:
    // Liste des routes qui composent ce trajet.
    // N.B.: la liste reste coherente ici car on utilise pas DeleteRoute()
    ListRoute *routes;
};

#endif //TP2_C_COMPOSEDROUTE_H
