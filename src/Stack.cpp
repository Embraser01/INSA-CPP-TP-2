//
// Created by Lucas ONO on 21/11/16.
//

#include "Stack.h"

void Stack::push(const char * city)
{
    Link * newTop;
    newTop = new Link;
    newTop->cityName = new char[strlen(city) +1];
    strcpy(newTop->cityName,city);
    newTop->next = this->top;
    this->top = newTop;
}

char * Stack::pop()
{
    if(top != NULL)
    {
        delete[] topData;
        Link * newTop;
        newTop = top->next;
        topData = new char[strlen(top->cityName)+1];
        strcpy(topData,top->cityName);
        delete [] top->cityName;
        delete top;
        top = newTop;
        return topData;
    }else
    {
        return NULL;
    }
}


Stack::Stack()
{
    top = NULL;
#ifdef MAP
    cout << "Appel au constructeur de <Stack>" << endl;
#endif
}


Stack::~Stack()
{
    delete[] topData;
    while(pop()!=NULL)
    {//bloc vide
    }
#ifdef MAP
    cout << "Appel au destructeur de <Stack>" << endl;
#endif
}

