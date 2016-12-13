#ifndef TP2_C_CATALOG_H
#define TP2_C_CATALOG_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "ListRoute.h"
#include "Route.h"

#include <string>

//------------------------------------------- Rôle de la classe
// Rôle : Catalog a pour rôle
//       de contenir une liste de Route
//       et de rechercher dans cette liste
//-------------------------------------------

class Catalog
{
//--------------------------------------- Méthodes publiques

  public:

    void Display();
    // Mode d'emploi :
    //      Cette méthode permet d'afficher sur la sortie standard les trajets présent dans le catalogue


    void Query(const std::string departureCity, const std::string arrivalCity);
    // Paramètre <departureCity> : Chaîne de caractère contenant la ville de départ
    // Paramètre <arrivalCity> : Chaîne de caractère contenant la ville d'arrivée
    // Mode d'emploi :
    //      Cette méthode affiche une liste de trajets répondant
    //      aux critères de recherche <departureCity> et <arrivalCity>


    void AdvanceQuery(const std::string departureCity, const std::string arrivalCity);
    // Paramètre <departureCity> : Chaîne de caractère contenant la ville de départ
    // Paramètre <arrivalCity> : Chaîne de caractère contenant la ville d'arrivée
    // Mode d'emploi :
    //      Cette méthode affiche une liste de trajets répondant
    //      aux critères de recherche <departureCity> et <arrivalCity>.
    //      Elle diffère de Query() par ça manière de rechercher :
    //          AdvanceQuery() recherche toutes les combinaisons
    //          de trajet existant entre <departureCity> et <arrivalCity>


    void AddRoute(const Route *route);
    // Paramètre <route> : Route à ajouter au tableau <routes>
    // Mode d'emploi :
    //      Cette méthode ajoute <route> à la liste

    const ListRoute * getRoutes();
    // Mode d'emploi :
    //      Cette methode nous permet d'acceder a une liste de trajets depuis l'exterieur


    //--------------------------------------- Redéfinition d'opérateurs

    //--------------------------------------- Constructeurs - destructeur

    Catalog();
    // Mode d'emploi :
    //      Ce constructeur initialise une nouvelle ListeRoute

    virtual ~Catalog();
    // Destructeur


//--------------------------------------- Méthodes protégées ou privées

  protected:
  private:
    void display(ListRoute *listRoute, const std::string departureCity, const std::string arrivalCity);
    // Paramètre <listRoute> : ListeRoute à afficher
    // Paramètre <departureCity> : Chaîne de caractère contenant la ville de départ (dans le cas d'une recherche)
    // Paramètre <arrivalCity> : Chaîne de caractère contenant la ville d'arrivée (dans le cas d'une recherche)
    // Mode d'emploi :
    //      Cette méthode affiche le contenu de <listRoute>, elle est privé
    //      car doit afficher uniquement les routes lui appartenant


    void findPath(Route *currentRoute);
    // Paramètre <currentRoute> : Route où démarrer la recherche
    // Mode d'emploi :
    //      Cette méthode est récursive,
    //      elle est utilisée par AdvanceQuery(),

//--------------------------------------- Attributs et types protégés ou privés

  protected:
  private:
    ListRoute *routes; // Liste des trajets existants

    // Pour AdvanceQuery() (recherche advancée)

    ListRoute *visited; // Liste des routes déjà visitées
    ListRoute *path; // Liste des chemins pris pour trouver une combinaison
    ListRoute *arrivalRoutes; // Liste contenant les routes pour arriver à <arrivalCity>
    unsigned int nbFind; // Nombre de combinaisons trouvées
};

#endif //TP2_C_CATALOG_H
