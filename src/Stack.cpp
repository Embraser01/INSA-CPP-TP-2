//
// Created by Lucas ONO on 21/11/16.
//

#include "Stack.h"

void Stack::push(const char *city)
{
    if (top >= maxHeight)
    {
        maxHeight += DELTA_STACK_SIZE;
        char **newStack = new char *[maxHeight];

        // On recopie le contenu de l'ancien tableau
        for (unsigned int i = 0; i < top; i++)
        {
            newStack[i] = cities[i];
        }

        delete[] cities;
        cities = newStack;
    }

    char *newCity = new char[strlen(city) + 1];
    strcpy(newCity, city);

    cities[top++] = newCity;
}

char *Stack::pop()
{
    if (cities != NULL)
    {
        delete[] topCity;

        top--;

        topCity = new char[strlen(cities[top]) + 1];
        strcpy(topCity, cities[top]);


        delete[] cities[top];
        cities[top] = NULL;


        if (top == 0)
        { // Si la liste est vide, on supprime le tableau

            delete[] cities;
        }
        return topCity;
    } else
    {
        //pile deja vide
        return NULL;
    }
}

const char *Stack::readI(unsigned int i) {
    if (i < top) {
        return cities[top - 1 - i];
    }
    return NULL;
}

unsigned int Stack::getSize() {
    return top;
}

Stack::Stack() {
    maxHeight = 0;
    top = 0;
    topCity = NULL;
    cities = NULL;

#ifdef MAP
    cout << "Appel au constructeur de <Stack>" << endl;
#endif
}


Stack::~Stack()
{
    while (pop() != NULL)
    {//bloc vide
    }
    delete[] topCity;

#ifdef MAP
    cout << "Appel au destructeur de <Stack>" << endl;
#endif
}

