#ifndef ELLIPSES_H
#define ELLIPSES_H

#include "Forme.h"
#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"

class Ellipses : public Forme
{
    public:
        Ellipses();
        Ellipses(Coords _coords, double _rayonX, double _rayonY, Couleur _Fill, Couleur _Stroke =  Couleur(0,0,0), int _Epaisseur = 0);
        Ellipses(Coords _coords, double _rayonX, double _rayonY, std::string ID_ClipPath, Couleur _Fill, Couleur _Stroke =  Couleur(0,0,0), int _Epaisseur = 0);
        virtual ~Ellipses();
        virtual void dessiner(Svgfile& svgout);

    protected:
        Coords m_Coords;
        double m_Rx;
        double m_Ry;
        Couleur m_CouleurFill;
        Couleur m_CouleurContour;
        int m_EpaisseurContour;
        std::string m_ClipPath;

    private:
};

#endif // ELLIPSES_H
