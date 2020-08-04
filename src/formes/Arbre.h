#ifndef ARBRE_H
#define ARBRE_H

#include "Forme.h"
#include <iostream>
#include <random>
#include <algorithm>

#include "../geometrie/coords.h"
#include "../graphisme/couleur.h"
#include "../Struct.h"

#include "Ellipses.h"
#include "Triangle.h"
#include "Rectangle.h"



class Arbre : public Forme
{
    public:
        Arbre(Coords _coord,
              std::mt19937& _Seed,
              t_parameter Parametres,
              double taille = 1,
              double _rotation = 0,
              int degre_recursif = 0,
              Couleur _Tronc = Couleur(0, 0, 0, -1),
              Couleur _Feuillage = Couleur(0, 0, 0, -1));
        virtual ~Arbre();
        Coords getCoords() const;
        virtual void dessiner(Svgfile& svgout);



        static bool sortByHeigh(Forme* &lhs, Forme* &rhs);

    protected:
        void dessiner_branches(Svgfile& svgout, bool groupe);
        Coords m_Coords;
        std::mt19937& m_Seed;
        Forme* m_Feuillage;
        Ellipses m_Ombre;
        Triangle m_Tronc;
        Rectangle m_OmbreRelief;
        bool m_hivers;

        std::vector<Arbre> m_Branches;
        double m_rotation;
        int m_degreRecursif;
    private:
};

#endif // ARBRE_H
