#include "Arbre.h"

#include "../util/util.h"
#include <sstream>
#include <cmath>
const double PI = 3.14159265358979323846;

#include "Cercle.h"
Arbre::Arbre(Coords _coord, std::mt19937& _Seed, t_parameter Parametres, double taille, double _rotation, int degre_recursif, Couleur _Tronc, Couleur _Feuillage)
    : m_Coords{ _coord }, m_Seed{ _Seed}, m_rotation{_rotation}, m_degreRecursif{degre_recursif}
{
    m_hivers = false;
    if ((double) _Tronc == -1)
    {
        _Tronc = Couleur(126, 88, 53);
        _Tronc.muter(10, m_Seed);
    }
    if ((double) _Feuillage == -1)
    {
        _Feuillage = Couleur(50, 150, 0, 0.75+util::alea(0.0, 0.25, m_Seed));
        _Feuillage.muter(30, m_Seed);
    }
    else if ((double) _Feuillage == 0)
    {
        m_hivers = true;
    }



    double Yt_bot = (200 + util::alea(-10, 10, m_Seed))*taille;
    Coords tmp_Coords (_coord.getX(), _coord.getY()-Yt_bot);

    // ---- CREATION DU FEUILLAGE ----
    double Xf = (tmp_Coords.getX() );// + util::alea(-10, 10,  m_Seed));  //X central de l'elipse
    double Yf = (tmp_Coords.getY() );// + util::alea(-10, 10,  m_Seed)) ;  // Y central de l'ellipse
    double RXf = (100 + util::alea(-20, 20,  m_Seed) )* taille;                //Rayon X de l'ellipse
    double RYf = (60 + util::alea(-20, 20,  m_Seed) )* taille;                 //Rayon Y de l'ellipse



    m_Ombre = Ellipses(m_Coords, RXf, RYf, "CP_Colline", Couleur("url(#Ombre)", 0.75));

    if ((m_degreRecursif != 0 ) || (util::alea(0, 1, m_Seed)))
    {
        m_Feuillage = new Ellipses(Coords(Xf, Yf), RXf, RYf , _Feuillage); //CF: destructeur de l'Arbre.

        for (int i = util::alea(0, 2, m_Seed); i<2; i++)
        {
            if (m_degreRecursif < 3)
            {
                double Ybranche = util::alea(m_Coords.getY() - Yt_bot + (Yt_bot/3), m_Coords.getY() - (Yt_bot/3), m_Seed);

                m_Branches.push_back(Arbre (Coords(m_Coords.getX(), Ybranche), m_Seed, Parametres, taille/util::alea(2, 3, m_Seed), util::alea(-90, 90, m_Seed), m_degreRecursif+1, _Tronc, _Feuillage));
            }
        }
    }
    else
    {
        Couleur VertSapin (9, 82, 40);
        VertSapin.muter(15, m_Seed);
        m_Feuillage = new Triangle(Coords(Xf, Yf + RXf/2), Coords(0, -RXf), Coords(-RYf, RXf), Coords(+RYf, RXf), VertSapin); //CF: destructeur de l'Arbre.
    }



    // ---- CREATION DU RELIEF OMBRAGE ----

    std::ostringstream oss;
    oss << "CP_" << this;

    const int X_central = Svgfile::WIDTH/2;
    const int Y_central = 250;

    ///int heure = util::alea(0, 12, seed);

    double X = -X_central*cos(-Parametres.heure*PI/12.0);
    double Y = Y_central*sin(-Parametres.heure*PI/12.0);

    Coords CooSoleil = Coords(X_central+X, Y_central+Y);


    if (Xf < CooSoleil.getX())
    {
        m_OmbreRelief = Rectangle(Coords(Xf - (RXf + (m_Coords.getX() - Xf)), Yf-RYf),
                                  RXf + (m_Coords.getX() - Xf),
                                  RYf + (m_Coords.getY() - Yf),
                                  oss.str(),
                                  Couleur(0,0,0, 0.15));
    }
    else
    {
        m_OmbreRelief = Rectangle(Coords(Xf, Yf-RYf),
                                  RXf + (m_Coords.getX() - Xf),
                                  RYf + (m_Coords.getY() - Yf),
                                  oss.str(),
                                  Couleur(0,0,0, 0.15));
    }


    // ---- CREATION DU TRONC ----
    m_Tronc = Triangle (Coords(tmp_Coords.getX(), tmp_Coords.getY()),
                        Coords (0, 0),
                        //Coords((-20*taille + util::alea(0, 10,  m_Seed))*taille, Yt_bot),
                        //Coords((20*taille + util::alea(0, 10,  m_Seed))*taille, Yt_bot),
                        Coords(-20*taille, Yt_bot),
                        Coords(20*taille, Yt_bot),
                        _Tronc);


}

