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
    if (departureCity != NULL && arrivalCity != NULL)
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
        cout << "#\t\t" << i + 1 << ". "; // Tabulation
        listRoute->getElement(i)->display();
        cout << endl;
    }
}


void Catalog::query(const char *departureCity, const char *arrivalCity)
{
    // On créé une liste de la même taille du catalogue existant pour optimiser les performances
    // car pas besoin de recopier le tableau, et la recherche est stockée en mémoire que temporairement
    ListRoute *searchResults = new ListRoute(routes->getSize(), false);

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
    path = new ListRoute(DEFAULT_LIST_SIZE, false);
    visited = new ListRoute(DEFAULT_LIST_SIZE, false);
    arrivalRoutes = routes->getArrivalTo(arrivalCity);
    nbFind = 0;

    ListRoute *baseRoutes = routes->getDepartureFrom(departureCity);

    for (unsigned int i = 0; i < baseRoutes->getSize(); ++i)
    {
        findPath(baseRoutes->getElement(i));
    }

    delete baseRoutes;
    delete visited;
    delete path;
    delete arrivalRoutes;
}

void Catalog::findPath(Route *currentRoute)
{
    Route *tmp;
    ListRoute *previousRoute;
    ListRoute *nextRoutes;

    bool isArrived = false;

    for (unsigned int i = 0; i < arrivalRoutes->getSize() && !isArrived; ++i)
    {
        if (arrivalRoutes->getElement(i) == currentRoute)
        {
            isArrived = true;
        }
    }

    if (isArrived)
    {
        nbFind++;
        size_t size = path->getSize();
        cout << "PARCOURS " << nbFind << " : --------------------------------------------------------" << endl;
        for (size_t i = 0; i < size; i++)
        {
            path->getElement(i)->display();
            cout << endl;
        }

        // On affiche la dernière route
        currentRoute->display();
        cout << endl
             << "FIN PARCOURS : --------------------------------------------------------" << endl;
/*
        // On enlève la dernière route
        path->deleteRoute(path->getElement(size - 1));*/

    } else
    {
        previousRoute = routes->getArrivalTo(currentRoute->getDeparture());

        for (unsigned int i = 0; i < previousRoute->getSize(); ++i)
        { // On ajoute les routes où on est passé
            visited->addRoute(previousRoute->getElement(i));
        }

        path->addRoute(currentRoute);

        nextRoutes = routes->getDepartureFrom(currentRoute->getArrival());

        for (unsigned int i = 0; i < nextRoutes->getSize(); ++i)
        {
            tmp = nextRoutes->getElement(i);

            if (!visited->has(tmp))
            {
                findPath(tmp);
            }
        }

        for (unsigned int i = 0; i < previousRoute->getSize(); ++i)
        { // On enleve les routes où on est passé
            visited->deleteRoute(previousRoute->getElement(i));
        }

        path->deleteRoute(path->getElement(path->getSize() - 1));

        delete nextRoutes;
        delete previousRoute;
    }
}


bool Catalog::addRoute(const Route *route)
{
    /* Dans le cas où on verifie si la route existe
    for (unsigned int i = 0; i < routes->getSize(); ++i)
    {
        if (*route == *routes->getElement(i))
        { // Vérifie que la route n'existe pas déjà
            return false;
        }
    }*/

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
