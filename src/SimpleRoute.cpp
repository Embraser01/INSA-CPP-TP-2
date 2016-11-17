/*************************************************************************
                           SimpleRoute  -  description
                             -------------------
    début                : 14 Nov 2016
    copyright            : (C) 2016 par lucasono
    e-mail               : lucas.okumura-ono@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <SimpleRoute> (fichier SimpleRoute.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "SimpleRoute.h"

#define MAP
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
SimpleRoute::SimpleRoute(const char *departure,
                         const char *arrival,
                         const char *transport)
{
    this->departure = new char[strlen(departure) + 1];
    strcpy(this->departure, departure);

    this->arrival = new char[strlen(arrival) + 1];
    strcpy(this->arrival, arrival);

    this->transport = new char[strlen(transport) + 1];
    strcpy(this->transport, arrival);

#ifdef MAP
    cout << "Appel au constructeur de <SimpleRoute>" << endl;
#endif
}

void SimpleRoute::display()
{
    cout << "De " << departure << " vers " << arrival;
}


SimpleRoute::~SimpleRoute()
{
    delete[] departure;
    delete[] arrival;
    delete[] transport;
}
//---------------------------------------------------- Fonctions publiques
//type Nom ( liste de paramètres )
// Algorithme :
//
//{
//} //----- fin de Nom