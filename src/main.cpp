using namespace std;

#include <iostream>

#define MAP
#define BUFFER_SIZE 1000
#define MAX_CONSOLE_LINES 30


#include "Catalog.h"
#include "SimpleRoute.h"
#include "ComposedRoute.h"


char buff[BUFFER_SIZE] = {'\0'};


void clearConsole()
{ // Permet d'effacer le contenu du terminal à defaut de pouvoir utiliser une autre lib...

    for (int i = 0; i < MAX_CONSOLE_LINES; ++i)
    {
        cout << endl;
    }
}


void typeToContinue()
{
    cout << "Appuyer sur une touche pour continuer..." << endl;
    cin.get();
}


SimpleRoute *getSimpleRoute(char *string)
{
    char *save_ptr;

    // On recupère le moyen de transport (avant le '(')
    char *transport = strtok_r(buff, "(", &save_ptr);

    // On recupère la ville de départ (avant le ',')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *departure = strtok_r(NULL, ",", &save_ptr);


    // On recupère la ville d'arrivée (avant le ')')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *arrival = strtok_r(NULL, ")", &save_ptr);


    if (!strlen(transport) || !strlen(departure) || !strlen(arrival)) return NULL;

    return new SimpleRoute(departure, arrival, transport);
}

void addRoute(Catalog *catalog)
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Ajouter un trajet" << endl
         << "#\t" << endl
         << "#\t" << "\tAjoutez un trajet sous la forme suivante :" << endl
         << "#\t" << "\t  <Vehicule>(<Ville de départ>, <Ville d'arrivée>)" << endl
         << "#\t" << endl
         << "#\t" << "\tPour créer un trajet composé, séparez chaque trajet simple par \";\" " << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#----------------------------------------------------------------------------------------------" << endl
         << "Saisisser le trajet : ";

    cin >> buff;

    if (strpbrk(buff, ";") == NULL)
    { // Si c'est un trajet simple (pas de point virgule dans le buffer)

        SimpleRoute *route = getSimpleRoute(buff);

        if (route == NULL)
        { // Si une des chaines est vide

            cout << "Erreur lors de la saisie !" << endl;
            typeToContinue();
            return;
        }

        if (catalog->addRoute(route))
        {
            cout << "Le trajet suivant a bien été ajouté : ";
            route->display();
        } else
        {
            cerr << "Erreur lors de l'insertion !" << endl;
        }

    } else
    { // Trajet composé
        char *save_ptr;
        SimpleRoute *simpleRoute = NULL;
        ComposedRoute *composedRoute = NULL;

        char *partial = strtok_r(buff, ";", &save_ptr);
        while (partial != NULL)
        {
            simpleRoute = getSimpleRoute(partial);

            if (simpleRoute == NULL)
            { // Si une des chaines est vide

                cout << "Erreur lors de la saisie !" << endl;
                typeToContinue();
                return;
            }

            if (composedRoute == NULL)
            { // Lors du premier loop, on instancie la route composée
                composedRoute = new ComposedRoute(simpleRoute);
            } else if (!composedRoute->addSimpleRoute(simpleRoute))
            { // Sinon erreur lors de l'ajout de la route
                cerr << "Erreur lors de l'insertion !" << endl;
                typeToContinue();
                return;
            }

            partial = strtok_r(NULL, ";", &save_ptr);
        }

        if (catalog->addRoute(composedRoute))
        {
            cout << "Le trajet suivant a bien été ajouté : ";
            composedRoute->display();
        } else
        {
            cerr << "Erreur lors de l'insertion !" << endl;
        }
    }

    typeToContinue();
}


void displayCatalog(Catalog *catalog)
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Voir le catalogue" << endl
         << "#\t" << endl;

    catalog->display();

    cout << "#----------------------------------------------------------------------------------------------" << endl;

    typeToContinue();
}

void searchRoute(Catalog *catalog, bool advance = false)
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Rechercher un voyage (" << (advance ? "Avancée" : "Simple") << ")" << endl
         << "#\t" << endl
         << "#\t" << "\tRechercher un voyage sous la forme suivante :" << endl
         << "#\t" << "\t  <Ville de départ>, <Ville d'arrivée>" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#----------------------------------------------------------------------------------------------" << endl
         << "Saisisser la recherche : ";

    cin >> buff;

    char *save_ptr;

    // On recupère la ville de départ (avant le ',')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *departure = strtok_r(buff, ",", &save_ptr);


    // On recupère la ville d'arrivée (après le ',')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *arrival = strtok_r(NULL, "", &save_ptr);

    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Résultat de la recherche " << (advance ? "avancée" : "simple") << endl
         << "#\t" << endl;

    if (advance)
    {
        catalog->advanceQuery(departure, arrival);
    } else
    {
        catalog->query(departure, arrival);
    }

    cout << "#----------------------------------------------------------------------------------------------" << endl;

    typeToContinue();
}

int main()
{
    Catalog *catalog = new Catalog();


    for (;;)
    { // Tant que l'utilisateur ne veut pas quitter (à travers un break;)
        clearConsole();
        cout << "#----------------------------------------------------------------------------------------------"
             << endl
             << "#\t Ultra promo voyage" << endl
             << "#\t" << endl
             << "#\t" << "\t1. Ajouter un trajet au catalogue" << endl
             << "#\t" << "\t2. Consulter le catalogue" << endl
             << "#\t" << "\t3. Rechercher un parcours (simple)" << endl
             << "#\t" << "\t4. Rechercher un parcours (avancée)" << endl
             << "#\t" << endl
             << "#\t" << endl
             << "#\t" << "\ta. A propos" << endl
             << "#\t" << "\tq. Quitter l'application" << endl
             << "#----------------------------------------------------------------------------------------------"
             << endl
             << "Saisisser l'option voulue : ";
        cin >> buff;

        if (buff[0] == 'q')
        { // S'il veut quitter, on quitte imediatement
            break;
        }

        switch (buff[0])
        {
            case '1':
                addRoute(catalog);
                break;
            case '2':
                displayCatalog(catalog);
                break;
            case '3':
                searchRoute(catalog);
                break;
            case '4':
                searchRoute(catalog, true);
                break;
            default:
                break;
        }
    }


    delete catalog;
    return 0;
}