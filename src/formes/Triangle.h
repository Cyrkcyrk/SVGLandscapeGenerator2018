#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Forme.h"
#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"

#include <vector>

class Triangle : public Forme
{
    public:
        Triangle();
        Triangle(Coords _CoordsPrincipal, Coords _CoordsR1, Coords _CoordsR2, Coords _CoordsR3, Couleur _fill, Couleur _stroke =  Couleur(0,0,0), int _Epaisseur = 0);
        virtual ~Triangle();
        virtual void dessiner(Svgfile& svgout);

        std::vector<Coords> getCoords();

    protected:
        Coords m_Coords;
        std::vector<Coords> m_CoordsRelative;
        Couleur m_CouleurFill;
        Couleur m_CouleurContour;
        int m_EpaisseurContour;

    private:
};

#endif // TRIANGLE_H
