#include "Triangle.h"

#include <iostream>
#include <sstream>

Triangle::Triangle()
{
    /*m_Coords.saisir();
    for (int i=0; i<3; i++)
    {
        Coords _tmp_Coord;
        _tmp_Coord.saisir();
        m_CoordsRelative.push_back({_tmp_Coord.getX(), _tmp_Coord.getY()});
    }
    std::cout<< "Fill color?: ";
    m_CouleurFill.saisir();

    std::cout << "Contour color?: ";
    m_CouleurContour.saisir();

    std::cout << "Epaisseur du trait : ";
    std::cin >> m_EpaisseurContour;**/
}

Triangle::Triangle(Coords _CoordsPrincipal, Coords _CoordsR1, Coords _CoordsR2, Coords _CoordsR3, Couleur _fill, Couleur _stroke, int _Epaisseur)
{
    m_Coords = _CoordsPrincipal;
    m_CoordsRelative.push_back({_CoordsR1.getX(), _CoordsR1.getY()});
    m_CoordsRelative.push_back({_CoordsR2.getX(), _CoordsR2.getY()});
    m_CoordsRelative.push_back({_CoordsR3.getX(), _CoordsR3.getY()});
    m_CouleurFill = _fill;
    m_CouleurContour = _stroke;
    m_EpaisseurContour = _Epaisseur;
}


Triangle::~Triangle()
{
}

///<polygon points=" 1381.57,392.741 1375.79,482.549 1384.67,482.549" style="fill:rgb(122,85,59);stroke:rgb(0,0,0);stroke-width:0" />
void Triangle::dessiner(Svgfile& svgout)
{
    /*svgout.addTriangle(m_Coords.getX() + m_CoordsRelative[0].getX(), m_Coords.getY() + m_CoordsRelative[0].getY(),
                       m_Coords.getX() + m_CoordsRelative[1].getX(), m_Coords.getY() + m_CoordsRelative[1].getY(),
                       m_Coords.getX() + m_CoordsRelative[2].getX(), m_Coords.getY() + m_CoordsRelative[2].getY(),
                       m_CouleurFill, m_EpaisseurContour, m_CouleurContour);*/

    std::ostringstream oss;

    oss << "<polygon id = \"" << this
        << "\" points = \""
        << m_Coords.getX() + m_CoordsRelative[0].getX() << "," << m_Coords.getY() + m_CoordsRelative[0].getY() << " "
        << m_Coords.getX() + m_CoordsRelative[1].getX() << "," << m_Coords.getY() + m_CoordsRelative[1].getY() << " "
        << m_Coords.getX() + m_CoordsRelative[2].getX() << "," << m_Coords.getY() + m_CoordsRelative[2].getY()
        << "\" style = \"fill:" << (std::string) m_CouleurFill
        << "; opacity:" << (double) m_CouleurFill
        << "; stroke : " << (std::string) m_CouleurContour
        << "; stroke-width : " << m_EpaisseurContour
        << "\" />\n";

    svgout.addString(oss.str());
}


std::vector<Coords> Triangle::getCoords()
{
    std::vector<Coords> retour;
    for (size_t i=0; i<m_CoordsRelative.size(); i++)
    {
        retour.push_back(Coords(m_CoordsRelative[i].getX() + m_Coords.getX(), m_CoordsRelative[i].getY() + m_Coords.getY()));
    }
    return retour;
}
