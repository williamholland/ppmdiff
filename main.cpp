#include <fstream>
#include <iostream>

#include "Pixmap.h"
#include "PortablePixelMap.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

ofstream outPpm;

int main(int argc, char *argv[]) {
    if( argc != 4) {
        cout << "usage:" << endl << "    ./a.out 1.ppm 2.ppm out.ppm" << endl;
        return 1;
    }
    char *firstPpmName = argv[1];
    char *secondPpmName = argv[2];
    char *outPpmName = argv[3];

    PortablePixelMap firstPpm;
    PortablePixelMap secondPpm;
    PortablePixelMap resultantPpm;

    ifstream firstPpmFile(firstPpmName);
    firstPpm.readPpm(firstPpmFile);
    firstPpmFile.close();

    ifstream secondPpmFile(secondPpmName);
    secondPpm.readPpm(secondPpmFile);
    secondPpmFile.close();

    Pixmap p1 = *firstPpm.pixelmap();
    Pixmap p2 = *secondPpm.pixelmap();
    Pixmap diff = p1 - p2;

    resultantPpm.setPixmap(&diff);
    ofstream outPpm(outPpmName);
    resultantPpm.writeAsciiPpm(outPpm);
    outPpm.close();

    return 0;
}
