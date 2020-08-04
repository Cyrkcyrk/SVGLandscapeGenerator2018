#include "Ellipses.h"
#include <iostream>
#include <sstream>

Ellipses::Ellipses()
{
    /*m_Coords.saisir();

    std::cout << "Rayon X: ";
    std::cin >> m_Rx;

    std::cout << "Rayon Y: ";
    std::cin >> m_Ry;

    std::cout<< "Fill color?: ";
    m_CouleurFill.saisir();

    std::cout << "Contour color?: ";
    m_CouleurContour.saisir();

    std::cout << "Epaisseur du trait: ";
    std::cin >> m_EpaisseurContour;*/
}

Ellipses::Ellipses(Coords _coords, double _rayonX, double _rayonY, Couleur _Fill, Couleur _Stroke, int _Epaisseur)
{
    m_Coords = _coords;
    m_Rx =_rayonX;
    m_Ry =_rayonY;
    m_CouleurFill = _Fill;
    m_CouleurContour = _Stroke;
    m_EpaisseurContour = _Epaisseur;
    m_ClipPath[0] = 0;
}

Ellipses::Ellipses(Coords _coords, double _rayonX, double _rayonY, std::string ID_ClipPath, Couleur _Fill, Couleur _Stroke, int _Epaisseur)
{
    m_Coords = _coords;
    m_Rx =_rayonX;
    m_Ry =_rayonY;
    m_CouleurFill = _Fill;
    m_CouleurContour = _Stroke;
    m_EpaisseurContour = _Epaisseur;
    m_ClipPath = ID_ClipPath;
}


Ellipses::~Ellipses()
{
    //dtor
}

///<ellipse cx="75" cy="75" rx="20" ry="5" stroke="red" fill="transparent" stroke-width="5"/>
void Ellipses::dessiner(Svgfile& svgout)
{
    //svgout.addEllipses(m_Coords.getX(), m_Coords.getY(), m_Rx, m_Ry, m_CouleurFill, m_EpaisseurContour, m_CouleurContour);

    std::ostringstream oss;

    oss << "<ellipse id=\"" << this
        << "\" cx=\"" << m_Coords.getX()
        << "\" cy=\"" << m_Coords.getY()
        << "\" rx=\"" << m_Rx
        << "\" ry=\"" << m_Ry
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
