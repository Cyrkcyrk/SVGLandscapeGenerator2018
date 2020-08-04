#include "Menu.h"

void ParametresDefauts(t_parameter& Parametres);
void GenerateurPaysage(t_parameter& Parametres);

namespace Menu
{
    void MainMenu(t_parameter& Parametres, Console* pConsole)
    {
        std::vector<std::string> TxtmainMenu;
        int mainMenuLongueur = 21;
        TxtmainMenu.push_back("Graines de generation");
        TxtmainMenu.push_back("Reglages densitee    ");
        TxtmainMenu.push_back("Autres Reglages      ");
        TxtmainMenu.push_back("Reinitialiser        ");
        TxtmainMenu.push_back("Quitter              ");

        std::vector<std::string> TxtMenuSeed;
        TxtMenuSeed.push_back("Graine generale ");
        TxtMenuSeed.push_back("Graine Ciel     ");
        TxtMenuSeed.push_back("Graine Montagnes");
        TxtMenuSeed.push_back("Graine Plaine   ");
        TxtMenuSeed.push_back("Retour          ");

        std::vector<std::string> TxtMenuHauteur;
        TxtMenuHauteur.push_back("Hauteur de la neige  ");
        TxtMenuHauteur.push_back("Taille des arbres    ");
        TxtMenuHauteur.push_back("Hauteur de la colline");
        TxtMenuHauteur.push_back("Jour/Nuit            ");
        TxtMenuHauteur.push_back("Heure                ");
        TxtMenuHauteur.push_back("Terrain              ");
        TxtMenuHauteur.push_back("Retour               ");

        std::vector<std::string> TxtMenuDensite;
        TxtMenuDensite.push_back("Densite etoiles  ");
        TxtMenuDensite.push_back("Densite Montagnes");
        TxtMenuDensite.push_back("Densite Nuages   ");
        TxtMenuDensite.push_back("Densite Arbres   ");
        TxtMenuDensite.push_back("Retour           ");



        bool quitter = true;
        int retour_menu = 0;
        int old_retour_menu;

        const int posX = 3;
        const int posY = 3;

        while (quitter)
        {
            retour_menu = menu(TxtmainMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || ((size_t) old_retour_menu == TxtmainMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+mainMenuLongueur+9), 30, 15);
                quitter = false;
            }
            else if (retour_menu == -2)
            {
                retour_menu = old_retour_menu;
            }
            else if (retour_menu == 0)
            {
                afficher_menu(TxtmainMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                switch(old_retour_menu)
                {
                    default:
                    case 1: ///Menu SEED
                    {
                        MenuSeed(Parametres, posX+ old_retour_menu, posY+mainMenuLongueur+9, TxtMenuSeed, pConsole);
                        break;
                    }
                    case 2: /// Menu DENSITEE
                    {
                        MenuDensitee(Parametres, posX+ old_retour_menu, posY+mainMenuLongueur+9, TxtMenuDensite, pConsole);
                        break;
                    }
                    case 3: /// Menu Autres
                    {
                        MenuparametreG(Parametres, posX+ old_retour_menu, posY+mainMenuLongueur+9, TxtMenuHauteur, pConsole);
                        break;
                    }
                    case 4:
                    {
                        Generateur::ParametresDefauts(Parametres);
                        Generateur::GenerateurPaysage(Parametres);
                        break;
                    }

                }

                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+mainMenuLongueur+9), 30, 15);
                old_retour_menu = retour_menu;
                switch(retour_menu)
                {
                    default:
                    case 1:
                    {
                        afficher_menu(TxtMenuSeed, Coords(posX+ retour_menu, posY+mainMenuLongueur+9), pConsole, -1, false);
                        break;
                    }
                    case 2:
                    {
                        afficher_menu(TxtMenuDensite, Coords(posX+ retour_menu, posY+mainMenuLongueur+9), pConsole, -1, false);
                        break;
                    }
                    case 3:
                    {
                        afficher_menu(TxtMenuHauteur, Coords(posX+ retour_menu, posY+mainMenuLongueur+9), pConsole, -1, false);
                        break;
                    }
                    case 4:
                    {

                    }

                }
            }
        }

    }

    void MenuSubSeed(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole, int SeedARegen)
    {
        const int decalage = 21;
        bool quitter = true;
        int retour_menu = 1;
        int old_retour_menu;


        while (quitter)
        {

            retour_menu = menu(monMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || retour_menu == -2 || ( (size_t) old_retour_menu == monMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                afficher_menu(monMenu, Coords(posX, posY), pConsole, -1, false);
                quitter = false;
            }

            else if (retour_menu == 0)
            {
                switch(old_retour_menu)
                {
                    default:
                    case 1: ///Random
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);

                        if (SeedARegen == 0)
                        {
                            Parametres.SeedText[0] = util::alea(0, 2147483647, Parametres.timeRG);
                            Parametres.RG[0] = (std::mt19937 {Parametres.SeedText[0]});

                            Parametres.SeedText[1] = util::alea(0, 2147483647, Parametres.RG[0]);
                            Parametres.SeedText[2] = util::alea(0, 2147483647, Parametres.RG[0]);
                            Parametres.SeedText[3] = util::alea(0, 2147483647, Parametres.RG[0]);
                        }
                        else
                        {
                            Parametres.SeedText[SeedARegen] = util::alea(0, 2147483647, Parametres.RG[0]);
                        }

                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }

                    case 2: ///Entree utilisateur
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Une graine (nombre):", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 2147483647)
                            {
                                fin = true;
                            }
                        }
                        if (SeedARegen == 0)
                        {
                            Parametres.SeedText[0] = retour;
                            Parametres.RG[0] = (std::mt19937 {Parametres.SeedText[0]});

                            Parametres.SeedText[1] = util::alea(0, 2147483647, Parametres.RG[0]);
                            Parametres.SeedText[2] = util::alea(0, 2147483647, Parametres.RG[0]);
                            Parametres.SeedText[3] = util::alea(0, 2147483647, Parametres.RG[0]);
                        }
                        else
                        {
                            Parametres.SeedText[SeedARegen] = retour;
                        }
                        Generateur::GenerateurPaysage(Parametres);
                        menu_entre_utilisateur("Une graine (nombre):", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);

                        break;
                    }



                }
                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                old_retour_menu = retour_menu;
                switch(retour_menu)
                {
                    default:
                    case 1: ///Random
                    {

                        break;
                    }
                    case 2: ///Seed fixee
                    {
                        menu_entre_utilisateur("Une graine (nombre):", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }


                }
            }
        }
        Generateur::GenerateurPaysage(Parametres);
    }

    void MenuJour(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole)
    {
        const int decalage = 14;
        bool quitter = true;
        int retour_menu = 1;
        int old_retour_menu;

        while (quitter)
        {

            retour_menu = menu(monMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || retour_menu == -2 || ((size_t) old_retour_menu == monMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                afficher_menu(monMenu, Coords(posX, posY), pConsole, -1, false);
                quitter = false;
            }
            else if (retour_menu == 0)
            {
                switch(old_retour_menu)
                {
                    case 1: ///Forcer JOUR
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 0);
                        Parametres.jourForce = 1;
                        Generateur::GenerateurPaysage(Parametres);


                        break;
                    }
                    case 2: ///Forcer NUIT
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 1);
                        Parametres.jourForce = 0;
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    default:
                    case 3: ///Laisser RANDOM
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 2);
                        Parametres.jourForce = -1;
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                }

                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                old_retour_menu = retour_menu;
            }
        }
    }

    void MenuSaison(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole)
    {
        const int decalage = 14;
        bool quitter = true;
        int retour_menu = 1;
        int old_retour_menu;

        while (quitter)
        {

            retour_menu = menu(monMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || retour_menu == -2 || ((size_t) old_retour_menu == monMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                afficher_menu(monMenu, Coords(posX, posY), pConsole, -1, false);
                quitter = false;
            }
            else if (retour_menu == 0)
            {
                switch(old_retour_menu)
                {
                    case 1: ///Forcer ETE
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 0);
                        Parametres.saisonForce = 0;
                        Generateur::GenerateurPaysage(Parametres);


                        break;
                    }
                    case 2: ///Forcer Automne
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 1);
                        Parametres.saisonForce = 1;
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 3: ///Forcer Bleu
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 1);
                        Parametres.saisonForce = 2;
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 4: ///Forcer Hivers
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 2);
                        Parametres.saisonForce = 3;
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 5: ///Entrer couleur
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 2);
                        Parametres.saisonForce = 4;

                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        {
                            double retour = 0;
                            bool fin = true;
                            while (fin)
                            {
                                fin = false;
                                retour = menu_entre_utilisateur("Entrez le rouge (0 - 255)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                                if (retour < 0 || retour > 255)
                                {
                                    fin = true;
                                }
                            }
                            Parametres.CouleurDominante[0] = retour;
                            fin = true;

                            while (fin)
                            {
                                fin = false;
                                retour = menu_entre_utilisateur("Entrez le vert (0 - 255) ", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                                if (retour < 0 || retour > 255)
                                {
                                    fin = true;
                                }
                            }
                            Parametres.CouleurDominante[1] = retour;
                            fin = true;

                            while (fin)
                            {
                                fin = false;
                                retour = menu_entre_utilisateur("Entrez le bleu (0 - 255) ", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                                if (retour < 0 || retour > 255)
                                {
                                    fin = true;
                                }
                            }
                            Parametres.CouleurDominante[2] = retour;
                            effacer(Coords(posX, posY+decalage+9), 35, 15);
                            menu_entre_utilisateur("Entrez une couleur RVB", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);

                        }

                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    default:
                    case 6: ///Laisser Random
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        //MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, monMenu, pConsole, 2);
                        Parametres.jourForce = -1;
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                }

                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                old_retour_menu = retour_menu;

                switch(retour_menu)
                {
                    case 5: ///Etoiles
                    {
                        menu_entre_utilisateur("Entrez une couleur RVB", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }



    void MenuSeed(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole)
    {
        const int decalage = 16;
        bool quitter = true;
        int retour_menu = 1;
        int old_retour_menu;

        std::vector<std::string> TxtChanger;
        TxtChanger.push_back("Changer aleatoirement");
        TxtChanger.push_back("Rentrer manuellement ");
        TxtChanger.push_back("Retour               ");

        while (quitter)
        {

            retour_menu = menu(monMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || retour_menu == -2 || ((size_t) old_retour_menu == monMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                afficher_menu(monMenu, Coords(posX, posY), pConsole, -1, false);
                quitter = false;
            }
            else if (retour_menu == 0)
            {
                switch(old_retour_menu)
                {
                    default:
                    case 1: ///Graine Generale
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, TxtChanger, pConsole, 0);


                        break;
                    }
                    case 2: ///Graine Ciel
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, TxtChanger, pConsole, 1);
                        break;
                    }
                    case 3: ///Graine Montagnes
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, TxtChanger, pConsole, 2);
                        break;
                    }
                    case 4: ///Graine Plaine
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        MenuSubSeed(Parametres, posX+ old_retour_menu, posY+decalage+9, TxtChanger, pConsole, 3);
                        break;
                    }

                }

                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                old_retour_menu = retour_menu;
                switch(retour_menu)
                {
                    case 1: ///Generale
                    {
                        afficher_menu(TxtChanger, Coords(posX+ retour_menu, posY+decalage+9), pConsole, -1, false);
                        break;
                    }
                    case 2: ///Ciel
                    {
                        afficher_menu(TxtChanger, Coords(posX+ retour_menu, posY+decalage+9), pConsole, -1, false);
                        break;
                    }
                    case 3: ///Montagnes
                    {
                        afficher_menu(TxtChanger, Coords(posX+ retour_menu, posY+decalage+9), pConsole, -1, false);
                        break;
                    }
                    case 4: ///Plaine
                    {
                        afficher_menu(TxtChanger, Coords(posX+ retour_menu, posY+decalage+9), pConsole, -1, false);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }

    void MenuDensitee(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole)
    {
        const int decalage = 17;
        bool quitter = true;
        int retour_menu = 1;
        int old_retour_menu;


        while (quitter)
        {

            retour_menu = menu(monMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || retour_menu == -2 || ((size_t) old_retour_menu == monMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                afficher_menu(monMenu, Coords(posX, posY), pConsole, -1, false);
                quitter = false;
            }
            else if (retour_menu == 0)
            {
                switch(old_retour_menu)
                {
                    default:
                    case 1: ///Densitee Etoile
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.densitee_etoiles = retour;
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }

                    case 2: ///Densitee Montagnes
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.densitee_montagne = retour;
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }


                    case 3: ///Densitee Nuages
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.densitee_nuages = retour;
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }


                    case 4: ///Densitee Arbres
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.densitee_arbre = retour;
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                }
                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+decalage+9), 35, 15);
                old_retour_menu = retour_menu;
                switch(retour_menu)
                {
                    case 1: ///Etoiles
                    {
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 2: ///Montagnes
                    {
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 3: ///Nuages
                    {
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 4: ///Arbres
                    {
                        menu_entre_utilisateur("Entrez un pourcentage (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }

    void MenuparametreG(t_parameter& Parametres, int posX, int posY, std::vector<std::string> monMenu, Console* pConsole)
    {
        const int decalage = 21;
        bool quitter = true;
        int retour_menu = 1;
        int old_retour_menu;

        std::vector<std::string> TxtJour;
        TxtJour.push_back("Forcer le jour");
        TxtJour.push_back("Forcer la nuit");
        TxtJour.push_back("Laisser Random");
        TxtJour.push_back("Retour        ");

        std::vector<std::string> TxtSaison;
        TxtSaison.push_back("Saison Ete    ");
        TxtSaison.push_back("Saison Automne");
        TxtSaison.push_back("Monde Feerique");
        TxtSaison.push_back("Devaste       ");
        TxtSaison.push_back("Entrer couleur");
        TxtSaison.push_back("Laisser Random");
        TxtSaison.push_back("Retour        ");

        while (quitter)
        {
            retour_menu = menu(monMenu, Coords(posX, posY), retour_menu, pConsole);
            if(retour_menu == -1 || retour_menu == -2 || ((size_t) old_retour_menu == monMenu.size() && retour_menu == 0))
            {
                effacer(Coords(posX, posY+decalage+9), 50, 15);
                afficher_menu(monMenu, Coords(posX, posY), pConsole, -1, false);
                quitter = false;
            }
            else if (retour_menu == 0)
            {
                switch(old_retour_menu)
                {
                    default:
                    case 1: ///Hauteur de la neige
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez une hauteur (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.hauteur_neige = retour;
                        menu_entre_utilisateur("Entrez une hauteur (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 2: ///Taille des arbres
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez une taille (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.hauteur_arbre = retour;
                        menu_entre_utilisateur("Entrez une taille (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 3: ///Hauteur de la colline
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez une hauteur (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 100)
                            {
                                fin = true;
                            }
                        }
                        Parametres.hauteur_colline = retour;
                        menu_entre_utilisateur("Entrez une hauteur (0 - 1)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 4: ///Jour ou Nuit
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        MenuJour(Parametres, posX+ old_retour_menu, posY+decalage+9, TxtJour, pConsole);
                        break;
                    }
                    case 5: ///Heure
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        double retour = 0;
                        bool fin;
                        fin = true;
                        while (fin)
                        {
                            fin = false;
                            retour = menu_entre_utilisateur("Entrez une heure (0 - 11) (-1 pour random)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, true);
                            if (retour < 0 || retour > 11 || retour == -1)
                            {
                                fin = true;
                            }
                        }
                        Parametres.heureForce = (int) retour;
                        menu_entre_utilisateur("Entrez une heure (0 - 11) (-1 pour random)", Coords(posX+ old_retour_menu, posY+decalage+9), pConsole, false);
                        Generateur::GenerateurPaysage(Parametres);

                        break;
                    }
                    case 6: ///Saison
                    {
                        afficher_menu(monMenu, Coords(posX, posY), pConsole, old_retour_menu-1, true);
                        MenuSaison(Parametres, posX+ old_retour_menu, posY+decalage+9, TxtSaison, pConsole);
                        break;
                    }

                }

                retour_menu = old_retour_menu;
            }
            else
            {
                effacer(Coords(posX, posY+decalage+9), 50, 15);
                old_retour_menu = retour_menu;
                switch(retour_menu)
                {
                    case 1: ///Hauteur neige
                    {
                        menu_entre_utilisateur("Entrez une hauteur (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 2: ///Taille arbres
                    {
                        menu_entre_utilisateur("Entrez une taille (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 3: ///Hauteur colline
                    {
                        menu_entre_utilisateur("Entrez une hauteur (0 - 1)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 4: ///joiur ou nuit
                    {
                        afficher_menu(TxtJour, Coords(posX+ retour_menu, posY+decalage+9), pConsole, -1, false);
                        break;
                    }
                    case 5: ///heure
                    {
                        menu_entre_utilisateur("Entrez une heure (0 - 11) (-1 pour random)", Coords(posX+ retour_menu, posY+decalage+9), pConsole, false);
                        break;
                    }
                    case 6: ///joiur ou nuit
                    {
                        afficher_menu(TxtSaison, Coords(posX+ retour_menu, posY+decalage+9), pConsole, -1, false);
                        break;
                    }
                    default:
                    {
                        break;
                    }

                }
            }
        }
    }




    void effacer(Coords _Coord, int largeur, int hauteur)
    {
        Console* pConsole = NULL;
        pConsole = Console::getInstance();
        for(int i=0; i< hauteur; i++)
        {
            pConsole->gotoLigCol(_Coord.getX()+i, _Coord.getY());
            std::cout << std::string(largeur, ' ');
        }
        Console::deleteInstance();
    }

    double menu_entre_utilisateur(std::string Texte, const Coords _Coord, Console* pConsole, bool demander)
    {
        pConsole->gotoLigCol(_Coord.getX(), _Coord.getY());
        std::cout << (char)218 << std::string(Texte.size()+4, (char)196) << (char)191;
        pConsole->gotoLigCol(_Coord.getX()+1, _Coord.getY());
        std::cout << (char)179 << std::string(Texte.size()+4, ' ') << (char)179;
        pConsole->gotoLigCol(_Coord.getX()+2, _Coord.getY());
        std::cout << (char)179 << std::string(Texte.size()+4, ' ') << (char)179;
        pConsole->gotoLigCol(_Coord.getX()+3, _Coord.getY());
        std::cout << (char)192 << std::string(Texte.size()+4, (char)196) << (char)217;


        pConsole->gotoLigCol(_Coord.getX()+1, _Coord.getY()+2);
        std::cout << Texte;

        pConsole->gotoLigCol(_Coord.getX()+2, _Coord.getY()+2);
        double retour;
        if (demander)
        {
            pConsole->setColor(COLOR_RED);
            std::cin.clear();
            std::cin >> retour;

            pConsole->setColor(COLOR_DEFAULT);

            return retour;
        }
        else
        {
            return 0.0;
        }

    }

    void afficher_menu(const std::vector<std::string>& Menu, const Coords _Coord, Console* pConsole, int selection, bool selected)
    {
        int plus_grand = 0;

        for (size_t i=0; i<Menu.size(); i++)
        {
            pConsole->gotoLigCol(i+1+_Coord.getX(), _Coord.getY() + 1);

            if ((size_t) plus_grand < Menu[i].size())
            {
                plus_grand = Menu[i].size();
            }
            if(i == (size_t) selection)
            {
                if (selected)
                {
                    pConsole->setColor(COLOR_GREEN);
                    std::cout << " > " << i+1 << ": " << Menu[i];
                    pConsole->setColor(COLOR_DEFAULT);
                }
                else
                {
                    std::cout << " ";
                    pConsole->setColor(COLOR_GREEN);
                    std::cout << ">";
                    pConsole->setColor(COLOR_DEFAULT);
                    std::cout << " " << i+1 << ": " << Menu[i];
                }
            }
            else
            {
                std::cout << "   " << i+1 << ": " << Menu[i];
            }
        }

        plus_grand +=9;

        pConsole->gotoLigCol(_Coord.getX()+Menu.size()+1, _Coord.getY());
        std::cout << (char)192 << std::string(plus_grand-2, (char)196) << (char)217;

        pConsole->gotoLigCol(_Coord.getX(), _Coord.getY());
        std::cout << (char)218 << std::string(plus_grand-2, (char)196) << (char)191;


        for (size_t i=0; i<Menu.size(); i++)
        {
            pConsole->gotoLigCol(i+1+_Coord.getX(), _Coord.getY());
            std::cout << (char) 179;
            pConsole->gotoLigCol(i+1+_Coord.getX(), _Coord.getY()-1+plus_grand);
            std::cout << (char)179;
        }
    }

    int menu(const std::vector<std::string>& Menu, const Coords _Coord, int old_selection, Console* pConsole)
    {
        bool quit = true;
        unsigned int selection = old_selection;

        afficher_menu(Menu, _Coord, pConsole, old_selection-1, false);
        pConsole->gotoLigCol(0, 0);

        while(quit)
        {
            while(!pConsole->isKeyboardPressed())
            {
            }

            // Récupère le code ASCII de la touche
            int key = pConsole->getInputKey();
            if (key == 224)
            {
                switch (pConsole->getInputKey())
                {
                    case 72: //Fleche haut
                    {
                        if (selection > 1)
                        {
                            selection--;
                            quit = false;
                        }
                        break;
                    }
                    case 80: //Fleche bas
                    {
                        if((size_t) selection < Menu.size())
                        {
                            selection++;
                            quit = false;
                        }
                        break;
                    }
                    case 75: //Fleche gauche
                    {
                        selection = -2;
                        quit = false;
                        break;
                    }
                    case 77: //Fleche droite
                    {
                        if (selection > 0)
                        {
                            selection = 0;

                        }
                        else
                        {
                            selection = 1;
                        }
                        quit = false;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                quit = false;
            }
            else if ( key == 13) //ENTER
            {
                if(selection == Menu.size())
                {
                    selection = -1;
                }
                else
                {
                    selection = 0;
                }

                quit = false;
            }
            else if ( key == 27) //ESC
            {
                selection = -1;
                quit = false;
            }
        }

        //pConsole->gotoLigCol(25, 25); std::cout << util::alea(10, 99) << " - " << selection << "    ";
        return selection;

        // Libère la mémoire du pointeur !

    }
}
