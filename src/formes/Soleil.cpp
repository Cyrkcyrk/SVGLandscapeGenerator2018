#include "Soleil.h"

#include "../util/util.h"

#include "../svg/svgfile.h"
#include <cmath>
const double PI = 3.14159265358979323846;


Soleil::Soleil(t_parameter Parametres, std::mt19937& _Seed)
    : m_Seed{_Seed}
{
    int heure = Parametres.heure;
    double rayon;


    const int X_central = Svgfile::WIDTH/2;
    const int Y_central = 250;

    ///int heure = util::alea(0, 12, seed);

    double X = -X_central*cos(-heure*PI/12.0);
    double Y = Y_central*sin(-heure*PI/12.0);



    double coef;
    if (heure <7)
    {
        coef = (heure+1)/12.0;
    }
    else
    {
        coef = (13.0-heure)/12.0;
    }


    rayon = 75 +40/coef;// + util::alea(0.0, 10.0, m_Seed);

    m_Coords = Coords(X_central+X, Y_central+Y);

    m_Soleil = Cercle(m_Coords, rayon, Couleur("url(#GD_Soleil)", 1));

}

Soleil::~Soleil()
{
    //dtor
}

void Soleil::dessiner(Svgfile& svgout)
{
    svgout.addString("<g id = \"Soleil\">\n\t");
    m_Soleil.dessiner(svgout);
    svgout.addString("</g>\n");

}
