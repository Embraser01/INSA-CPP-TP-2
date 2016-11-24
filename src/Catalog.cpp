#include <iostream>
#include <cstring>

using namespace std;

#include "Catalog.h"

//------------------------------------------- Constantes, statiques et types privés

//#define MAP

//------------------------------------------- Méthodes protégées et privées


void Catalog::display(ListRoute *listRoute, const char *departureCity, const char *arrivalCity)
{
    // On affiche le header

    if (departureCity != NULL && arrivalCity != NULL)
    { // Si c'est une recherche

        cout << "#\tTrajets existant entre " << departureCity << " et " << arrivalCity << " :" << endl;
    } else
    {
        cout << "#\tTrajets disponibles dans le catalogue" << endl;
    }

    // Maintenant la route

    if (listRoute->GetSize() == 0)
    { // Si la liste est vide alors on affiche un message
        cout << "#\t" << "\tAucun trajet n'a été trouvé" << endl;
    } else
    {
        // On affiche l'ensemble des trajets

        for (unsigned int i = 0; i < listRoute->GetSize(); ++i)
        {
            cout << "#\t\t" << i + 1 << ". "; // Tabulation
            listRoute->GetElement(i)->Display();
            cout << endl;
        }
    }
}

void Catalog::findPath(Route *currentRoute)
// Algorithme :
//      On utilise ici un DFS (https://fr.wikipedia.org/wiki/Algorithme_de_parcours_en_profondeur)
//      Mais à la place de regarder les sommets (les villes), on regarde les arrêtes (les trajets)
{
    Route *tmp;
    ListRoute *previousRoutes;
    ListRoute *nextRoutes;

    bool isArrived = false;

    // On commence par vérifier si on a trouvé une combinaison

    for (unsigned int i = 0; i < arrivalRoutes->GetSize() && !isArrived; ++i)
    {
        if (arrivalRoutes->GetElement(i) == currentRoute)
        {
            isArrived = true;
        }
    }


    if (isArrived)
    { // Si une nouvelle combinaison est trouvée

        nbFind++;

        // On affiche la liste ordonnée <path>

        size_t size = path->GetSize();
        cout << "PARCOURS " << nbFind << " : --------------------------------------------------------" << endl;
        for (size_t i = 0; i < size; i++)
        {
            path->GetElement(i)->Display();
            cout << endl;
        }

        // On affiche la dernière route
        currentRoute->Display();
        cout << endl
             << "FIN PARCOURS : --------------------------------------------------------" << endl;

    } else
    {
        // On considères les routes utilisées pour
        // arrivées ici comme visitées

        previousRoutes = routes->GetArrivalTo(currentRoute->GetDeparture());

        for (unsigned int i = 0; i < previousRoutes->GetSize(); ++i)
        { // On ajoute les routes où on est passé
            visited->AddRoute(previousRoutes->GetElement(i));
        }


        // On ajoute la route à la combinaison en cours

        path->AddRoute(currentRoute);


        // On vas visiter toutes les routes accessibles depuis <currentRoute>

        nextRoutes = routes->GetDepartureFrom(currentRoute->GetArrival());

        for (unsigned int i = 0; i < nextRoutes->GetSize(); ++i)
        {
            tmp = nextRoutes->GetElement(i);

            if (!visited->Has(tmp))
            {
                findPath(tmp);
            }
        }

        // On enlève les routes où on est passé

        for (unsigned int i = 0; i < previousRoutes->GetSize(); ++i)
        {
            visited->DeleteRoute(previousRoutes->GetElement(i));
        }


        // On enlève <currentRoute> de la pile <path>

        path->DeleteRoute(path->GetElement(path->GetSize() - 1));


        // On vide la mémoire

        delete nextRoutes;
        delete previousRoutes;
    }
}

//------------------------------------------- METHODES PUBLIC

void Catalog::Display()
{
    display(routes, NULL, NULL);
}

void Catalog::Query(const char *departureCity, const char *arrivalCity)
{
    // On créé une liste de la même taille du catalogue existant pour optimiser les performances
    // car pas besoin de recopier le tableau, et la recherche est stockée en mémoire que temporairement
    ListRoute *searchResults = new ListRoute(routes->GetSize(), false);

    Route *tmp;

    for (unsigned int i = 0; i < routes->GetSize(); ++i)
    {
        tmp = routes->GetElement(i);

        if (strcmp(tmp->GetDeparture(), departureCity) == 0
            && strcmp(tmp->GetArrival(), arrivalCity) == 0)
        { // Si les villes de départ et d'arrivée correspondent à la recherche

            searchResults->AddRoute(tmp);
        }
    }

    // On affiche les résultats de la requête
    display(searchResults, departureCity, arrivalCity);

    delete searchResults;
}

void Catalog::AdvanceQuery(const char *departureCity, const char *arrivalCity)
{
    // On initialise les différents attributs nécessaires pour la suite de la recherche

    path = new ListRoute(DEFAULT_LIST_SIZE, false);
    visited = new ListRoute(DEFAULT_LIST_SIZE, false);
    arrivalRoutes = routes->GetArrivalTo(arrivalCity);
    nbFind = 0;

    // On récupères les routes de départ
    ListRoute *baseRoutes = routes->GetDepartureFrom(departureCity);

    for (unsigned int i = 0; i < baseRoutes->GetSize(); ++i)
    { // Pour chaque route, on lance la recherche en profondeur

        findPath(baseRoutes->GetElement(i));
    }

    // On supprime les différents attributs nécessaires pour la suite de la recherche

    delete baseRoutes;
    delete visited;
    delete path;
    delete arrivalRoutes;
}

void Catalog::AddRoute(const Route *route)
{
    routes->AddRoute(route);
}


//------------------------------------------- Redefinition d'operateurs

//------------------------------------------- Constructeurs - destructeur

Catalog::Catalog()
{
    routes = new ListRoute();

#ifdef MAP
    cout << "Appel au contructeur de <Catalog>" << endl;
#endif
}

Catalog::~Catalog()
{
    delete routes;

#ifdef MAP
    cout << "Appel au destructeur de <Catalog>" << endl;
#endif
}
