#ifndef POLYGONE_H
#define POLYGONE_H

#include "Forme.h"
#include <iostream>
#include <random>
#include <algorithm>

#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"


class Polygone : public Forme
{
    public:
        Polygone(Coords _coord, std::mt19937& _Seed, double taille, int nbr_cote, Couleur _fill = Couleur(255, 255, 255), int _Epaisseur = 2, Couleur _Stroke = Couleur (0, 0, 0));
        virtual ~Polygone();
        virtual void dessiner(Svgfile& svgout);

    protected:
        std::mt19937& m_Seed;
        Coords m_Centre;
        int m_NombreCote;
        double m_Taille;
        Couleur m_CouleurFill;
        Couleur m_CouleurContour;
        int m_EpaisseurContour;

        std::vector<Coords> m_Coords;

    private:
};

#endif // POLYGONE_H
