#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Pixel.h"
#include "Pixmap.h"
#include "PortablePixelMap.h"

using std::endl;
using std::string;
using std::list;
using std::getline;

typedef std::list<Pixel>::iterator itr;

bool PortablePixelMap::readPpm(std::ifstream &ppmFile)
{
    if(!ppmFile.is_open())
        return false;

    string line;
    while(getline(ppmFile, line))
    {
        std::istringstream iss(line);
        string word;
        iss >> word;
        // ignore lines starting with # as these are comments
        if( word[0] == '#')
            continue;
        // starting with P3 means ascii
        else if( word == "P3") {
            return this->readAsciiPpm(ppmFile);
        }
        // starting with P3 means raw
        else if( word == "P6") {
            return this->readRawPpm(ppmFile);
        }
        return false;
    }
    return false;
}

bool PortablePixelMap::readAsciiPpm(std::ifstream &ppmFile)
{
    if(!ppmFile.is_open())
        return false;

    //TODO delete any old pixmap
    Pixmap *p = new Pixmap;
    this->pixelmap_p = p;

    string line;
    string word;
    bool gotWidth = false;
    bool gotHeight = false;
    bool gotMaxval = false;

    while(getline(ppmFile, line))
    {
        std::istringstream iss(line);

        // ignore lines starting with # as these are comments
        if( line[line.find_first_not_of(" \t")] == '#')
            continue;

        while(iss >> word)
        {
            if(!gotWidth) {
                this->pixelmap_p->setWidth(std::stoi(word));
                gotWidth = true;
                continue;
            }
            if(!gotHeight) {
                this->pixelmap_p->setHeight(std::stoi(word));
                gotHeight = true;
                continue;
            }
            if(!gotMaxval) {
                this->pixelmap_p->setMaxval(std::stoi(word));
                gotMaxval = true;
                break;
            }
        }
        if(gotMaxval)
            break;
    }

    while(getline(ppmFile, line))
    {
        std::istringstream iss(line);

        // ignore lines starting with # as these are comments
        if( line[line.find_first_not_of(" \t")] == '#')
            continue;

        for( int col = 0; col < this->pixelmap_p->width(); ++col)
        {
            unsigned int ir, ig, ib;
            unsigned char r, g, b;
            iss >> word;
            ir = stoi(word);
            r = (unsigned char) ir;
            iss >> word;
            ig = stoi(word);
            g = (unsigned char) ig;
            iss >> word;
            ib = stoi(word);
            b = (unsigned char) ib;
            Pixel p(r, g, b);
            this->pixelmap_p->addPixel(p);
        }
    }
    return true;
}

bool PortablePixelMap::readRawPpm(std::ifstream &ppmFile)
{
    if(!ppmFile.is_open())
        return false;

    //TODO delete any old pixmap
    Pixmap *p = new Pixmap;
    this->pixelmap_p = p;

    string line;
    string word;
    bool gotWidth = false;
    bool gotHeight = false;
    bool gotMaxval = false;

    while(getline(ppmFile, line))
    {
        std::istringstream iss(line);

        // ignore lines starting with # as these are comments
        if( line[line.find_first_not_of(" \t")] == '#')
            continue;

        while(iss >> word)
        {
            if(!gotWidth) {
                this->pixelmap_p->setWidth(std::stoi(word));
                gotWidth = true;
                continue;
            }
            if(!gotHeight) {
                this->pixelmap_p->setHeight(std::stoi(word));
                gotHeight = true;
                continue;
            }
            if(!gotMaxval) {
                this->pixelmap_p->setMaxval(std::stoi(word));
                gotMaxval = true;
                break;
            }
        }
        if(gotMaxval)
            break;
    }

    while(getline(ppmFile, line))
    {
        std::istringstream iss(line);

        // ignore lines starting with # as these are comments
        if( line[line.find_first_not_of(" \t")] == '#')
            continue;

        unsigned char r,g,b;
        int numPixels = pixelmap_p->width()*pixelmap_p->height();
        for( int col = 0; col < numPixels; ++col)
        {
            iss >> r;
            iss >> g;
            iss >> b;
            Pixel p(r, g, b);
            this->pixelmap_p->addPixel(p);
        }
    }
    return true;
}

bool PortablePixelMap::writeAsciiPpm(std::ofstream &ppmFile)
{
    if(!ppmFile.is_open())
        return false;

    ppmFile << "P3" << endl
            << this->pixelmap_p->width() << " "
            << this->pixelmap_p->height() << endl
            << this->pixelmap_p->maxval() << endl;

    int pixelsOnThisLine = 0;
    unsigned int r, g, b;
    list<Pixel> pixels = this->pixelmap_p->pixels();
    for( itr i = pixels.begin(); i != pixels.end(); ++i ) {

        if( pixelsOnThisLine >= this->pixelmap_p->width() ) {
            ppmFile << endl;
            pixelsOnThisLine = 0;
        }

        r = (*i).r();
        g = (*i).g();
        b = (*i).b();
        ppmFile << r << " "
                << g << " "
                << b << "  ";

        ++pixelsOnThisLine;
    }

    ppmFile << endl;

    return true;
}

bool PortablePixelMap::writeRawPpm(std::ofstream &ppmFile)
{
    if(!ppmFile.is_open())
        return false;

    ppmFile << "P6" << endl
            << this->pixelmap_p->width() << " "
            << this->pixelmap_p->height() << endl
            << this->pixelmap_p->maxval() << endl;

    char r, g, b;
    list<Pixel> pixels = this->pixelmap_p->pixels();
    for( itr i = pixels.begin(); i != pixels.end(); ++i ) {

        r = (*i).r();
        g = (*i).g();
        b = (*i).b();
        ppmFile.write(&r, 1);
        ppmFile.write(&g, 1);
        ppmFile.write(&b, 1);
    }

    ppmFile << endl;

    return true;
}
