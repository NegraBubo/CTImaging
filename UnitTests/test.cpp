#include "pch.h"
#include "gtest/gtest.h"
#include "../CT imaging/ProcessCTSlices.h"
#include "../CT imaging/DataFormats.h"
# define M_PI           3.14159265358979323846

 void test_findLineInSpace(float pfiAngle, float thetaAngle, LineInSpaceParameters* lineInSpace)
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

TEST(FindLineParameters, expectedTrue) {

	LineInSpaceParameters* lineSpaceParameters = new LineInSpaceParameters();
	LineInSpaceParameters* expectedLineSpaceParameters = new LineInSpaceParameters();

	expectedLineSpaceParameters->xComponent = std::make_pair(-1, 0);
	expectedLineSpaceParameters->yComponent = std::make_pair(1, 0);
	expectedLineSpaceParameters->zComponent = std::make_pair(-sqrt(2), 0);

	test_findLineInSpace(3*M_PI/4, 3 * M_PI / 4, lineSpaceParameters);


	EXPECT_NEAR(expectedLineSpaceParameters->xComponent.first, lineSpaceParameters->xComponent.first, 0.1);
	EXPECT_NEAR(expectedLineSpaceParameters->yComponent.first, lineSpaceParameters->yComponent.first,0.1);
	EXPECT_NEAR(expectedLineSpaceParameters->zComponent.first, lineSpaceParameters->zComponent.first,0.1);
	EXPECT_TRUE(true);
}

void test_findIntersectiopnPointBtwYPlaneAndLine(LineInSpaceParameters* lineParameters, float yParameterOfPlane, Point* point)
{
	float t = 0;
	t = yParameterOfPlane / lineParameters->yComponent.first;

	point->x = lineParameters->xComponent.first * t;
	point->y = yParameterOfPlane;
	point->z = lineParameters->zComponent.first * t;
}

TEST(IntersectionPoint, expectedTrue) {

	LineInSpaceParameters* lineSpaceParameters = new LineInSpaceParameters();
	Point* point = new Point;
	Point* expectedPointIntersection = new Point;

	float yParameterOfPlane = 4.5;
	lineSpaceParameters->xComponent = std::make_pair(1, 0);
	lineSpaceParameters->yComponent = std::make_pair(1, 0);
	lineSpaceParameters->zComponent = std::make_pair(2, 0);

	expectedPointIntersection->x = 4.5;
	expectedPointIntersection->y = 4.5;
	expectedPointIntersection->z = 9;


	test_findIntersectiopnPointBtwYPlaneAndLine(lineSpaceParameters, yParameterOfPlane, point);

	EXPECT_EQ(expectedPointIntersection->x, point->x);
	EXPECT_EQ(expectedPointIntersection->y, point->y);
	EXPECT_EQ(expectedPointIntersection->z, point->z);

	EXPECT_TRUE(true);
}

bool test_checkIfPointIsInidePolygon(ContourParameters* contourParameters, Point* point)
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

TEST(PointInPolygon, expectedTrue) {

	ContourParameters* contourParameters = new ContourParameters();
	Point point1 = Point(1,0,1);
	Point point2 = Point(2,0,1);
	Point point3 = Point(3,0,3);
	contourParameters->contourPoints = new std::vector<Point>();
	contourParameters->contourPoints->push_back(point1);
	contourParameters->contourPoints->push_back(point2);
	contourParameters->contourPoints->push_back(point3);

	Point pointToCheck = Point(1.5, 0, 1.2);

	bool pointInsidePolygon = test_checkIfPointIsInidePolygon(contourParameters, &pointToCheck);

	EXPECT_EQ(true, pointInsidePolygon);

	EXPECT_TRUE(true);
}

TEST(PointInPolygon, expectedFalse) {

	ContourParameters* contourParameters = new ContourParameters();
	Point point1 = Point(1, 0, 1);
	Point point2 = Point(2, 0, 1);
	Point point3 = Point(3, 0, 3);
	contourParameters->contourPoints = new std::vector<Point>();
	contourParameters->contourPoints->push_back(point1);
	contourParameters->contourPoints->push_back(point2);
	contourParameters->contourPoints->push_back(point3);

	Point point2ToCheck = Point(1.5, 0, 3);

	bool pointInsidePolygon = test_checkIfPointIsInidePolygon(contourParameters, &point2ToCheck);

	EXPECT_EQ(false,pointInsidePolygon);

	EXPECT_TRUE(true);
}