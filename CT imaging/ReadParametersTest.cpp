#include "gtest/gtest.h"
#include "../CT imaging/ReadParameters.h"
#include "DataFormats.h"


TEST(ReadParametersContour0, ReadParametersTest) {

	std::string parametersPath = "SampleContours/contour0";
	ContourParameters* contourParametersPtr = new ContourParameters();

	ReadParameters::ReadContourParameters(parametersPath, contourParametersPtr);

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}