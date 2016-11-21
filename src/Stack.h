/*************************************************************************
                           Stack  -  une file (structure de donnees)
                             -------------------
    début                : 14/11/2016
*************************************************************************/

#ifndef TP_CPP_2_STACK_H
#define TP_CPP_2_STACK_H



//------------------------------------------- Interfaces utilisées, Types, Constantes

#include <iostream>
#include <cstring>

#define DEFAULT_STACK_SIZE 10


#define DELTA_STACK_SIZE 5
//TODO utiliser tableau dynamique au lieu de la liste


class Stack
{

//--------------------------------------- Méthodes publiques

public:

    Stack();

    void push(const char *city);

    char *pop();

    virtual ~Stack();


//--------------------------------------- Méthodes protégées ou privées

protected:
private:

//--------------------------------------- Attributs et types protégés ou privés

protected:
private:
    char ** cities;
    int top;//the first empty cell of the table
    size_t maxHeight;
    char * topCity;
};


#endif //TP_CPP_2_STACK_H
