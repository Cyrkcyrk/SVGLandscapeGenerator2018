#include "Montagne.h"
#include <sstream>

#include "Cercle.h"

#include <cmath>
const double PI = 3.14159265358979323846;

Montagne::Montagne(Coords _Coord, std::mt19937 _Seed, t_parameter Parametres)
    : m_Coord{_Coord}, m_Seed{_Seed}
{

    double decalage = util::alea(100, 400, m_Seed);
    Coords CoordLeft (-decalage, Svgfile::HEIGH - m_Coord.getY());
    Coords CoordRight (decalage, Svgfile::HEIGH);

    std::ostringstream oss;
    oss << "CP_" << this;



    Couleur MontagneCol (100,100,100);
    MontagneCol.muter(20, m_Seed);

    Couleur Neige (255, 255, 255);
    Neige.muter(40, m_Seed);

    m_Base = Triangle(m_Coord, Coords(0, 0), CoordLeft, CoordRight, MontagneCol);
    m_Contour = Triangle(m_Coord, Coords(0, 0), CoordLeft, CoordRight, Couleur("transparent", 1), Couleur(0, 0, 0), 5);

    m_Mont = Cercle(m_Coord, ((Svgfile::HEIGH-m_Coord.getY())/4)*Parametres.hauteur_neige, oss.str(), Neige);



    const int X_central = Svgfile::WIDTH/2;
    const int Y_central = 250;

    ///int heure = util::alea(0, 12, seed);

    double X = -X_central*cos(-Parametres.heure*PI/12.0);
    double Y = Y_central*sin(-Parametres.heure*PI/12.0);

    Coords CooSoleil = Coords(X_central+X, Y_central+Y);


    if (m_Coord.getX() < CooSoleil.getX())
    {
        m_Ombre = Rectangle(Coords(m_Coord.getX()-decalage,
                                   m_Coord.getY()),
                            CoordRight.getX(),
                            CoordRight.getY(),
                            oss.str(),
                            Couleur(0, 0, 0, 0.25));

    }
    else
    {
        m_Ombre = Rectangle(m_Coord, CoordRight.getX(), CoordRight.getY(), oss.str(), Couleur(0, 0, 0, 0.25));

    }



    /**m_Coord = Coords(200, 400);

    std::cout << "X = " <<m_Coord.getX() << " & Y = " << m_Coord.getY() << std::endl;

    Coords CoordLeft (-100, Svgfile::HEIGH-m_Coord.getY());
    Coords CoordRight (100, Svgfile::HEIGH-m_Coord.getY());

    m_Base = Triangle(m_Coord, Coords(0, 0), CoordLeft, CoordRight, Couleur(255, 0, 0));

    m_Mont = Cercle(m_Coord, (m_Coord.getY()/Svgfile::HEIGH)*200, Couleur(255,0,255));*/
}

Montagne::~Montagne()
{
    //dtor
}

void Montagne::dessiner(Svgfile& svgout)
{
    std::ostringstream oss;
    oss << "<clipPath id=\"CP_" << this << "\">\n\t\t";

    svgout.addString(oss.str());
    m_Base.dessiner(svgout);
    svgout.addString("\t</clipPath>\n\t");
    m_Base.dessiner(svgout);
    svgout.addString("\t");
    m_Mont.dessiner(svgout);
    svgout.addString("\t");
    m_Contour.dessiner(svgout);
    svgout.addString("\t");
    m_Ombre.dessiner(svgout);
    svgout.addString("\n\n\t");

}
