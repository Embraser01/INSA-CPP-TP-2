//
// Created by Lucas ONO on 21/11/16.
//

#include "Stack.h"

void Stack::push(const char * city)
{
    link * newTop;
    newTop = new link;
    newTop.cityName = new char[strlen(city) +1];
    strcpy(newTop.cityName,city);
    newTop.next = this->top;
    this.top = newTop;
}

char * Stack::pop()
{
    if(top != NULL)
    {
        link * newTop;
        char * city;
        newTop = top.next;
        city = new char[strlen(top.cityName)+1];
        strcpy(city,top.cityName);
        delete [] top.cityName;
        delete top;
        return city;
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
    while(pop()!=NULL)
    {//bloc vide
    }
#ifdef MAP
    cout << "Appel au destructeur de <Stack>" << endl;
#endif
}

