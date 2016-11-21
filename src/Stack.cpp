//
// Created by Lucas ONO on 21/11/16.
//

#include "Stack.h"

void Stack::push(const char * city)
{
    if(top>=maxHeight)
    {
        maxHeight+=DELTA_STACK_SIZE;
        char **newStack = new char *[maxHeight];

        // On recopie le contenu de l'ancien tableau
        for (unsigned int i = 0; i < maxHeight; i++)
        {
            newStack[i] = cities[i];
        }

        delete[] cities;
        cities = newStack;
    }
    char * newCity = new char[strlen(city) +1];
    strcpy(newCity,city);
    cities[top++] = newCity;
    delete topCity;
    topCity = new char[strlen(city) +1];
    strcpy(topCity,city);
}

char * Stack::pop()
{
    if(top > 0)
    {
        delete [] topCity;
        topCity = new char[strlen(cities[top-1])+1];
        strcpy(topCity,cities[top-1]);
        delete[] cities[--top];
        return topCity;
    } else
    {
        //pile deja vide
        return NULL;
    }
}

Stack::Stack()
{
    cities = new char*[DEFAULT_STACK_SIZE];
    top = 0;
    topCity = NULL;
    maxHeight = DEFAULT_STACK_SIZE;
#ifdef MAP
    cout << "Appel au constructeur de <Stack>" << endl;
#endif
}


Stack::~Stack()
{
    while(pop()!=NULL)
    {//bloc vide
    }
    delete[] topCity;
#ifdef MAP
    cout << "Appel au destructeur de <Stack>" << endl;
#endif
}