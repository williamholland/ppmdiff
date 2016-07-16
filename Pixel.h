#ifndef PPMDIFFPIXEL_H
#define PPMDIFFPIXEL_H

class Pixel
{

private:
    unsigned char rp;
    unsigned char gp;
    unsigned char bp;

public:
    Pixel(unsigned char _r, unsigned char _g, unsigned char _b);
    friend Pixel operator-(const Pixel &p1, const Pixel &p2);
    friend Pixel operator*(int c, const Pixel &p);
    friend Pixel operator*(const Pixel &p, int c);
    friend Pixel operator/(const Pixel &p, int c);
    inline Pixel operator*=(int c);
    inline Pixel operator/=(int c);
    unsigned char inline r() const;
    unsigned char inline g() const;
    unsigned char inline b() const;

};

inline unsigned char Pixel::r() const
{ return rp; }

inline unsigned char Pixel::g() const
{ return gp; }

inline unsigned char Pixel::b() const
{ return bp; }

inline Pixel Pixel::operator*=(int c)
{ rp*=c; gp*=c; bp*=c; return *this; }

inline Pixel Pixel::operator/=(int c)
{ rp/=c; gp/=c; bp/=c; return *this; }

#endif
