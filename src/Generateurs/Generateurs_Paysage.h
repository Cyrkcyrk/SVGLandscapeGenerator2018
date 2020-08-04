#ifndef GENERATEURS_PAYSAGE_H_INCLUDED
#define GENERATEURS_PAYSAGE_H_INCLUDED


#include <random>
#include <sstream>

#include "../graphisme/couleur.h"
#include "../graphisme/gradient.H"
#include "../svg/svgfile.h"
#include "../util/util.h"
#include "../Struct.h"
#include "../console/console.h"
#include "../Menu/Menu.h"
#include "../Generateurs/Generateurs_Paysage.h"

#include "../formes/ToutesLesFormes.h"

namespace Generateur
{
    void ParametresDefauts(t_parameter& Parametres);
    void GenerateurPaysage(t_parameter& Parametres);
    void generateur_PlanColline(Svgfile& svgout, std::mt19937& seed, const t_parameter& Parametres);
    void generateur_PlanMontagne(Svgfile& svgout, std::mt19937& seed, const t_parameter& Parametres);
    void generateur_PlanCiel(Svgfile& svgout, std::mt19937& seed, const t_parameter& Parametres);
}
#endif // GENERATEURS_PAYSAGE_H_INCLUDED
