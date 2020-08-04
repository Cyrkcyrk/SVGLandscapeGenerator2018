#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Forme.h"
#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"

#include "../svg/svgfile.h"

#include <string>


class Rectangle : public Forme
{
    public:
        Rectangle();
        Rectangle(Coords _CoordsPrincipal, double _largeur, double _hauteur, Couleur _fill, Couleur _stroke = Couleur(0,0,0), int _Epaisseur = 0);
        Rectangle(Coords _CoordsPrincipal, double _largeur, double _hauteur,  std::string ID_ClipPath, Couleur _fill, Couleur _stroke = Couleur(0,0,0), int _Epaisseur = 0);
        virtual ~Rectangle();

        virtual void dessiner(Svgfile& svgout);

    protected:
        Coords m_Coord;
        double m_Largeur;
        double m_Hauteur;

        Couleur m_Fill;
        Couleur m_Stroke;
        int m_Epaisseur;

        std::string m_ClipPath;

    private:
};

#endif // RECTANGLE_H
