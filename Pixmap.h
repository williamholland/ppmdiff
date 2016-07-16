#ifndef PPMDIFFPIXMAP_H
#define PPMDIFFPIXMAP_H

#include <list>

#include "Pixel.h"

using std::list;

class Pixmap
{

private:
    int width_p;
    int height_p;
    int maxval_p;
    list<Pixel> pixels_p;

public:
    friend Pixmap operator-(const Pixmap &p1, const Pixmap &p2);
    friend Pixmap operator*(int c, const Pixmap &p);
    friend Pixmap operator*(const Pixmap &p, int c);
    friend Pixmap operator/(const Pixmap &p, int c);
    Pixmap operator*=(int c);
    Pixmap operator/=(int c);
    inline int width() const;
    inline int height() const;
    inline int maxval() const;
    inline list<Pixel> pixels() const;
    inline void setWidth(int w);
    inline void setHeight(int h);
    inline void setMaxval(int m);
    inline void addPixel(Pixel p);

};

inline int Pixmap::width() const
{ return width_p; }

inline int Pixmap::height() const
{ return height_p; }

inline int Pixmap::maxval() const
{ return maxval_p; }

inline list<Pixel> Pixmap::pixels() const
{ return pixels_p; }

inline void Pixmap::setWidth(int w)
{ width_p = w; }

inline void Pixmap::setHeight(int h)
{ height_p = h; }

inline void Pixmap::setMaxval(int m)
{ maxval_p = m; }

inline void Pixmap::addPixel(Pixel p)
{ this->pixels_p.push_back(p); }

#endif
