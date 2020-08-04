#ifndef COLLINE_H
#define COLLINE_H

#include "Forme.h"
#include "../Struct.h"
#include "Arbre.h"
#include <iostream>
#include <random>

#include "../graphisme/couleur.h"

/*
double colline_Y = 450;
    double colline_X_left = -5;
    double colline_X_right = Svgfile::WIDTH+5;

    double colline_RX = (colline_X_right - colline_X_left)/2;
    double colline_RY = colline_RX/5;

*/

class Colline : public Forme
{
    public:
        Colline(std::mt19937 _Seed, const t_parameter& Parametres, Couleur _fill);
        virtual ~Colline();

        virtual void dessiner(Svgfile& svgout);

        int getMont() const;
        double getY() const;
        double getRX() const;
        double getRY() const;

    protected:
        std::mt19937 m_Seed;
        double m_Y;
        double m_X_left;
        double m_X_right;

        double m_RX;
        double m_RY;

        int m_mont;

        Couleur m_Fill;

    private:
};

#endif // COLLINE_H
