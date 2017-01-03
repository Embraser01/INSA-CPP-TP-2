#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//------------------------------------------- Interfaces utilisées, Types, Constantes

#include "Catalog.h"
#include "SimpleRoute.h"
#include "ComposedRoute.h"

using namespace std;


const int MAX_CONSOLE_LINES = 20;

enum FILTER
{
    NONE, TYPE, PASS_BY, INDEX
};


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


string trim(const string &str)
// Paramètre <str> : Chaîne de caractère à "trimmer"
// Mode d'emploi :
//      Permet de "trim" (enelver les espaces avant et après une phrase) une chaîne de caractères
//      génère une nouvelle chaîne ! (à delete plus tard)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


// From : http://stackoverflow.com/a/236803/5285167

void split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
}


vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


SimpleRoute *getSimpleRoute(string str)
// Paramètre <str> : Chaîne de caractère à parser pour générer une SimpleRoute
// Mode d'emploi :
//      Renvoie une nouvelle instance de SimpleRoute depuis une chaîne de caractère de la forme :
//              Moyen de transport ( Ville de départ, Ville d'arrivée)
//      Renvoie NULL si la chaîne est malformée
{
    if (str.empty())
    {
        return NULL;
    }

    size_t start = str.find("(");
    size_t end = start;

    // On recupère le moyen de transport (avant le '(')
    string transport = trim(str.substr(0, end));

    // On recupère la ville de départ (avant le ',')
    start++;
    end = str.find(",", start);
    string departure = trim(str.substr(start, end - start));


    // On recupère la ville d'arrivée (avant le ')')
    start = end + 1;
    end = str.find(")", start);
    string arrival = trim(str.substr(start, end - start));


    // S'il manque un élément
    if (transport.empty()
        || departure.empty()
        || arrival.empty())
    {
        return NULL;
    }

    return new SimpleRoute(departure, arrival, transport);
}


Route *getRoute(const string str)
{

    vector<string> routes = split(str, ';');
    if (routes.size() == 0)
    {
        return NULL;
    }

    if (routes.size() == 1)
    { // Si c'est une route simple
        return getSimpleRoute(str);
    }


    // Sinon
    ComposedRoute *composedRoute = NULL;
    SimpleRoute *tmp;

    for (vector<string>::iterator it = routes.begin(); it < routes.end(); it++)
    {
        tmp = getSimpleRoute(*it);
        if (tmp == NULL)
        { // Si mauvaise syntaxe
            delete composedRoute;
            return NULL;
        }

        if (composedRoute == NULL)
        { // Si c'est la première route
            composedRoute = new ComposedRoute(tmp);
        } else if (!composedRoute->AddSimpleRoute(tmp))
        { // Si erreur pour l'ajout
            delete tmp;
            delete composedRoute;
            return NULL;
        }
    }

    return composedRoute;
}



//--------------------------------------- Méthodes

void addRouteFromString(Catalog *catalog, const string str)
// Paramètre <catalog> : Catalog où ajouter la route générée
// Paramètre <str> : Chaîne de caractère à parser pour générer une Route
// Mode d'emploi :
//      Ajoute à <catalog> la route générer depuis <str> qui est de la forme :
//              Moyen de transport ( Ville de départ, Ville d'arrivée)[; MdT(VdeDépart, VdArrivee)]
//
//      Dans le cas d'une route composée, chaque trajet simple est séparée par ';'
{

    Route *newRoute = getRoute(str);

    if (newRoute == NULL)
    { // Si pas valide
        cout << "Erreur lors de l'insertion !" << endl;
        return;
    }

    // On ajoute au catalogue la route et on notifie l'utilisateur

    catalog->AddRoute(newRoute);
    cout << "Le trajet suivant a bien été ajouté : ";
    newRoute->Display();
    cout << endl;
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

    string route;

    getline(cin, route);
    addRouteFromString(catalog, route);
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

    string research;

    getline(cin, research);


    // On recupère la ville de départ (avant le ',')
    string departure = trim(research.substr(0, research.find(",")));


    // On recupère la ville d'arrivée (après le ',')
    string arrival = trim(research.substr(research.find(","), string::npos));

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

    typeToContinue();
}


