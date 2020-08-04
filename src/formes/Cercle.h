#ifndef CERCLE_H
#define CERCLE_H

#include "Forme.h"
#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"

class Cercle : public Forme
{
    public:
        Cercle();
        Cercle(Coords _coords, double _rayon, Couleur _Fill, Couleur _Stroke = Couleur(0,0,0), int _Epaisseur = 0);
        Cercle(Coords _coords, double _rayon,std::string ID_ClipPath, Couleur _Fill, Couleur _Stroke = Couleur(0,0,0), int _Epaisseur = 0);
        virtual ~Cercle();
        virtual void dessiner(Svgfile& svgout);

    protected:
        Coords m_Coords;
        double m_Rayon;
        Couleur m_CouleurFill;
        Couleur m_CouleurContour;
        int m_EpaisseurContour;
        std::string m_ClipPath;

    private:
};

#endif // CERCLE_H
