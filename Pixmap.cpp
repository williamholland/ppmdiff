#include <list>
#include <iostream>

#include "Pixmap.h"

using std::list;

typedef list<Pixel>::iterator itr;
typedef list<Pixel>::const_iterator citr;

int euclid(int u, int v) {
    while ( v != 0) {
        int r = u % v; u = v; v = r;
    }
    return u;
}

Pixmap operator-(const Pixmap &p1, const Pixmap &p2)
{
    Pixmap pixmap;
    int gcd = euclid(p1.maxval(),p2.maxval());
    Pixmap p1prime;
    Pixmap p2prime;

    // scale to a common maxval
    //p1prime = p1 * ( p2.maxval() / gcd );
    //p2prime = p2 * ( p1.maxval() / gcd );
    p1prime = p1;
    p2prime = p2;

    pixmap.setWidth(p1.width());
    pixmap.setHeight(p1.height());
    pixmap.setMaxval(p1.maxval() * p2.maxval() / gcd);

    list<Pixel> pixels1 = p1prime.pixels();
    list<Pixel> pixels2 = p2prime.pixels();
    citr i1 = pixels1.begin();
    for( citr i2 = pixels2.begin(); i2 != pixels2.end(); ++i2) {
        Pixel pix = (*i1) - (*i2);
        pixmap.addPixel(pix);
        ++i1;
    }

    return pixmap;
}

Pixmap operator*(int c, const Pixmap &p)
{
    Pixmap pixmap;
    Pixel *pix;
    pixmap.setWidth(p.width());
    pixmap.setHeight(p.height());
    pixmap.setMaxval(c * p.maxval());
    list<Pixel> pixels = p.pixels();
    for( citr i = pixels.begin(); i != pixels.end(); ++i) {
        *pix = c * (*i);
        pixmap.addPixel(*pix);
    }
    return pixmap;
}

Pixmap operator*(const Pixmap &p, int c)
{
    return c * p;
}

Pixmap operator/(const Pixmap &p, int c)
{
    Pixmap pixmap;
    Pixel *pix;
    pixmap.setWidth(p.width());
    pixmap.setHeight(p.height());
    pixmap.setMaxval(p.maxval() / c);
    list<Pixel> pixels = p.pixels();
    for( citr i = pixels.begin(); i != pixels.end(); ++i) {
        *pix = (*i) / c;
        pixmap.addPixel(*pix);
    }
    return pixmap;
}

Pixmap Pixmap::operator*=(int c)
{
    this->setMaxval(c * this->maxval());
    for( itr i = pixels_p.begin(); i != pixels_p.end(); ++i) {
        (*i) *= c;
    }
    return *this;
}

Pixmap Pixmap::operator/=(int c)
{
    this->setMaxval(this->maxval() / c);
    for( itr i = pixels_p.begin(); i != pixels_p.end(); ++i) {
        (*i) /= c;
    }
    return *this;
}

