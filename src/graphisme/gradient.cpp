#include "Gradient.h"

#include "../svg/svgfile.h"

#include <sstream>
#include <iostream>
#include <string>

Gradient::Gradient(int r, int v, int b, int _offset)
    : Couleur(r, v, b), m_offset{_offset}
{

}

Gradient::Gradient(int r, int v, int b, int _offset, double _opacity)
    : Couleur(r, v, b), m_offset{_offset}
{
    this->m_opacity = _opacity;
}


Gradient::~Gradient()
{
    //dtor
}


void Gradient::AjouterGradientDefault(Svgfile& svgout)
{
    std::vector<Gradient> CielBleu;
    CielBleu.push_back(Gradient(0, 40, 100, 0));
    CielBleu.push_back(Gradient(0, 40, 255, 10));
    CielBleu.push_back(Gradient(255, 255, 255, 60));


    std::vector<Gradient> CielNuit;
    const int eclaircie = 50;
    CielNuit.push_back(Gradient(40+eclaircie, 40+eclaircie, 70+eclaircie, 0));
    CielNuit.push_back(Gradient(49+eclaircie, 53+eclaircie, 95+eclaircie, 30));
    CielNuit.push_back(Gradient(39+eclaircie, 38+eclaircie, 67+eclaircie, 60));

    std::vector<Gradient> Ombre;
    Ombre.push_back(Gradient(0, 0, 0, 0, 0.5));
    Ombre.push_back(Gradient(0, 0, 0, 100, 0));

    std::vector<Gradient> Soleil;
    Soleil.push_back(Gradient(255, 255, 255, 0, 1));
    Soleil.push_back(Gradient(255, 255, 255, 5, 1));
    Soleil.push_back(Gradient(255, 200, 30, 20, 1));
    Soleil.push_back(Gradient(255, 200, 30, 100, 0));

    std::vector<Gradient> Lune;
    Lune.push_back(Gradient(255, 255, 255, 0, 1));
    Lune.push_back(Gradient(255, 255, 255, 100, 0));

    std::vector<Gradient> VoieLactee;
    VoieLactee.push_back(Gradient(255, 255, 255, 0, 0));
    VoieLactee.push_back(Gradient(255, 255, 255, 50, 0.5));
    VoieLactee.push_back(Gradient(255, 255, 255, 100, 0));

    std::vector<Gradient> RedStar;
    RedStar.push_back(Gradient(255, 0, 0, 0, 1));
    RedStar.push_back(Gradient(200, 0, 0, 50, 0));
    RedStar.push_back(Gradient(0, 0, 0, 100, 0));

    std::vector<Gradient> BlueStar;
    BlueStar.push_back(Gradient(0, 0, 255, 0, 1));
    BlueStar.push_back(Gradient(0, 0, 200, 50, 0));
    BlueStar.push_back(Gradient(0, 0, 0, 100, 0));

    svgout.addLinearGradient("CielBleu", 0, 0, 0, 1, CielBleu);
    svgout.addLinearGradient("CielNuit", 0, 0, 0, 1, CielNuit);
    svgout.addLinearGradient("GD_VoieLactee", 0, 0, 1, 0, VoieLactee);

    //svgout.addRadialGradient("Ombre", 1, 1, 1, Ombre);
    svgout.addRadialGradient("Ombre", Ombre);
    svgout.addRadialGradient("GD_Soleil", Soleil);
    svgout.addRadialGradient("GD_Lune", Lune);
    svgout.addRadialGradient("GD_RedStar", RedStar);
    svgout.addRadialGradient("GD_BlueStar", BlueStar);
}

/**
<linearGradient id=\"Ciel_Bleu\" x1=\"0\" x2=\"0\" y1=\"0\" y2=\"1\">
    <stop offset=\"0%\" stop-color=\"rgb(0,40,100)\"/>
    <stop offset=\"25%\" stop-color=\"rgb(0,40,255)\"/>
    <stop offset=\"100%\" stop-color=\"rgb(255,255,255)\"/>
</linearGradient>
**/

Gradient::operator std::string() const
{
    std::ostringstream oss;
    //std::cout << m_offset << std::endl;
    oss << "<stop offset=\"" << m_offset
        << "%\" stop-color=\"" << Svgfile::makeRGB(m_rouge, m_vert, m_bleu)
        << "\" stop-opacity=\"" << m_opacity
        << "\"/>\n";

    return oss.str();
}
