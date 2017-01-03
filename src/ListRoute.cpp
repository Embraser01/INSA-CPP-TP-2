#include <iostream>
#include <cstring>

using namespace std;

#include "ListRoute.h"

//------------------------------------------- Constantes, statiques et types privés

//#define MAP

//------------------------------------------- Méthodes protégées et privées

//------------------------------------------- METHODES PUBLIC

void ListRoute::AddRoute(const Route *route)
{
    if (this->cardMax <= this->currentCard)
    { // Si pas assez de place, on agrandit le tableau de DELTA_LIST_SIZE

        cardMax += DELTA_LIST_SIZE;

        Route **newList = new Route *[cardMax];

        // On recopie le contenu de l'ancien tableau
        for (unsigned int i = 0; i < currentCard; i++)
        {
            newList[i] = routes[i];
        }

        delete[] routes;
        routes = newList;
    }

    // Ici on cast pour pouvoir copier la valeur du pointeur dans le tableau
    // Ceci n'est pas autorisé sans cast avec l'option -fpermissive

    routes[currentCard++] = (Route *) route;
}

ListRoute *ListRoute::GetDepartureFrom(const string city)
{
    // On crée une nouvelle liste qui va contenir les routes partant de <city>
    // Cette nouvelle liste ne supprimera pas les routes lors de sa suppression
    ListRoute *departureRoutes = new ListRoute(DEFAULT_LIST_SIZE, false);

    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (routes[i]->GetDeparture() == city)
        {
            departureRoutes->AddRoute(routes[i]);
        }
    }

    return departureRoutes;
}

ListRoute *ListRoute::GetArrivalTo(const string city)
{
    // On crée une nouvelle liste qui va contenir les routes arrivant à <city>
    // Cette nouvelle liste ne supprimera pas les routes lors de sa suppression
    ListRoute *arrivalRoutes = new ListRoute(DEFAULT_LIST_SIZE, false);

    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (routes[i]->GetArrival() == city)
        {
            arrivalRoutes->AddRoute(routes[i]);
        }
    }

    return arrivalRoutes;
}

size_t ListRoute::GetSize() const
{
    return currentCard;
}

Route *ListRoute::GetElement(size_t i) const
{
    if (i < currentCard)
    {
        return routes[i];
    }
    return NULL;
}

bool ListRoute::DeleteRoute(Route *route)
{
    for (unsigned int i = 0; i < currentCard; i++)
    {
        if (routes[i] == route)
        { // Même addresse

            if (deleteRouteOnRemove)
            {
                delete route;
            }

            currentCard--;

            for (; i < currentCard; i++)
            { // On décale les routes d'après
                routes[i] = routes[i + 1];
            }

            // Par précaution on met la dernière route à NULL
            routes[currentCard] = NULL;
            return true;
        }
    }

    // Si aucune suppression
    return false;

}

bool ListRoute::Has(Route *route)
{
    for (unsigned int i = 0; i < GetSize(); i++)
    {
        if (routes[i] == route)
        {
            return true;
        }
    }
    return false;
}


ListRoute *ListRoute::FilterSelect(int n, int m)
{
    if (n>m||n<0){
        return nullptr;
    }
    ListRoute *Filter= new ListRoute(DEFAULT_LIST_SIZE, false);
    for (unsigned int i=(unsigned int)n;i<m;i++){
        Filter->AddRoute(this->GetElement(i));
    }
    return Filter;
}

//------------------------------------------- Redefinition d'operateurs

//------------------------------------------- Constructeurs - destructeur

ListRoute::ListRoute(size_t sizeInit, bool deleteRouteOnRemove)
{
    this->cardMax = sizeInit;
    this->currentCard = 0;
    this->routes = new Route *[cardMax];
    this->deleteRouteOnRemove = deleteRouteOnRemove;

#ifdef MAP
    cout << "Appel au constructeur de <ListRoute>" << endl;
#endif
}


ListRoute::~ListRoute()
{
    if (deleteRouteOnRemove)
    { // On supprime chaque route si besoin

        for (unsigned int i = 0; i < currentCard; ++i)
        {
            delete routes[i];
        }
    }

    delete[] routes;

#ifdef MAP
    cout << "Appel au destructeur de <ListRoute>" << endl;
#endif
}



