#include "Cercle.h"

#include <iostream>
#include <sstream>


Cercle::Cercle()
{
    /*m_Coords.saisir();

    std::cout << "Rayon: ";
    std::cin >> m_Rayon;

    std::cout<< "Fill color?: ";
    m_CouleurFill.saisir();

    std::cout << "Contour color?: ";
    m_CouleurContour.saisir();

    std::cout << "Epaisseur du trait: ";
    std::cin >> m_EpaisseurContour;*/
}

Cercle::Cercle(Coords _coords, double _rayon, Couleur _Fill, Couleur _Stroke, int _Epaisseur)
{
    m_Coords = _coords;
    m_Rayon =_rayon;
    m_CouleurFill = _Fill;
    m_CouleurContour = _Stroke;
    m_EpaisseurContour = _Epaisseur;
    m_ClipPath[0] = 0;
}
Cercle::Cercle(Coords _coords, double _rayon, std::string ID_ClipPath, Couleur _Fill, Couleur _Stroke, int _Epaisseur)
{
    m_Coords = _coords;
    m_Rayon =_rayon;
    m_CouleurFill = _Fill;
    m_CouleurContour = _Stroke;
    m_EpaisseurContour = _Epaisseur;
    m_ClipPath = ID_ClipPath;
}

Cercle::~Cercle()
{
    //dtor
}

///<circle cx="25" cy="75" r="20" stroke="red" fill="transparent" stroke-width="5"/>
void Cercle::dessiner(Svgfile& svgout)
{
    //svgout.addCircle(m_Coords.getX(), m_Coords.getY(), m_Rayon, m_EpaisseurContour, m_CouleurContour, m_CouleurFill);
    std::ostringstream oss;

    oss << "<circle id=\"" << this
        << "\" cx=\"" << m_Coords.getX()
        << "\" cy=\"" << m_Coords.getY()
        << "\" r=\"" << m_Rayon
        << "\" fill=\"" << (std::string) m_CouleurFill
        << "\" opacity=\"" << (double) m_CouleurFill
        << "\" stroke=\"" << (std::string) m_CouleurContour
        << "\" stroke-width=\"" << m_EpaisseurContour;

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
