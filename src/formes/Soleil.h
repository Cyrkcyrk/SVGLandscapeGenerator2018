#ifndef SOLEIL_H
#define SOLEIL_H

#include "Forme.h"
#include <iostream>
#include <random>
#include <algorithm>

#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"
#include "../Struct.h"

#include "Ellipses.h"
#include "Cercle.h"


class Soleil : public Forme
{
    public:
        Soleil(t_parameter Parametres, std::mt19937& _Seed);
        virtual ~Soleil();

        virtual void dessiner(Svgfile& svgout);
    protected:
        Coords m_Coords;
        std::mt19937& m_Seed;
        Cercle m_Soleil;
    private:
};

#endif // SOLEIL_H
