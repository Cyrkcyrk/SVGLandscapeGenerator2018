#ifndef FORME_H
#define FORME_H

#include "../svg/svgfile.h"

class Forme
{
    public:
        virtual ~Forme() = default;
        virtual void dessiner(Svgfile& svgout) = 0;

    protected:

    private:
};

#endif // FORME_H
