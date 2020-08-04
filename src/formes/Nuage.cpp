#include "Nuage.h"

#include "../util/util.h"

#include "Cercle.h"
#include <sstream>

Nuage::Nuage(Coords _coord, std::mt19937& _Seed)
    : Polygone::Polygone(_coord,
                         _Seed,
                         util::alea(20, 100, _Seed),
                         util::alea(3, 7, _Seed),
                         Couleur(200, 210, 255, util::alea(0.5, 1.0, _Seed)), 0)
{
    for (size_t i = 0; i<this->m_Coords.size(); i++)
    {
        m_Coords[i].muter(m_Taille/10, m_Seed);
    }
}

Nuage::~Nuage()
{
    //dtor
}


void Nuage::dessiner(Svgfile& svgout)
{
    std::ostringstream oss;
    oss << "<path id =\"" << this << "\" d=\"M" << m_Coords[0].getX() << " " << m_Coords[0].getY() << "\n";

    for (size_t i = 1; i< m_Coords.size()-1; i++)
    {
        oss << "          a " << util::alea(0.5, 2.0, m_Seed) << " 1 0 0 1 " << m_Coords[i].getX() << " " << m_Coords[i].getY() << "\n";
    }
    oss << "          A " << util::alea(0.5, 2.0, m_Seed) << " 1 0 0 1 " << m_Coords[0].getX() << " " << m_Coords[0].getY() << "z\n"
		<< "          \" fill=\"" << (std::string) m_CouleurFill <<"\" opacity = \""<< (double) m_CouleurFill <<"\"/>" << std::endl;

    svgout.addString(oss.str());
}