FILTER getFilter(string &param1, string &param2)
{
    // TODO Faire l'interface qui permet de selectionner les filtres (pour le chargement et l'enregistrement) et enregistrer les valeurs des paramètres dans param1 & param2 si necessaire
    return NONE;
}


void loadFile(Catalog *catalog)
// Paramètre <catalog> Catalogue ou ajouter les trajets charges
// Mode d'emploi:
// Demande a l'utilisateur le nom du fichier contenant le Catalogue
{
    clearConsole();
    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Charger un catalogue " << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#----------------------------------------------------------------------------------------------" << endl
         << "Saisisser le nom du fichier a charger : ";

    string fileName;
    getline(cin, fileName);

    ifstream f;
    f.open(fileName);

    // TODO check if exists and readable

    ListRoute *listRoute = new ListRoute(DEFAULT_LIST_SIZE, false);
    Route *tmp;
    string strRoute;


    // Filter
    string param1;
    string param2;
    FILTER filter = getFilter(param1, param2);
    bool isValid = false;

    while (!f.bad() && !f.eof())
    {
        getline(cin, strRoute);
        tmp = getRoute(strRoute);

        if (tmp != NULL)
        {
            switch (filter)
            {
                case NONE:
                    isValid = true;
                    break;
                case TYPE:
                    isValid = (tmp->IsComposed() && param1 == "Composed")
                              || (!tmp->IsComposed() && param1 == "Simple");
                    break;
                case PASS_BY:
                    isValid = tmp->PassBy(param1, param2);
                    break;
                case INDEX:
                    isValid = true; // On gère l'index après
                    break;
                default:
                    break;

            }
            if (isValid)
            {
                listRoute->AddRoute(tmp);
            } else
            {
                delete tmp;
            }
        } else
        {
            cout << "Erreur lors du chargement d'une route, on l'ignore" << endl;
        };
    }

    if (filter == INDEX)
    { // Pour l'index on travaille sur la liste et non pas sur la route

        int n = stoi(param1);
        int m = stoi(param2);

        ListRoute *filtered = listRoute->FilterSelect(n, m);

        // TODO Check if NULL or NOT

        for (unsigned int i = 0; i < n; i++)
        {
            delete listRoute->GetElement(i);
            // ON l'enlève pas du tableau listRoute car on va la supprimer juste après
        }

        for (unsigned int i = (unsigned int) (m + 1); i < listRoute->GetSize(); i++)
        {
            delete listRoute->GetElement(i);
            // ON l'enlève pas du tableau listRoute car on va la supprimer juste après
        }

        delete listRoute;
        listRoute = filtered;
    }

    // On ajoute les routes restantes au catalogue
    for (unsigned int i = 0; i < listRoute->GetSize(); i++)
    {
        catalog->AddRoute(listRoute->GetElement(i));
    }

    delete listRoute;
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
    string choice = "";


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
             << "#\t" << "\t5. Charger les données depuis un fichier" << endl
             << "#\t" << "\t6. Sauvegarder les données dans un fichier" << endl
             << "#\t" << endl
             << "#\t" << "\ta. A propos" << endl
             << "#\t" << "\tq. Quitter l'application" << endl
             << "#----------------------------------------------------------------------------------------------"
             << endl
             << "Saisisser l'option voulue : ";
        getline(cin, choice);


        if (choice.size() == 1)
        { // Si seulement 1 caractère !

            switch (choice[0])
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
                case '5':
                    loadFile(catalog);
                    break;
                case '6':
                    // TODO Sauvegarder (dans catalog ou dans le main ?)
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