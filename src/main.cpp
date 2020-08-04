#include "main.h"
#include <sstream>

/**
IMPLEMENTATION DES FORMES DE BASE:

Rectangle Rctg(Coords(100, 100), 30, 20, Couleur(255, 0, 255, 0.75));
Triangle Trgl (Coords (200, 200), Coords (-25, -25), Coords (25, 25), Coords(10, -10), Couleur(100, 0, 100), Couleur(0, 100, 0), 2 );

Ellipses Elps (Coords(200, 600), 10, 25, Couleur(100, 100, 0), Couleur(0, 100, 100), 2);
Polygone Plgn (Coords(100, 100), rg2, 50.0, 10, Couleur(255, 0, 255), 0, Couleur(0, 0, 0));
**/

int main()
{
    Console* pConsole = NULL;
    pConsole = Console::getInstance();
    pConsole->setColor(COLOR_DEFAULT);


    t_parameter Parametres;

    int temps = std::time(nullptr);
    Parametres.timeRG = std::mt19937 {temps};

    Parametres.SeedText.push_back(util::alea(0, 2147483647, Parametres.timeRG));
    //Parametres.SeedText[0] = 195441503;
    Parametres.RG.push_back(std::mt19937 {Parametres.SeedText[0]});

    Parametres.SeedText.push_back(util::alea(0, 2147483647, Parametres.RG[0]));
    Parametres.SeedText.push_back(util::alea(0, 2147483647, Parametres.RG[0]));
    Parametres.SeedText.push_back(util::alea(0, 2147483647, Parametres.RG[0]));

    Parametres.RG.push_back(std::mt19937 {Parametres.SeedText[1]});
    Parametres.RG.push_back(std::mt19937 {Parametres.SeedText[2]});
    Parametres.RG.push_back(std::mt19937 {Parametres.SeedText[3]});


    Generateur::ParametresDefauts(Parametres);

    Generateur::GenerateurPaysage(Parametres);

    Menu::MainMenu(Parametres, pConsole);

    Console::deleteInstance();
    return 0;
}
