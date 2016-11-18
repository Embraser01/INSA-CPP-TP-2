/*************************************************************************
                           Catalog  -  Description
                             -------------------
    début                : 17/11/2016
*************************************************************************/

#include "Catalog.h"

void Catalog::display()
{
    display(routes, NULL, NULL);
}

void Catalog::display(ListRoute *listRoute, const char *departureCity, const char *arrivalCity)
{
    if (departureCity != NULL)
    { // Si c'est une recherche

        cout << "#\tTrajets existant entre " << departureCity << " et " << arrivalCity << " :" << endl;
    } else
    {
        cout << "#\tTrajets disponibles dans le catalogue" << endl;
    }

    if (listRoute->getSize() == 0)
    { // Si la liste est vide alors on affiche un message et stop la fonction
        cout << "#\t" << "\tAucun trajet n'a été trouvé" << endl;
    }

    // On affiche l'ensemble des trajets

    for (unsigned int i = 0; i < listRoute->getSize(); ++i)
    {
        cout << "#\t\t"; // Tabulation
        listRoute->getElement(i)->display();
        cout << endl;
    }
}


void Catalog::query(const char *departureCity, const char *arrivalCity)
{
    // On créé une liste de la même taille du catalogue existant pour optimiser les performances
    // car pas besoin de recopier le tableau, et la recherche est stockée en mémoire que temporairement
    ListRoute *searchResults = new ListRoute(routes->getSize());

    Route *tmp;

    for (unsigned int i = 0; i < routes->getSize(); ++i)
    {
        tmp = routes->getElement(i);

        if (strcasecmp(tmp->getDeparture(), departureCity) == 0
            && strcasecmp(tmp->getArrival(), arrivalCity) == 0)
        { // Si les villes de départ et d'arrivée correspondent à la recherche

            searchResults->addRoute(tmp);
        }
    }

    // On affiche les résultats de la requête
    display(searchResults, departureCity, arrivalCity);

    delete searchResults;
}

void Catalog::advanceQuery(const char *departureCity, const char *arrivalCity)
{
    // TODO Advance query

    query(departureCity, arrivalCity);
}


bool Catalog::addRoute(const Route *route)
{
    for (unsigned int i = 0; i < routes->getSize(); ++i)
    {
        if (*route == *routes->getElement(i))
        { // Vérifie que la route n'existe pas déjà
            return false;
        }
    }

    routes->addRoute(route);
    return true;
}

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
