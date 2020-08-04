#ifndef GRADIENT_H
#define GRADIENT_H

#include "couleur.h"
#include "../svg/svgfile.h"

class Svgfile;

class Gradient : public Couleur
{
    public:
        Gradient(int r, int v, int b, int _offset);
        Gradient(int r, int v, int b, int _offset, double _opacity);
        virtual ~Gradient();

        static void AjouterGradientDefault(Svgfile& svgout);

        operator std::string() const;


    protected:
        int m_offset;
    private:
};

#endif // GRADIENT_H
