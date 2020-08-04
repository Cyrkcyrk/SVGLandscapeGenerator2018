#ifndef MONTAGNE_H
#define MONTAGNE_H

#include "Forme.h"
#include "../Struct.h"
#include <iostream>
#include <random>
#include <algorithm>

#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"

#include "Cercle.h"
#include "Triangle.h"
#include "Rectangle.h"


class Montagne : public Forme
{
    public:
        Montagne(Coords _Coord, std::mt19937 _Seed, t_parameter Parametres);
        virtual ~Montagne();

        virtual void dessiner(Svgfile& svgout);

    protected:
        Coords m_Coord;
        std::mt19937 m_Seed;
        Triangle m_Base;
        Triangle m_Contour;
        Cercle m_Mont;
        Rectangle m_Ombre;
    private:
};

#endif // MONTAGNE_H
