#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

#include <string>
#include <cstdint>
#include <random>

class Couleur
{
    public :
        Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu);
        Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu, double opacity);
        Couleur(std::string _str, double opacity);
        Couleur();
        void afficher() const;
        void saisir();
        void muter(double amplitude, std::mt19937& Seed);

        double getOpacity() const;

        operator std::string() const;
        operator double() const;

    protected :
        // uint8_t équivalent à unsigned char :
        // unsigned 8 bits (8 bits non signé)
        uint8_t saisirCanal();
        uint8_t muterCanal(uint8_t v, double amplitude, std::mt19937& Seed);


        uint8_t m_rouge, m_vert, m_bleu;
        std::string m_Str;
        double m_opacity;
        bool m_StrBool;


};

#endif // COULEUR_H_INCLUDED
