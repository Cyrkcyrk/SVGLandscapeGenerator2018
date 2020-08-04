#include "Colline.h"
#include "../util/util.h"
#include "../svg/svgfile.h"

#include <sstream>

Colline::Colline(std::mt19937 _Seed, const t_parameter& Parametres, Couleur _fill)
    : m_Seed{_Seed}, m_Fill{_fill}
{
    int hauteur = 800 * Parametres.hauteur_colline;
    //m_Y = util::alea(300, 600, m_Seed);
    m_X_left = 0;
    m_X_right = Svgfile::WIDTH;

    m_RX = (m_X_right - m_X_left)/2;
    m_RY = m_RX/5;

    m_mont = util::alea(0, 1, m_Seed);
    //m_mont = 1;


    //m_Fill = Couleur("black", 1);

    if (m_mont)
    {
        m_Y = util::alea(hauteur, hauteur+200, m_Seed);
    }
    else
    {
        m_Y = util::alea(hauteur-100, hauteur+100, m_Seed);
    }


}

Colline::~Colline()
{
    //dtor
}

int Colline::getMont() const
{
    return m_mont;
}

double Colline::getY() const
{
    return m_Y;
}

double Colline::getRX() const
{
    return m_RX;
}

double Colline::getRY() const
{
    return m_RY;
}

void Colline::dessiner(Svgfile& svgout)
{
    std::ostringstream oss;

    oss << "\n\n<path id=\"" << this << "\" d=\"M " << m_X_left << " " << m_Y
                              << " \tA " << m_RX << " " << m_RY
                              << " 0 0 "  << m_mont << " "
                              << m_X_right << " " << m_Y
        << "\n\t\t\t\t\tv +1000 \n\t\t\t\t\th "
        << -(Svgfile::WIDTH+10)
        << "z\n\t\t\t\t\t\" fill=\""
        << (std::string) m_Fill << "\" />\n";

    svgout.addString("<clipPath id=\"CP_Colline\">");
    svgout.addString(oss.str());
    svgout.addString("</clipPath>\n");

    svgout.addString(oss.str());




}
