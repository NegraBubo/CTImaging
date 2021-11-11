// CT imaging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ReadParameters.h"
#include "ProcessCTSlices.h"

int main(int argc,char* argv[])
{

    std::cout << "CT imaging program!\n";
    char processCT = 'Y';
    std::string contourPath = "";
    std::string outputDirectoryFile = "";
    float beamAngle = 0;

    while (processCT == 'Y' || processCT == 'y')
    {
        std::cout << "Do you want to process a new CT imaging? Please press Y for yes. \n";
        std::cin >> processCT;
        if (processCT == 'Y')
        {
            std::cout << "Insert contour file path: \n";
            std::cin >> contourPath;
            std::cout << "Insert beam angle: \n";
            std::cin >> beamAngle;
            std::cout << "Insert output file name with the path: \n";
            std::cin >> outputDirectoryFile;
            ProcessCTSlices::processCTSlices(contourPath, outputDirectoryFile, beamAngle);

        }
        else
        {
            break;
        }

    }
}


