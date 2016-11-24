#include <iostream>
#include <cstring>

using namespace std;

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "Catalog.h"
#include "SimpleRoute.h"
#include "ComposedRoute.h"

const int BUFFER_SIZE = 1000;
const int MAX_CONSOLE_LINES = 20;

char buff[BUFFER_SIZE] = {'\0'}; // Variable globale


//--------------------------------------- Méthodes utilitaires (helpers)

void clearConsole()
// Mode d'emploi :
//      Permet d'effacer le contenu du terminal
{
    for (int i = 0; i < MAX_CONSOLE_LINES; ++i)
    {
        cout << endl;
    }
}


void typeToContinue()
// Mode d'emploi :
//      Lance un "Appuyer sur ENTREE pour continuer..."
{
    cout << "Appuyer sur ENTREE pour continuer...";
    cin.ignore(256, '\n');
}


char *trim(char *str)
// Paramètre <str> : Chaîne de caractère à "trimmer"
// Mode d'emploi :
//      Permet de "trim" (enelver les espaces avant et après une phrase) une chaîne de caractères
//      génère une nouvelle chaîne ! (à delete plus tard)
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


SimpleRoute *getSimpleRoute(char *str)
// Paramètre <str> : Chaîne de caractère à parser pour générer une SimpleRoute
// Mode d'emploi :
//      Renvoie une nouvelle instance de SimpleRoute depuis une chaîne de caractère de la forme :
//              Moyen de transport ( Ville de départ, Ville d'arrivée)
//      Renvoie NULL si la chaîne est malformée
{
    if (str == NULL)
    {
        return NULL;
    }

    char *savePtr; // Pour retenir la chaine utilisée

    // On recupère le moyen de transport (avant le '(')
    char *transport = trim(strtok_r(str, "(", &savePtr));

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


//--------------------------------------- Méthodes

void addRouteFromString(Catalog *catalog, const char *str)
// Paramètre <catalog> : Catalog où ajouter la route générée
// Paramètre <str> : Chaîne de caractère à parser pour générer une Route
// Mode d'emploi :
//      Ajoute à <catalog> la route générer depuis <str> qui est de la forme :
//              Moyen de transport ( Ville de départ, Ville d'arrivée)[; MdT(VdeDépart, VdArrivee)]
//
//      Dans le cas d'une route composée, chaque trajet simple est séparée par ';'
{

    // On copie <str> dans une chaîne locale

    char *data = new char[strlen(str) + 1];
    strcpy(data, str);

    Route *newRoute = NULL; // Route ajoutée au catalogue

    if (strpbrk(data, ";") == NULL)
    { // Si c'est un trajet simple (pas de point virgule dans la chaîne)

        newRoute = getSimpleRoute(data);

        if (newRoute == NULL)
        { // Si la chaîne est malformée

            cout << "Erreur lors de la saisie !" << endl;
            typeToContinue();
            delete[] data;
            return;
        }
    } else
    { // Sinon, Trajet composé

        char *savePtr;

        SimpleRoute *simpleRoute = NULL; // Trajet temporaire
        ComposedRoute *composedRoute = NULL; // Futur trajet du catalogue

        char *partial = strtok_r(data, ";", &savePtr); // Première partie de la chaîne
        while (partial != NULL)
        {
            simpleRoute = getSimpleRoute(partial);

            if (simpleRoute == NULL)
            { // Si une des chaines est vide

                cout << "Erreur lors de la saisie !" << endl;
                delete composedRoute;
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

                delete composedRoute;
                delete simpleRoute;
                delete[] data;
                typeToContinue();
                return;
            }

            // On récupère la suite des trajets simples
            partial = strtok_r(NULL, ";", &savePtr);
        }
        newRoute = composedRoute;
    }

    // On ajoute au catalogue la route et on notifie l'utilisateur

    catalog->AddRoute(newRoute);
    cout << "Le trajet suivant a bien été ajouté : ";
    newRoute->Display();
    cout << endl;
    delete[] data;
}


void addRoute(Catalog *catalog)
// Paramètre <catalog> : Catalog où ajouter la route
// Mode d'emploi :
//      Demande à l'utilisateur de rentrer une route
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
// Paramètre <catalog> : Catalog à afficher
// Mode d'emploi :
//      Affiche le contenu de <catalog>
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
// Paramètre <catalog> : Catalog où rechercher
// Paramètre <advance> : Flag pour savoir si la recherche est avancée
// Mode d'emploi :
//      Demande à l'utilisateur les villes de départ et d'arrivée pour la recherche
//      Appelle la fonction de recherche de <catalog>
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
// Mode d'emploi :
//     Affiche des informations statiques sur le programme
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------"
         << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\tApplication : Catalogue de trajet" << endl
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
    bool stop = false; // Variable d'arrêt
    Catalog *catalog = new Catalog(); // Catalogue utilisé dans l'application


    for (; !stop;)
    { // Tant que l'utilisateur ne veut pas quitter

        clearConsole();
        cout << "#----------------------------------------------------------------------------------------------"
             << endl
             << "#\t Catalogue de trajet" << endl
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
        { // Si seulement 1 caractère !

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