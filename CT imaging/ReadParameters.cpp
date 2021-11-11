#pragma once
#include "ReadParameters.h"
#include "DataFormats.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


 void ReadParameters::ReadContourParameters(std::string path, ContourParameters* contourParametersPtr)
{
	ContourParameters contourParameters =  ContourParameters();

    
    string col1, col2;
    ifstream inFile;

    inFile.open(path);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }

    while (inFile >> col1 >> col2) {
        if (contourParametersPtr->numberOfContourPoints == 0)
        {
            contourParametersPtr->numberOfContourPoints = stoi(col1);
            contourParametersPtr->ContourY = stof(col2);
            contourParametersPtr->contourPoints = new std::vector<Point>();
        }
        else
        {
            Point point = Point();
            point.x = stof(col1);
            point.y = contourParametersPtr->ContourY;
            point.z = stof(col2);
            contourParametersPtr->contourPoints->push_back(point);
        }
    }

    inFile.close();
}
