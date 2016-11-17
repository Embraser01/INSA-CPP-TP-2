/*************************************************************************
                           Route  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#include "Route.h"


Route::~Route()
{
#ifdef MAP
    cout << "Appel au destructeur de <Route>" << endl;
#endif
}