using namespace std;

#include <iostream>

#define BUFFER_SIZE 1000
#define MAX_CONSOLE_LINES 20

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
    cout << "Appuyer sur ENTREE pour continuer...";
    cin.ignore(256, '\n');
}

char *trim(char *str)
{
    if (str == NULL)
    { return NULL; }

    size_t size = strlen(str);
    unsigned int first = 0;
    unsigned int last = (unsigned int) size;

    bool firstFound = false;
    bool lastFound = false;

    for (unsigned int i = 0; i < size && (!firstFound || !lastFound); ++i)
    {
        if (!firstFound && str[i] != ' ')
        {
            firstFound = true;
            first = i;
        }

        if (!lastFound && str[size - i - 1] != ' ')
        {
            lastFound = true;
            last = (unsigned int) size - i;
        }
    }

    size_t newSize = last - first;

    // On refuse les chaines vides
    if (!firstFound || !lastFound)
    { return NULL; }

    char *newStr = new char[newSize + 1];
    newStr[newSize] = '\0';

    for (unsigned int j = 0; j < newSize; ++j)
    {
        newStr[j] = str[j + first];
    }

    return newStr;
}


SimpleRoute *getSimpleRoute(char *string)
{
    if (string == NULL)
    { return NULL; }

    char *savePtr; // Pour retenir la chaine utilisée

    // On recupère le moyen de transport (avant le '(')
    char *transport = trim(strtok_r(string, "(", &savePtr));

    // On recupère la ville de départ (avant le ',')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *departure = trim(strtok_r(NULL, ",", &savePtr));


    // On recupère la ville d'arrivée (avant le ')')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *arrival = trim(strtok_r(NULL, ")", &savePtr));


    // S'il manque un élément
    if (transport == NULL
        || departure == NULL
        || arrival == NULL)
    {
        // On supprime les autres chaines si elles existent
        if (transport != NULL)
        { delete[] transport; }
        if (departure != NULL)
        { delete[] departure; }
        if (arrival != NULL)
        { delete[] arrival; }

        return NULL;
    }

    SimpleRoute *simpleRoute = new SimpleRoute(departure, arrival, transport);

    delete[] transport;
    delete[] departure;
    delete[] arrival;

    return simpleRoute;
}


void addRouteFromString(Catalog *catalog, const char *str)
{
    char *data = new char[strlen(str) + 1];
    strcpy(data, str);

    if (strpbrk(data, ";") == NULL)
    { // Si c'est un trajet simple (pas de point virgule dans le buffer)

        SimpleRoute *route = getSimpleRoute(data);

        if (route == NULL)
        { // Si une des chaines est vide

            cout << "Erreur lors de la saisie !" << endl;
            typeToContinue();
            delete[] data;
            return;
        }

        if (catalog->AddRoute(route))
        {
            cout << "Le trajet suivant a bien été ajouté : ";
            route->Display();
            cout << endl;
        } else
        {
            cerr << "Ce trajet existe déjà !" << endl;
            delete route;
        };
    } else
    { // Trajet composé
        char *savePtr;
        SimpleRoute *simpleRoute = NULL;
        ComposedRoute *composedRoute = NULL;

        char *partial = strtok_r(data, ";", &savePtr);
        while (partial != NULL)
        {
            simpleRoute = getSimpleRoute(partial);

            if (simpleRoute == NULL)
            { // Si une des chaines est vide

                cout << "Erreur lors de la saisie !" << endl;
                if (composedRoute != NULL)
                { delete composedRoute; }
                delete[] data;
                typeToContinue();
                return;
            }

            if (composedRoute == NULL)
            { // Lors du premier loop, on instancie la route composée
                composedRoute = new ComposedRoute(simpleRoute);
            } else if (!composedRoute->AddSimpleRoute(simpleRoute))
            { // Sinon erreur lors de l'ajout de la route
                cerr << "Erreur lors de l'insertion ! Vérifiez que les villes soient correctement rentrées" << endl;
                typeToContinue();

                delete[] data;
                delete composedRoute;
                delete simpleRoute;
                return;
            }

            partial = strtok_r(NULL, ";", &savePtr);
        }


        if (catalog->AddRoute(composedRoute))
        {
            cout << "Le trajet suivant a bien été ajouté : ";
            composedRoute->Display();
            cout << endl;
        } else
        {
            cerr << "Ce trajet existe déjà !" << endl;
            delete composedRoute;
        };
    }

    delete[] data;
}

void addRoute(Catalog *catalog)
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Ajouter un trajet" << endl
         << "#\t" << endl
         << "#\t" << "\tAjoutez un trajet sous la forme suivante :" << endl
         << "#\t" << "\t  <Vehicule>(<Ville de départ>,<Ville d'arrivée>)" << endl
         << "#\t" << endl
         << "#\t" << "\tPour créer un trajet composé, séparez chaque trajet simple par \";\" " << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#----------------------------------------------------------------------------------------------" << endl
         << "Saisisser le trajet : ";

    cin.getline(buff, BUFFER_SIZE);

    addRouteFromString(catalog, buff);
    typeToContinue();
}


void displayCatalog(Catalog *catalog)
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Voir le catalogue" << endl
         << "#\t" << endl;

    catalog->Display();

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

    cin.getline(buff, BUFFER_SIZE);

    char *savePtr;

    // On recupère la ville de départ (avant le ',')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *departure = trim(strtok_r(buff, ",", &savePtr));


    // On recupère la ville d'arrivée (après le ',')
    //  Envoyer la valeur NULL permet d'utiliser la derniere chaine
    char *arrival = trim(strtok_r(NULL, "", &savePtr));

    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Résultat de la recherche " << (advance ? "avancée" : "simple") << endl
         << "#\t" << endl;

    if (advance)
    {
        catalog->AdvanceQuery(departure, arrival);
    } else
    {
        catalog->Query(departure, arrival);
    }

    cout << "#----------------------------------------------------------------------------------------------" << endl;

    delete[] departure;
    delete[] arrival;

    typeToContinue();
}

void about()
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------"
         << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\tApplication : Ultra promo voyage" << endl
         << "#\tAuteurs : " << endl
         << "#\t" << "\tMarc-Antoine FERNANDES" << endl
         << "#\t" << "\tGuillaume MARCELIN" << endl
         << "#\t" << "\tLucas ONO" << endl
         << "#\t" << endl
         << "#\tCréé pour le TP C++ n.2 - INSA Lyon - 2016" << endl
         << "#\t" << endl
         << "#----------------------------------------------------------------------------------------------"
         << endl;

    typeToContinue();
}

int main()
{
    bool stop = false;
    Catalog *catalog = new Catalog();


    for (; !stop;)
    { // Tant que l'utilisateur ne veut pas quitter
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
             << "#\t" << endl
             << "#\t" << "\ta. A propos" << endl
             << "#\t" << "\tq. Quitter l'application" << endl
             << "#----------------------------------------------------------------------------------------------"
             << endl
             << "Saisisser l'option voulue : ";
        cin.getline(buff, BUFFER_SIZE);


        if (strlen(buff) == 1)
        { // Si seulement un caractère !

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
                case 'a':
                    about();
                    break;
                case 'q':
                    stop = true;
                    break;
                default:
                    break;
            }
        }
    }

    delete catalog;
    return 0;
}