#include "Generateurs_Paysage.h"


namespace Generateur
{
    void ParametresDefauts(t_parameter& Parametres)
    {
        Parametres.densitee_arbre = 0.5;
        Parametres.hauteur_arbre = 1;
        Parametres.hauteur_colline = 0.8;
        Parametres.jourForce = -1;
        Parametres.heureForce = -1;
        Parametres.saisonForce = -1;

        Parametres.densitee_etoiles = 1;

        Parametres.densitee_montagne = 1;
        Parametres.hauteur_neige = 1;
        Parametres.densitee_nuages = 1;
    }

    void GenerateurPaysage(t_parameter& Parametres)
    {
        Parametres.RG[1] = (std::mt19937 {Parametres.SeedText[1]});
        Parametres.RG[2] = (std::mt19937 {Parametres.SeedText[2]});
        Parametres.RG[3] = (std::mt19937 {Parametres.SeedText[3]});

        Svgfile svgout;
        std::ostringstream oss;
        oss << "<!-- \n\tSeed global de generation: " << Parametres.SeedText[0]
            << "\n\tSeed de generation du ciel: " << Parametres.SeedText[1]
            << "\n\tSeed de generation des montagnes " << Parametres.SeedText[2]
            << "\n\tSeed de generation des plaines: " << Parametres.SeedText[3]
            << "\n-->\n\n";
        svgout.addString(oss.str());

        Gradient::AjouterGradientDefault(svgout);

        Parametres.jour = util::alea(0, 1, Parametres.RG[1]);
        if (Parametres.jourForce != -1)
        {
            Parametres.jour = Parametres.jourForce;
        }

        Parametres.saison = util::alea(0, 3, Parametres.RG[3]);
        if (Parametres.saisonForce != -1)
        {
            Parametres.saison = Parametres.saisonForce;
        }

        Parametres.heure = util::alea(0.0, 12.0, Parametres.RG[1]);
        if (Parametres.heureForce != -1)
        {
            Parametres.heure = Parametres.heureForce;
        }

        generateur_PlanCiel(svgout, Parametres.RG[1], Parametres);

        generateur_PlanMontagne(svgout, Parametres.RG[2], Parametres);

        generateur_PlanColline(svgout, Parametres.RG[3], Parametres);


        if (!Parametres.jour)
        {
            svgout.addBackground(Couleur(0, 0, 0, 0.50));
        }
    }

