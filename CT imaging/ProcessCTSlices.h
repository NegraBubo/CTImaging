#pragma once
#include <string>
#include "DataFormats.h"

class ProcessCTSlices
{
	public:
		static void processCTSlices(std::string inputDirectory, std::string outputDirectory, float beamAngle);
		static void findLineInSpace(float pfiAngle, float thetaAngle, LineInSpaceParameters*);
		static void findIntersectiopnPointBtwYPlaneAndLine(LineInSpaceParameters* lineParameters, float yParameterOfPlane, Point*);
		static bool checkIfPointIsInidePolygon(ContourParameters*, Point*);
};

