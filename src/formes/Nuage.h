#ifndef NUAGE_H
#define NUAGE_H

#include "Polygone.h"

/*
<path d="M30 30 a 2 1 - 0 0 10 -1
				a 2 1 0 0 0 1 -10
				a 2 1 0 0 0 -10 1
				a 2 1 0 0 0 -10 5
				A 2.5 2.5 0 0 0 30 30
				" stroke="black" fill="rgb(200, 210, 255)"/>*/


class Nuage : public Polygone
{
    public:
        Nuage(Coords _coord, std::mt19937& _Seed);
        virtual ~Nuage();
        virtual void dessiner(Svgfile& svgout);

    protected:

    private:
};

#endif // NUAGE_H
