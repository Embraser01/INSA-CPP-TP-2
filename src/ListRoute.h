#ifndef TP2_C_LISTROUTE_H
#define TP2_C_LISTROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "Route.h"

const int DEFAULT_LIST_SIZE = 10; // Taille par defaut de la liste
const int DELTA_LIST_SIZE = 5; // Lorsque la liste est trop petite, on rajoute DELTA_LIST_SIZE cases


//------------------------------------------- Rôle de la classe
// Rôle : ListRoute a pour rôle
//       de contenir une liste de Route
//-------------------------------------------

class ListRoute
{
//--------------------------------------- Méthodes publiques

  public:

    void AddRoute(const Route *route);
    // Paramètre <route> : Route à ajouter au tableau <routes>
    // Mode d'emploi :
    //      Cette méthode ajoute <route> au tableau dynamique <routes>


    ListRoute *GetDepartureFrom(const char *city);
    // Paramètre <city> : Chaîne de caractère contenant la ville de départ
    // Mode d'emploi :
    //      Cette méthode permet de récupérer une liste de tous les trajets qui partent de <city>


    ListRoute *GetArrivalTo(const char *city);
    // Paramètre <arrival> : Chaîne de caractère contenant la ville d'arrivée
    // Mode d'emploi :
    //      Cette méthode permet de récupérer une liste de tous les trajets qui arrivent à <city>


    size_t GetSize() const;
    // Mode d'emploi :
    //      Cette méthode renvoie le nombre de route dans la liste


    Route *GetElement(size_t i) const;
    // Paramètre <i> : Index du tableau
    // Mode d'emploi :
    //      Cette méthode renvoie le l'élément d'index i dans le tableau <routes>
    //      Si l'élement n'existe pas, NULL est renvoyé


    bool DeleteRoute(Route *route);
    // Paramètre <route> : Route à supprimer du tableau
    // Mode d'emploi :
    //      Cette méthode enlève <route> de la liste,
    //      Si <deleteRoutesOnRemove>, alors <route> est également supprimé
    //      Si <route> n'est pas dans la liste, false est renvoyé


    bool Has(Route *route);
    // Mode d'emploi :
    //      Cette méthode renvoie true si la route
    //      est présente dans la liste, false sinon


    //--------------------------------------- Redéfinition d'opérateurs


    //--------------------------------------- Constructeurs - destructeur

    ListRoute(size_t sizeInit = DEFAULT_LIST_SIZE, bool deleteRouteOnRemove = true);
    // Paramètre <sizeInit> : Taille de la liste lors de l'initialisation
    // Paramètre <deleteRouteOnRemove> : Si on doit supprimer une route quand on l'enlève de la liste
    // Mode d'emploi :
    //      Ce constructeur initialise un tableau de <sizeInit> élements


    virtual ~ListRoute();
    // Destructeur

    //--------------------------------------- Méthodes protégées ou privées

  protected:
  private:

    //--------------------------------------- Attributs et types protégés ou privés

  protected:
  private:
    Route **routes; // Tableau contenant les routes
    size_t cardMax; // Taille du tableau
    unsigned int currentCard; // Nombre d'élements dans le tableau
    bool deleteRouteOnRemove; // Flag pour savoir si on doit supprimer une route quand on l'enlève de la liste
};

#endif //TP2_C_LISTROUTE_H
