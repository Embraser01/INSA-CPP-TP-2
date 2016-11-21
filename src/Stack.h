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


typedef struct Link
{
    char *cityName;
    Link *next;
} Link;

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
    Link* top;
    char *topData;
};


#endif //TP_CPP_2_STACK_H
