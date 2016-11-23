/*************************************************************************
                           Catalog  -  Description
                             -------------------
    début                : 17/11/2016
*************************************************************************/

#include "Catalog.h"

void Catalog::Display()
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

    if (listRoute->GetSize() == 0)
    { // Si la liste est vide alors on affiche un message et stop la fonction
        cout << "#\t" << "\tAucun trajet n'a été trouvé" << endl;
    }

    // On affiche l'ensemble des trajets

    for (unsigned int i = 0; i < listRoute->GetSize(); ++i)
    {
        cout << "#\t\t" << i + 1 << ". "; // Tabulation
        listRoute->GetElement(i)->Display();
        cout << endl;
    }
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
    // TODO Advance Query
    path = new ListRoute(DEFAULT_LIST_SIZE, false);
    visited = new ListRoute(DEFAULT_LIST_SIZE, false);
    arrivalRoutes = routes->GetArrivalTo(arrivalCity);
    nbFind = 0;

    ListRoute *baseRoutes = routes->GetDepartureFrom(departureCity);

    for (unsigned int i = 0; i < baseRoutes->GetSize(); ++i)
    {
        findPath(baseRoutes->GetElement(i));
    }

    delete baseRoutes;
    delete visited;
    delete path;
    delete arrivalRoutes;
}

void Catalog::findPath(Route *currentRoute)
{
    Route *tmp;
    ListRoute *previousRoutes;
    ListRoute *nextRoutes;

    bool isArrived = false;

    for (unsigned int i = 0; i < arrivalRoutes->GetSize() && !isArrived; ++i)
    {
        if (arrivalRoutes->GetElement(i) == currentRoute)
        {
            isArrived = true;
        }
    }

    if (isArrived)
    {
        nbFind++;
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
        previousRoutes = routes->GetArrivalTo(currentRoute->GetDeparture());

        for (unsigned int i = 0; i < previousRoutes->GetSize(); ++i)
        { // On ajoute les routes où on est passé
            visited->AddRoute(previousRoutes->GetElement(i));
        }

        path->AddRoute(currentRoute);

        nextRoutes = routes->GetDepartureFrom(currentRoute->GetArrival());

        for (unsigned int i = 0; i < nextRoutes->GetSize(); ++i)
        {
            tmp = nextRoutes->GetElement(i);

            if (!visited->Has(tmp))
            {
                findPath(tmp);
            }
        }

        for (unsigned int i = 0; i < previousRoutes->GetSize(); ++i)
        { // On enleve les routes où on est passé
            visited->DeleteRoute(previousRoutes->GetElement(i));
        }

        path->DeleteRoute(path->GetElement(path->GetSize() - 1));

        delete nextRoutes;
        delete previousRoutes;
    }
}


bool Catalog::AddRoute(const Route *route)
{
    /* Dans le cas où on verifie si la route existe
    for (unsigned int i = 0; i < routes->GetSize(); ++i)
    {
        if (*route == *routes->GetElement(i))
        { // Vérifie que la route n'existe pas déjà
            return false;
        }
    }*/

    routes->AddRoute(route);
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
