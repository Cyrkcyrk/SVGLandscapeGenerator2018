#include "couleur.h"
#include "../svg/svgfile.h"
#include "../util/util.h"
#include <iostream>
#include <sstream>

Couleur::Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : m_rouge{rouge}, m_vert{vert}, m_bleu{bleu}, m_opacity{1}
{
    m_StrBool = false;
}

Couleur::Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu, double opactity)
    : m_rouge{rouge}, m_vert{vert}, m_bleu{bleu}, m_opacity{opactity}
{
    m_StrBool = false;
}

Couleur::Couleur()
    : Couleur(0, 0, 0) // Délégation de constructeur
{
    m_StrBool = false;
}

Couleur::Couleur(std::string _str, double opacity)
    : m_Str{_str}, m_opacity{opacity}
{
    m_StrBool = true;
}


void Couleur::afficher() const
{
    std::cout << "(" << (int)m_rouge << ", " << (int)m_vert << ", " << (int)m_bleu << ")" << std::endl;
}

uint8_t Couleur::saisirCanal()
{
    int val;
    std::cin >> val;
    while (val<0 || val>255)
    {
        std::cout << "Mauvaise valeur couleur, recommencer : ";
        util::videCin();
        std::cin >> val;
    }

    return (uint8_t)val;
}

void Couleur::saisir()
{
    std::cout << "Veuillez saisir rouge vert et bleu SVP : ";
    m_rouge = saisirCanal();
    m_vert = saisirCanal();
    m_bleu = saisirCanal();
}


uint8_t Couleur::muterCanal(uint8_t v, double amplitude, std::mt19937& Seed)
{
    int val=v;

    val += util::alea(-amplitude, amplitude, Seed);

    if ( val<0 )
        val = 0;

    if ( val>255 )
        val = 255;

    return (uint8_t)val;
}

void Couleur::muter(double amplitude, std::mt19937& Seed)
{
    m_rouge = muterCanal(m_rouge, amplitude, Seed);
    m_vert = muterCanal(m_vert, amplitude, Seed);
    m_bleu = muterCanal(m_bleu, amplitude, Seed);
}


double Couleur::getOpacity() const
{
    return this->m_opacity;
}

Couleur::operator std::string() const
{

    if (m_StrBool)
    {
        return m_Str;
    }
    else
    {
        return Svgfile::makeRGB(m_rouge, m_vert, m_bleu);
    }
}

Couleur::operator double() const
{
    return this->m_opacity;
}
