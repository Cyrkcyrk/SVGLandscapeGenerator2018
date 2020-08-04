#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <random>
#include <vector>

typedef struct parameter
{
    double densitee_arbre;
    double hauteur_arbre;
    double hauteur_colline;

    int jour;
    int jourForce;
    double heure;
    int heureForce;
    int saison;
    int saisonForce;

    int CouleurDominante[3];

    double densitee_montagne;
    double hauteur_neige;
    double densitee_nuages;

    double densitee_etoiles;

    std::vector<int> SeedText;
    std::vector<std::mt19937> RG;
    std::mt19937 timeRG;

}t_parameter;

#endif // STRUCT_H_INCLUDED
