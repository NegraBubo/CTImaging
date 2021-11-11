#pragma once
#include "ProcessCTSlices.h"
#include "ReadParameters.h"
#include <math.h>   
#include <filesystem>
#include <iostream>
#include <fstream>  
#include <execution>
#include <mutex>

# define M_PI           3.14159265358979323846

namespace fs = std::filesystem;


void ProcessCTSlices::processCTSlices(std::string inputDirectory, std::string outputDirectoryFile, float beamAngle)
{
	std::vector<std::pair<std::string, Point>> results;
	std::ofstream outfile(outputDirectoryFile);
	std::mutex m;

	for (const auto& entry : fs::directory_iterator(inputDirectory))
	{
		
		std::wstring wsPath = entry.path().c_str();
		std::string path(wsPath.begin(), wsPath.end());

		ContourParameters* contourParameters = new ContourParameters();
		ReadParameters::ReadContourParameters(path, contourParameters);

		//Find a line that coincides with the angle φ with the x axis in the xy plane, and the angle θ in the yz plane. Let φ be from 1 do 180 degrees. 45 in this case
		LineInSpaceParameters* lineInSpace = new LineInSpaceParameters();
		findLineInSpace(beamAngle,  M_PI / 4, lineInSpace);

		Point* intersectionPoint = new Point();
		findIntersectiopnPointBtwYPlaneAndLine(lineInSpace, contourParameters->ContourY, intersectionPoint);

		//Check if point is within polygon area in a plane
		bool pointInsidePolygon = checkIfPointIsInidePolygon(contourParameters, intersectionPoint);
		if (pointInsidePolygon)
		{
			unsigned first = path.find_last_of("\\");
			unsigned last = path.find(".txt");
			std::string contourName = path.substr(first+1, last - first-1);

			results.push_back(std::make_pair(contourName, *intersectionPoint));
		}

		delete contourParameters;
		delete lineInSpace;
		delete intersectionPoint;
	}

	outfile << "Beam angle: " << beamAngle<<"\n";
	outfile << "Number of points intersected: " << results.size() << "\n";

	for (int i=0; i< results.size(); i++)
	{
		outfile << results.at(i).first<<" : "<<results.at(i).second.x<<" " << results.at(i).second.z << "\n";
	}

	outfile.close();
}

 void ProcessCTSlices::findLineInSpace(float pfiAngle, float thetaAngle, LineInSpaceParameters* lineInSpace)
{
	//Find one arbitrary point in the line 
	//We will use transition from spherical to Cartesian coordinates according to transition equatione
	int r = 2;
	float x = r*sin(thetaAngle) * cos(pfiAngle);
	float y = r*sin(thetaAngle) * sin(pfiAngle);
	float z = r*cos(pfiAngle);

	//Find line equation with two points. One point is found in step above, second point is (0,0,0). From the equation of line with two known points, and when one point is (0,0,0), we can find parameters:
	lineInSpace->xComponent = std::make_pair(x, 0);
	lineInSpace->yComponent = std::make_pair(y, 0);
	lineInSpace->zComponent = std::make_pair(z, 0);
}

 void ProcessCTSlices::findIntersectiopnPointBtwYPlaneAndLine(LineInSpaceParameters* lineParameters, float yParameterOfPlane, Point* point)
{
	float t = 0;
	t = yParameterOfPlane / lineParameters->yComponent.first;

	point->x = lineParameters->xComponent.first * t;
	point->y = yParameterOfPlane;
	point->z = lineParameters->zComponent.first * t;
}

 bool ProcessCTSlices::checkIfPointIsInidePolygon(ContourParameters* contourParameters, Point* point)
 {
	 std::vector<Point>* points = contourParameters->contourPoints;
	 int i, j, numContourPoints = points->size();
	 bool intersected = false;
	
	 for (i = 0, j = numContourPoints - 1; i < numContourPoints; j = i++) {
		 if (((points->at(i).z >= point->z) != (points->at(j).z >= point->z)) &&
			 (point->x <= (points->at(j).x - points->at(i).x) * (point->z - points->at(i).z) / (points->at(j).z - points->at(i).z) + points->at(i).x)
			 )
			 intersected = !intersected;
	 }

	 return intersected;
 }
