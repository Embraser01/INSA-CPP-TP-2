#include <iostream>
#include <fstream>
#include <cstring>

#define BUFFER_SIZE 1000

//----- DEFINE pour l'insertion automatique
#define MAX_ROUTE_PER_COMPOSED_ROUTE 4
#define MAX_NAME_LENGTH 40

//----- INCLUDE uniquement utilisés pour l'insertion automatique
#include <stdlib.h>

using namespace std;

char buff[BUFFER_SIZE] = {'\0'};


int main()
{
    const char CITIES[][MAX_NAME_LENGTH] = {"Paris", "Marseille", "Lyon", "Toulouse", "Nice", "Nantes", "Strasbourg",
                                            "Montpellier", "Bordeaux", "Lille", "Rennes", "Reims", "Le Havre",
                                            "Saint-Étienne", "Toulon", "Grenoble", "Dijon", "Nîmes", "Angers",
                                            "Villeurbanne", "Le Mans", "Aix-en-Provence", "Clermont-Ferrand", "Brest",
                                            "Limoges", "Tours", "Amiens", "Perpignan", "Metz", "Besançon",
                                            "Boulogne-Billancourt", "Orléans", "Mulhouse", "Rouen", "Saint-Denis",
                                            "Caen", "Argenteuil", "Saint-Paul", "Montreuil"
    };
    const char TRANSPORTS[][MAX_NAME_LENGTH] = {"Voiture", "Train", "Car", "Avion"};
    const int NB_CITIES = (sizeof(CITIES) / sizeof(*CITIES));
    const int NB_TRANSPORTS = (sizeof(TRANSPORTS) / sizeof(*TRANSPORTS));

    ofstream ofstream1("dump.test");

    if (!ofstream1)
    {
        cerr << "Impossible d'ouvrir dump.test pour l'écriture";
        return EXIT_FAILURE;
    }

    cout << "#----------------------------------------------------------------------------------------------" << endl
         << "#\t Inserer des données aléatoires" << endl
         << "#\t" << endl
         << "#\t" << "\tRentrer le nombre de trajet à créer dans 'dump.test' :" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#\t" << endl
         << "#----------------------------------------------------------------------------------------------" << endl
         << "Saisisser le nombre de trajet : ";

    cin.getline(buff, BUFFER_SIZE);

    /* initialize random seed: */
    srand((unsigned int) time(NULL));

    int nbRoute = atoi(buff);
    int nbRoutePerComposedRoute;
    int departure_city;
    int arrival_city;
    int transport;
    char str[BUFFER_SIZE] = {'\0'};

    for (int i = 0; i < nbRoute; i++)
    {
        nbRoutePerComposedRoute = rand() % MAX_ROUTE_PER_COMPOSED_ROUTE + 1;

        arrival_city = -1;

        for (int j = 0; j < nbRoutePerComposedRoute; ++j)
        {

            transport = rand() % NB_TRANSPORTS;
            // Si trajet composé
            departure_city = (arrival_city != -1) ? arrival_city : rand() % NB_CITIES;
            arrival_city = rand() % NB_CITIES;

            // Si le départ est l'arrivée, on ajoute 1 à l'arrivée
            if (departure_city == arrival_city)
            { arrival_city++; }

            strcat(str, TRANSPORTS[transport]);
            strcat(str, "(");
            strcat(str, CITIES[departure_city]);
            strcat(str, ", ");
            strcat(str, CITIES[arrival_city]);
            strcat(str, ");");
        }

        ofstream1 << str << endl;

        strcpy(str, "");
    }

    ofstream1.close();

    return EXIT_SUCCESS;
}