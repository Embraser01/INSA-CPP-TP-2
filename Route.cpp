/*************************************************************************
                           Route  -  Description
                             -------------------
    début                : 14/11/2016
    e-mail               : $EMAIL
*************************************************************************/

#include "Route.h"

#include <cstring>

Route::Route(const char *name)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}