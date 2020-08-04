#include "Rectangle.h"
#include "../svg/svgfile.h"

#include <sstream>

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Coords _CoordsPrincipal, double _largeur, double _hauteur, Couleur _fill, Couleur _stroke, int _Epaisseur)
    : m_Coord{_CoordsPrincipal}, m_Largeur{_largeur}, m_Hauteur{_hauteur}, m_Fill{_fill}, m_Stroke{_stroke}, m_Epaisseur{_Epaisseur}
{
    m_ClipPath[0] = 0;
}

Rectangle::Rectangle(Coords _CoordsPrincipal, double _largeur, double _hauteur, std::string ID_ClipPath, Couleur _fill, Couleur _stroke, int _Epaisseur)
    : m_Coord{_CoordsPrincipal}, m_Largeur{_largeur}, m_Hauteur{_hauteur}, m_Fill{_fill}, m_Stroke{_stroke}, m_Epaisseur{_Epaisseur}
{
    m_ClipPath = ID_ClipPath;
}

Rectangle::~Rectangle()
{
    //dtor
}

void Rectangle::dessiner(Svgfile& svgout)
{
    std::ostringstream oss;

    oss << "<rect id =\"" << this
        << "\" x=\"" << m_Coord.getX()
        << "\" y=\"" << m_Coord.getY()
        << "\" width= \"" << m_Largeur
        << "\" height =\"" << m_Hauteur
        << "\" fill =\"" << (std::string) m_Fill
        << "\" opacity = \"" << (double) m_Fill
        << "\" stroke =\"" << m_Stroke
        << "\" stroke-width =\"" << m_Epaisseur;

    if (m_ClipPath[0] != 0)
    {
        oss << "\" clip-path= \"url(#" << m_ClipPath << ")\" />\n";
    }
    else
    {
        oss<< "\"/>\n";
    }

    svgout.addString(oss.str());
}
