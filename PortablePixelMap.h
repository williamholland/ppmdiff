#ifndef PPMDIFFPPM_H
#define PPMDIFFPPM_H

#include <fstream>
#include <string>

#include "Pixmap.h"

class PortablePixelMap
{
private:
    Pixmap *pixelmap_p;

public:
    inline Pixmap *pixelmap();
    inline void setPixmap(Pixmap *p);
    bool readPpm(std::ifstream &ppmFile);
    bool readAsciiPpm(std::ifstream &ppmFile);
    bool readRawPpm(std::ifstream &ppmFile);
    bool writeAsciiPpm(std::ofstream &ppmFile);
    bool writeRawPpm(std::ofstream &ppmFile);
};

inline Pixmap *PortablePixelMap::pixelmap()
{ return pixelmap_p; }

inline void PortablePixelMap::setPixmap(Pixmap *p)
{ pixelmap_p = p; }

#endif
