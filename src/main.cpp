using namespace std;

#include <iostream>

#define MAP
#define BUFFER_SIZE 100
#define MAX_CONSOLE_LINES 50


#include "Catalog.h"


void clearConsole()
{ // Permet d'effacer le contenu du terminal à defaut de pouvoir utiliser une autre lib...

    for (int i = 0; i < MAX_CONSOLE_LINES; ++i)
    {
        cout << endl;
    }
}


int main()
{
    char buff[BUFFER_SIZE] = {'\0'};

    Catalog *catalog = new Catalog();

    clearConsole();

    while (strcmp(buff, "q") != 0)
    { // Tant que l'utilisateur ne veut pas quitter

        cout << "#--------------------------------------------------------" << endl
             << "#\t Ultra promo voyage" << endl
             << "#\t" << "\t1. Ajouter un trajet au catalogue" << endl
             << "#\t" << "\t2. Consulter le catalogue" << endl
             << "#\t" << "\t3. Rechercher un parcours (simple)" << endl
             << "#\t" << "\t4. Rechercher un parcours (avancée)" << endl
             << "#\t" << endl
             << "#\t" << endl
             << "#\t" << endl
             << "#\t" << "\ta. A propos" << endl
             << "#\t" << "\tq. Quitter l'application" << endl
             << "#--------------------------------------------------------" << endl
             << "Rentrez l'option voulue :";
        cin >> buff;

        if (buff[0] == 'q')
        { // Si il veut quitter, on quitte imediatement
            break;
        }

        switch (buff[0])
        {

            case '1':
                break;

            default:
                break;
        }
    }

    cin >> buff;
    return 0;
}