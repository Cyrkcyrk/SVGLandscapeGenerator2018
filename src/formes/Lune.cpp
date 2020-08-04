#include "Lune.h"

#include "../util/util.h"

#include <cmath>
const double PI = 3.14159265358979323846;

Lune::Lune(t_parameter Parametres, std::mt19937& _Seed)
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


    rayon = 75 +2.5/coef + util::alea(0.0, 10.0, m_Seed);

    m_Coords = Coords(X_central+X, Y_central+Y);

    const double assombris = -50;
    m_Lune = Cercle(m_Coords, rayon, Couleur(216+assombris, 223+assombris, 227+assombris));
    m_Halo = Cercle(m_Coords, rayon*1.5, Couleur("url(#GD_Lune)", 1));


    // ---- Ajout des cratères ----

    for (int i=0; i< util::alea(1, 7, m_Seed); i++)
    {
        Ellipses* monCratere;

        double tmp_RX = util::alea(rayon/5, rayon/2, m_Seed);
        double tmp_RY = util::alea(rayon/5, rayon/2, m_Seed);

        double tmp_X = this->m_Coords.getX() + util::alea(-(rayon), rayon, m_Seed);
        double tmp_Y = this->m_Coords.getY() + util::alea(-(rayon), rayon, m_Seed);

        const int sombre = 100;
        Couleur fond (216-sombre, 223-sombre, 227-sombre, util::alea(0.5, 1.0, m_Seed));
        fond.muter(10, m_Seed);


        //monCratere = new Ellipses(Coords(tmp_X, tmp_Y), tmp_RX, tmp_RY, fond, Contour, util::alea(tmp_RX/10, tmp_RX/5, m_Seed));
        monCratere = new Ellipses(Coords(tmp_X, tmp_Y),  tmp_RX, tmp_RY, "CP_Lune", fond);

        m_Crateres.push_back(monCratere);
    }

    // ---- Ajout de l'ombre

    double teta = util::alea(0.0, 2.0, m_Seed)*PI;
    double Xombre = 2*rayon*cos(teta) + m_Coords.getX();
    double Yombre = 2*rayon*sin(teta) + m_Coords.getY();

    m_Ombre = Cercle(Coords(Xombre, Yombre), 2*rayon + rayon*util::alea(0.5, 0.8, m_Seed), "CP_Lune",  Couleur(255, 255, 255, 0.5));


}

Lune::~Lune()
{
    //dtor
}

void Lune::dessiner(Svgfile& svgout)
{
    svgout.addString("<g id = \"Lune\">\n\t");

    svgout.addString("<clipPath id=\"CP_Lune\">");
    m_Lune.dessiner(svgout);
    svgout.addString("\t</clipPath>\n\n\t");

    m_Halo.dessiner(svgout);
    m_Lune.dessiner(svgout);

    for (size_t i = 0; i< m_Crateres.size(); i++)
    {
        svgout.addString("\t");
        m_Crateres[i]->dessiner(svgout);
    }

    m_Ombre.dessiner(svgout);
    svgout.addString("</g>\n");
}
