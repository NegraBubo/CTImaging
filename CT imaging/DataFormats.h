#pragma once
#include <list>
#include <vector>

struct Point
{
	Point(float x=0, float y=0, float z=0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float x;
	float y;
	float z;
};

struct ContourParameters
{
	int numberOfContourPoints = 0;
	float ContourY = 0;
	std::vector<Point> *contourPoints;
};

struct LineInSpaceParameters
{
	//x=x0 + at; first parameter is x0, second is a, t is constant
	std::pair<float, float> xComponent;
	std::pair<float, float> yComponent;
	std::pair<float, float> zComponent;
};
