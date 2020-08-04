#ifndef LUNE_H
#define LUNE_H

#include "Forme.h"
#include <iostream>
#include <random>
#include <algorithm>

#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"
#include "../Struct.h"

#include "Ellipses.h"
#include "Cercle.h"


class Lune : public Forme
{
    public:
        Lune(t_parameter Parametres, std::mt19937& _Seed);
        virtual ~Lune();

        virtual void dessiner(Svgfile& svgout);

    protected:
        Coords m_Coords;
        std::mt19937& m_Seed;
        std::vector<Forme*> m_Crateres;
        Cercle m_Lune;
        Cercle m_Halo;
        Cercle m_Ombre;
    private:
};

#endif // LUNE_H
