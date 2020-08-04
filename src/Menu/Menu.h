#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../console/console.h"
#include "../geometrie/coords.h"
#include "../Struct.h"

#include "../Generateurs/Generateurs_Paysage.h"

#include <iostream>
#include <vector>
#include <string>



namespace Menu
{
    void MainMenu(t_parameter& Parametres, Console* p_Console);
    void MenuSubSeed(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole, int SeedARegen);
    void MenuJour(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole);
    void MenuSaison(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole);
    void MenuSeed(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole);
    void MenuDensitee(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole);
    void MenuparametreG(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole);
    void effacer(Coords _Coord, int largeur, int hauteur);
    double menu_entre_utilisateur(std::string Texte, const Coords _Coord, Console* pConsole, bool demander);
    int menu(const std::vector<std::string>& Menu, const Coords _Coord, int old_selection, Console* pConsole);
    void afficher_menu(const std::vector<std::string>& Menu, const Coords _Coord, Console* pConsole, int selection, bool selected);
}

#endif // MENU_H_INCLUDED
