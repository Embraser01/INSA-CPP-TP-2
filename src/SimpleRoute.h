#ifndef TP2_C_SIMPLEROUTE_H
#define TP2_C_SIMPLEROUTE_H

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "Route.h"


//------------------------------------------- Rôle de la classe
// Rôle : SimpleRoute a pour rôle
//       de représenter un trajet simple
//       contenant un moyen de transport,
//       une ville de départ et une ville d'arrivée
//-------------------------------------------

class SimpleRoute : public Route
{
//--------------------------------------- Méthodes publiques

  public:

    virtual char *GetDeparture() const;
    // Mode d'emploi :
    //      Cette méthode permet de récupérer la ville de départ

    virtual char *GetArrival() const;
    // Mode d'emploi :
    //      Cette méthode permet de récupérer la ville d'arrivée

    virtual void Display() const;
    // Mode d'emploi :
    //      Cette méthode permet d'afficher sur la sortie standard le trajet sous la forme suivante
    //          Départ de <Ville de départ> pour <Ville d'arrivée> en <Moyen de transport>

    virtual void out(std::ostream& os) const;
    //Paramètre <os> : le ostream ou nous allons écrire
    //Mode d'emploi:
    //      Cette méthode permet d'écrire sur la sortie fournie en paramètre


    //--------------------------------------- Redéfinition d'opérateurs

    //--------------------------------------- Constructeurs - destructeur

    SimpleRoute(const char *departure,
                const char *arrival,
                const char *transport);
    // Paramètre <departure> : Chaîne de caractère contenant la ville de départ
    // Paramètre <arrival> : Chaîne de caractère contenant la ville d'arrivée
    // Paramètre <transport> : Chaîne de caractère contenant le moyen de transport
    // Mode d'emploi :
    //      Ce constructeur crée une copie de chaque chaînes
    //      et l'affecte à l'attribut de la classe correspondant


    virtual ~SimpleRoute();
    // Destructeur


//--------------------------------------- Méthodes protégées ou privées

  protected:
  private:

//--------------------------------------- Attributs et types protégés ou privés

  protected:
  private:
    char *departure; // Ville de départ
    char *arrival; // Ville d'arrivée
    char *transport; // Moyen de transport
};

#endif //TP2_C_SIMPLEROUTE_H