    void generateur_PlanColline(Svgfile& svgout, std::mt19937& seed, const t_parameter& Parametres)
    {
        Couleur* CouleurColline;
        Couleur* CouleurArbre;

        switch (Parametres.saison)
        {
            default:
            case 0: //Ete
            {
                CouleurColline = new Couleur(100,255,100);
                CouleurColline->muter(10, seed);
                break;
            }
            case 1: //automne
            {
                CouleurColline = new Couleur(204,85,0);
                CouleurColline->muter(10, seed);
                break;
            }
            case 2: //feerique
            {
                CouleurColline = new Couleur(100,100,255);
                CouleurColline->muter(10, seed);
                break;
            }
            case 3: //hivers
            {
                CouleurColline = new Couleur(86, 48, 13);
                CouleurColline->muter(10, seed);
                break;
            }
            case 4: //custom
            {
                int r,v,b;

                if (Parametres.CouleurDominante[0] + 20 > 255)
                {
                    r = 255;
                }
                else
                {
                    r= Parametres.CouleurDominante[0] + 20;
                }

                if (Parametres.CouleurDominante[1] + 20 > 255)
                {
                    v = 255;
                }
                else
                {
                    v= Parametres.CouleurDominante[1] + 20;
                }

                if (Parametres.CouleurDominante[2] + 20 > 255)
                {
                    b = 255;
                }
                else
                {
                    b= Parametres.CouleurDominante[2] + 20;
                }
                CouleurColline = new Couleur(r,v,b);
                CouleurColline->muter(10, seed);
                break;
            }

        }
        Colline maColline(seed, Parametres, *CouleurColline);

        std::vector<Forme*> mesArbres;

        for (int i=0; i<(int)50*Parametres.densitee_arbre; i++)
        {
            Arbre* monArbre;

            double X_arbre = util::alea(-20, Svgfile::WIDTH+100, seed);
            double Y_max;
            double Y_arbre;

            if (maColline.getMont())
            {
                Y_max = maColline.getY() - maColline.getRY() * sin(acos((maColline.getRX() - X_arbre)/maColline.getRX()));
            }
            else
            {
                Y_max = maColline.getY() + maColline.getRY() * sin(acos((maColline.getRX() - X_arbre)/maColline.getRX()));
            }

            Y_arbre = util::alea(Y_max*1.0, Svgfile::HEIGH+100.0, seed);


            double coef_taille = (Y_arbre/Svgfile::HEIGH)*Parametres.hauteur_arbre;

            if (util::alea(0,50, seed) == 1) // 1 arbre sur 50 est plus grand que la moyenne
            {
                coef_taille = 1.5*coef_taille;
            }


            switch (Parametres.saison)
            {
                default:
                case 0: //Ete
                {
                    CouleurArbre = new Couleur(50, 150, 0, 0.75+util::alea(0.0, 0.25, seed));
                    CouleurArbre->muter(30, seed);
                    break;
                }
                case 1: //automne
                {
                    if (util::alea(0, 1, seed))
                    {
                        CouleurArbre = new Couleur(255, 69, 0, 0.75+util::alea(0.0, 0.25, seed));
                    }
                    else
                    {
                        CouleurArbre = new Couleur(255, 140, 0, 0.75+util::alea(0.0, 0.25, seed));
                    }

                    CouleurArbre->muter(30, seed);
                    break;
                }
                case 2: //feerique
                {
                    CouleurArbre = new Couleur(0, 50, 150, 0.75+util::alea(0.0, 0.25, seed));
                    CouleurArbre->muter(30, seed);
                    break;
                }
                case 3: //hivers
                {
                    CouleurArbre = new Couleur("transparent", 0);
                    break;
                }
                case 4: //custom
                {
                    int r,v,b;

                    if (Parametres.CouleurDominante[0] - 20 < 0)
                    {
                        r = 0;
                    }
                    else
                    {
                        r= Parametres.CouleurDominante[0] - 20;
                    }

                    if (Parametres.CouleurDominante[1] - 20 < 0)
                    {
                        v = 0;
                    }
                    else
                    {
                        v= Parametres.CouleurDominante[1] - 20;
                    }

                    if (Parametres.CouleurDominante[2] - 20 < 0)
                    {
                        b = 0;
                    }
                    else
                    {
                        b= Parametres.CouleurDominante[2] - 20;
                    }
                    CouleurArbre = new Couleur(r, v, b, 0.75+util::alea(0.0, 0.25, seed));
                    CouleurArbre->muter(30, seed);
                    break;
                }

            }

            monArbre = new Arbre (Coords (X_arbre, Y_arbre), seed, Parametres, coef_taille, 0, 0, Couleur(0,0,0,-1), *CouleurArbre);
            mesArbres.push_back(monArbre);
        }

        std::sort(mesArbres.begin(), mesArbres.end(), Arbre::sortByHeigh);


        maColline.dessiner(svgout);

        svgout.addString("\n<g id = \"Arbres\">\n");
        for (size_t i=0; i<mesArbres.size(); i++) ///On dessine toutes nos formes
        {
            mesArbres[i]->dessiner(svgout);
        }
        svgout.addString("</g> \n\n");

        delete(CouleurArbre);
        delete(CouleurColline);
        for (size_t i=0; i< mesArbres.size(); i++)
        {
            delete(mesArbres[i]);
        }
    }

