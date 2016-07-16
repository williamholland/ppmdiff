#include "Pixel.h"

Pixel::Pixel(unsigned char _r, unsigned char _g, unsigned char _b)
{ rp = _r; gp = _g; bp = _b; }

Pixel operator-(const Pixel &p1, const Pixel &p2)
{
    unsigned char r, g, b;
    r = p1.r() - p2.r();
    g = p1.g() - p2.g();
    b = p1.b() - p2.b();
    return Pixel(r,g,b);
}

Pixel operator*(int c, const Pixel &p)
{
    unsigned char r, g, b;
    r = c * - p.r();
    g = c * - p.g();
    b = c * - p.b();
    return Pixel(r,g,b);
}

Pixel operator*(const Pixel &p, int c)
{
    return c*p;
}

Pixel operator/(const Pixel &p, int c)
{
    unsigned char r, g, b;
    r = p.r() / c;
    g = p.g() / c;
    b = p.b() / c;
    return Pixel(r,g,b);
}