Arbre::~Arbre()
{
    /*
    Triangle* tr = dynamic_cast<Triangle*>(m_Feuillage);
    Ellipses* El = dynamic_cast<Ellipses*>(m_Feuillage);

    if (tr)
    {
        delete(tr);
    }
    else if (El)
    {
        delete(El);
    }*/


    //delete(m_Feuillage);

    ///Pour une raison inconnue, ca fait planter le programme si je delete le feuillage.
    ///Je sais donc qu'il y a une fuite mémoire ici, mais je ne sais pas comment la régler...
}

Coords Arbre::getCoords() const
{
    return m_Coords;
}



void Arbre::dessiner(Svgfile& svgout)
{

    Triangle* tr = dynamic_cast<Triangle*>(this->m_Feuillage);

    if(tr)
    {
        std::ostringstream oss;
        oss << "\t<g id = \"Sapin_" << this
            << "\" transform = \"rotate ("
            << m_rotation << ", "
            << m_Coords.getX() << ", "
            << m_Coords.getY() << ")\">\n\t\t"
            << "<clipPath id=\"CP_" << this <<"\">\n\t\t\t";

        svgout.addString(oss.str());

        m_Tronc.dessiner(svgout);
        if(!m_hivers)
        {
            svgout.addString("\t\t\t");
            m_Feuillage->dessiner(svgout);
        }
        svgout.addString("\t\t</clipPath>\n\t\t");


        m_Ombre.dessiner(svgout);
        svgout.addString("\t\t");
        m_Tronc.dessiner(svgout);
        if(!m_hivers)
        {
            svgout.addString("\t\t");
            m_Feuillage->dessiner(svgout);
        }
        svgout.addString("\t\t");
        m_OmbreRelief.dessiner(svgout);

        svgout.addString("\t</g>\n");
    }
    else
    {
        if(m_degreRecursif == 0)
        {
            std::ostringstream oss, ossCP;
            oss << "\t<g id = \"Chene_" << this << "\">\n\t\t";
            svgout.addString(oss.str());

            ossCP << "<clipPath id=\"CP_" << this <<"\">\n\t\t\t";
            svgout.addString(ossCP.str());

            ///svgout.addString("<!-- -->\n");
            m_Tronc.dessiner(svgout);
            if(!m_hivers)
            {
                svgout.addString("\t\t\t");
                m_Feuillage->dessiner(svgout);
            }
            for (size_t i =0; i<m_Branches.size(); i++)
            {
                m_Branches[i].dessiner_branches(svgout, false);
            }

            svgout.addString("\t\t</clipPath>\n\t\t");



            m_Ombre.dessiner(svgout);

            for (size_t i =0; i<m_Branches.size(); i++)
            {
                m_Branches[i].dessiner_branches(svgout, true);
            }

            svgout.addString("\t\t");
            m_Tronc.dessiner(svgout);
            if(!m_hivers)
            {
                svgout.addString("\t\t\t");
                m_Feuillage->dessiner(svgout);
            }

            svgout.addString("\t\t");
            m_OmbreRelief.dessiner(svgout);

            svgout.addString("\t</g>\n");
        }
    }
}

void Arbre::dessiner_branches(Svgfile& svgout, bool groupe)
{
    for (size_t i =0; i<m_Branches.size(); i++)
    {
        if (groupe)
        {
            std::ostringstream oss;

            oss << "\t\t\t<g id = \"" << this
                << "\" transform = \"rotate ("
                << m_rotation << ", "
                << m_Coords.getX() << ", "
                << m_Coords.getY() << ")\">\n";
                svgout.addString(oss.str());
        }

        for (size_t j =0; j<m_Branches.size(); j++)
        {
            m_Branches[j].dessiner_branches(svgout, groupe);
        }

        svgout.addString("\t\t\t\t");
        m_Tronc.dessiner(svgout);

        if(!m_hivers)
        {
            svgout.addString("\t\t\t\t");
            m_Feuillage->dessiner(svgout);
        }



        if (groupe)
        {
            svgout.addString("\t\t\t</g>\n");
        }

    }
}


bool Arbre::sortByHeigh(Forme* &lhs, Forme* &rhs)
{
    Arbre* arbr1 = dynamic_cast<Arbre*>(lhs);
    Arbre* arbr2 = dynamic_cast<Arbre*>(rhs);

    if (arbr1 && arbr2)
    {
        return arbr1->getCoords().getY() < arbr2->getCoords().getY();
    }
    return false;
}