    void generateur_PlanMontagne(Svgfile& svgout, std::mt19937& seed, const t_parameter& Parametres)
    {
        std::vector<Forme*> vec;

        int NB_Montagne = util::alea(5, 10, seed)*Parametres.densitee_montagne;
        for (int i=0; i<NB_Montagne; i++)
        {
            Coords tmp_Coord(util::alea(0, Svgfile::WIDTH, seed), util::alea(100, 400, seed));
            vec.push_back(new Montagne(tmp_Coord, seed, Parametres));
        }

        int NB_Nuage = util::alea(0, 15, seed)*Parametres.densitee_nuages;
        for (int i=0; i<NB_Nuage; i++)
        {
            vec.push_back(new Nuage(Coords(util::alea(0, Svgfile::WIDTH, seed), util::alea(0, 400, seed)), seed));
        }

        for (size_t i=0; i<vec.size(); i++)
        {
            int randomCase = util::alea(0, vec.size()-1, seed);

            Forme* tmp = vec[i];
            vec[i] = vec[randomCase];
            vec[randomCase] = tmp;
        }


        svgout.addString("<g id = \"Montagnes_Nuages\">\n");
        for (size_t i=0; i<vec.size(); i++)
        {
            vec[i]->dessiner(svgout);
        }
        svgout.addString("</g> \n\n");

        for (size_t i =0; i< vec.size(); i++)
        {
            delete(vec[i]);
        }

    }


    void generateur_PlanCiel(Svgfile& svgout, std::mt19937& seed, const t_parameter& Parametres)
    {
        if (Parametres.jour)
        {
            Soleil monSoleil(Parametres, seed);

            svgout.addBackground("CielBleu");
            monSoleil.dessiner(svgout);


        }
        else
        {
            Lune maLune(Parametres, seed);

            std::vector<Forme*> etoiles;

            double largeurVoieLactee = util::alea(150, 300, seed);
            double VoieLacteeX = (Svgfile::WIDTH/2)-largeurVoieLactee;

            Rectangle voieLactee (Coords(VoieLacteeX, -Svgfile::HEIGH ), largeurVoieLactee*2, Svgfile::HEIGH*3, Couleur("url(#GD_VoieLactee)", 0.4));

            for (int i=0; i< util::alea(300, 800, seed)*Parametres.densitee_etoiles; i++)
            {
                Couleur col;
                double rayon;
                int random = util::alea(0, 10, seed);
                switch (random)
                {
                    case 1:
                    {
                        col = Couleur("url(#GD_Lune)", 1);
                        rayon = util::alea(2.0, 7.0, seed);
                        break;
                    }
                    case 2:
                    {
                        col = Couleur("url(#GD_RedStar)", 1);
                        rayon = util::alea(2.0, 7.0, seed);
                        break;
                    }
                    case 3:
                    {
                        col = Couleur("url(#GD_BlueStar)", 1);
                        rayon = util::alea(2.0, 7.0, seed);
                        break;
                    }
                    default:
                    {
                        col = Couleur(255, 255, 255);
                        col.muter(10, seed);
                        rayon = util::alea(0.0, 2.0, seed);
                    }
                }

                Cercle* monEtoile = new Cercle(Coords(util::alea(0, Svgfile::WIDTH, seed), util::alea(0, Svgfile::HEIGH, seed)),
                                 rayon,
                                 col);

                etoiles.push_back(monEtoile);
            }

            svgout.addBackground("CielNuit");


            std::ostringstream oss;

            oss << "<g id = \"Voie_Lactee\" transform = \"rotate ("
                << util::alea(-20, 20, seed) << ", "
                << VoieLacteeX << ", "
                << Svgfile::HEIGH/2 << ")\">\n\t";

            svgout.addString(oss.str());
            voieLactee.dessiner(svgout);
            svgout.addString("</g> \n\n");

            svgout.addString("<g id = \"Etoiles\">\n");
            for (size_t i=0; i< etoiles.size(); i++)
            {
                svgout.addString("\t");
                etoiles[i]->dessiner(svgout);
            }
            svgout.addString("</g> \n\n");


            maLune.dessiner(svgout);


            for (size_t i =0; i< etoiles.size(); i++)
            {
                delete(etoiles[i]);
            }

        }
    }

}
