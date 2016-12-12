#include <iostream>

using namespace std;

#include "Route.h"

//------------------------------------------- Constantes, statiques et types privés

//#define MAP

//------------------------------------------- Méthodes protégées et privées

//------------------------------------------- METHODES PUBLIC

//------------------------------------------- Redefinition d'operateurs

//------------------------------------------- Constructeurs - destructeur

Route::~Route()
{
#ifdef MAP
    cout << "Appel au destructeur de <Route>" << endl;
#endif
}