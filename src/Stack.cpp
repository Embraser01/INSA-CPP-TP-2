//
// Created by Lucas ONO on 21/11/16.
//

#include "Stack.h"

void Stack::push(const char *city) {
    if (top >= maxHeight) {
        maxHeight += DELTA_STACK_SIZE;
        char **newStack = new char *[maxHeight];

        // On recopie le contenu de l'ancien tableau
        for (unsigned int i = 0; i < maxHeight; i++) {
            newStack[i] = cities[i];//en effet on ne recopie que les pointeurs
        }

        delete[] cities;
        cities = newStack;
    }
    char *newCity = new char[strlen(city) + 1];
    strcpy(newCity, city);
    cities[top++] = newCity;
    delete output;
    output = new char[strlen(city) + 1];
    strcpy(output, city);
}

char *Stack::pop() {
    if (top > 0) {
        delete[] output;//delete null != free null
        output = new char[strlen(cities[top - 1]) +
                          1];//top est la premiere case vide, top -1 est la derniere case ajoute
        strcpy(output, cities[top - 1]);
        delete[] cities[--top];
        return output;
    } else {
        //pile deja vide
        return NULL;//erreur
    }
}

char *Stack::readI(unsigned int i) {
    delete[] output;
    output = new char[strlen(cities[top - (i + 1)])];
    strcpy(output, cities[top - (i + 1)]);
    return output;
}

unsigned int Stack::getTop() {
    return top;
}

Stack::Stack() {
    cities = new char *[DEFAULT_STACK_SIZE];
    top = 0;
    output = NULL;
    maxHeight = DEFAULT_STACK_SIZE;
#ifdef MAP
    cout << "Appel au constructeur de <Stack>" << endl;
#endif
}


Stack::~Stack() {
    while (pop() != NULL) {//bloc vide
    }
    delete[] output;
#ifdef MAP
    cout << "Appel au destructeur de <Stack>" << endl;
#endif
}