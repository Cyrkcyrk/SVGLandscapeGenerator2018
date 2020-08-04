#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include "../graphisme/couleur.h"
#include "../graphisme/gradient.h"

#include <string>
#include <fstream>
#include <set>

constexpr char defcol[] = "black";

class Gradient;

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=Svgfile::WIDTH, int _height=Svgfile::HEIGH);
        ~Svgfile();

        void addDisk(double x, double y, double r, std::string color=defcol);
        void addCircle(double x, double y, double r, double ep, std::string colorStroke = defcol, std::string colorFill = "none");
        void addEllipses(double x, double y, double rx, double ry, Couleur colorFill, double ep, Couleur colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addLinearGradient(std::string _id, double _x1, double _y1, double _x2, double _y2, std::vector<Gradient>& _tabGrad);
        //void addRadialGradient(std::string _id, double _cx, double _cy, double _r, std::vector<Gradient>& _tabGrad);
        void addRadialGradient(std::string _id, std::vector<Gradient>& _tabGrad);


        void addBackground(Couleur _Couleur);
        void addBackground(std::string _Couleur, double _opacity = 1);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        void addString(std::string _aAjouter);

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;

        static const int WIDTH = 1920;
        static const int HEIGH = 1080;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED



