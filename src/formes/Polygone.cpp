#include "Polygone.h"

#include <cmath>
const double PI = 3.14159265358979323846;

#include <sstream>

//Algorithme inspiré d'ici: https://lycee-valin.fr/maths/exercices_en_ligne/algorithmes/polygone.html

Polygone::Polygone(Coords _coord,
                   std::mt19937& _Seed,
                   double taille,
                   int nbr_cote,
                   Couleur _Fill,
                   int _Epaisseur,
                   Couleur _Stroke)
    :   m_Seed{_Seed},
        m_Centre{_coord},
        m_NombreCote{nbr_cote},
        m_Taille{taille},
        m_CouleurFill{_Fill},
        m_CouleurContour{_Stroke},
        m_EpaisseurContour{_Epaisseur}
{
    m_Coords.push_back(Coords(m_Centre.getX()+ m_Taille, m_Centre.getY()));

    for (int i=0; i< m_NombreCote; i++)
    {
        m_Coords.push_back(Coords ((m_Taille*cos(2*PI*i/m_NombreCote))+0, (m_Taille*sin(2*PI*i/m_NombreCote))+0));
    }
}

Polygone::~Polygone()
{
    //dtor
}

void Polygone::dessiner(Svgfile& svgout)
{
    std::ostringstream oss;
    oss << "<path d=\"M" << m_Coords[0].getX() << " " << m_Coords[0].getY() << "\n";

    for (size_t i = 1; i< m_Coords.size()-1; i++)
    {
        oss << "          l" << m_Coords[i].getX() << " " << m_Coords[i].getY() << "\n";
    }
    oss << "          l" << m_Coords[m_Coords.size()-1].getX() << " " << m_Coords[m_Coords.size()-1].getY() << "z\n"
		<< "          \" stroke=\"black\" fill=\"rgb(200, 210, 255)\"/>" << std::endl;

    svgout.addString(oss.str());
}
