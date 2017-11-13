#pragma once
#include <vector>
#include <map>
#include <string>
typedef const std::vector<unsigned char> & pointerFunctionType;

//helpers
float M_ij(pointerFunctionType data, int i, int j);
float mi_ij(pointerFunctionType data, int i, int j);
float eta_ij(pointerFunctionType data, int i, int j);
float m_p(pointerFunctionType data, int p, float x_avg, float y_avg);
float mi_p(pointerFunctionType data, int p, float x_avg, float y_avg);
float Hu(pointerFunctionType data);
std::vector<unsigned char> linearFilter(pointerFunctionType data);
void normalize(int newMin, int newMax, std::vector<float> &list, float max = -INFINITY, float min = INFINITY);


std::vector<unsigned char> test(pointerFunctionType data);

//CONTAINS all functions to be used for computing attributes

/*counts white pixels in an image*/
float extractWhitePixelsCount(pointerFunctionType);
/*counts circles in an image*/
float extractRoundShapesCount(pointerFunctionType);
/*count white pixels on bottom half*/
float extractWhitePixelsOnBottomHalfCount(pointerFunctionType);
/*count white pixels on top half*/
float extractWhitePixelsOnTopHalfCount(pointerFunctionType);
/*count black pixels from digit's left side*/
float extractLeftSideShape(pointerFunctionType);
/*count black pixels from digit's right side*/
float extractRightSideShape(pointerFunctionType);
/*count black pixels from digit's top*/
float extractTopShape(pointerFunctionType);
/*count black pixels from digit's bottom*/
float extractBottomShape(pointerFunctionType);
/*size of rectangle with digit*/
float extractRectangleArea(pointerFunctionType);
/*extractWhitePixelsCount and extractRectangleArea ratio*/
float pixelRectangleRatio(pointerFunctionType);
/*get digit's width center */
float centerWidth(pointerFunctionType data);
/*get digit's height center*/
float centerHeight(pointerFunctionType data);
/*check every pixel's distance from digit's center*/
float distanceCenter(pointerFunctionType data);
/*is digit higher or wider? basd on centerWidth and centerHeight*/
float heightWidthRatio(pointerFunctionType data);
/*extracts data from whole image 28x28 and coverts it to float*/
float extractWholeImage(pointerFunctionType data);
/*extracts data from whole image 28x28 and coverts it to float but starts from the end of vector*/
float extractWholeImageInverse(pointerFunctionType data);

float I_1(pointerFunctionType data);
float I_2(pointerFunctionType data);
float I_3(pointerFunctionType data);
float I_4(pointerFunctionType data);
float I_5(pointerFunctionType data);
float I_6(pointerFunctionType data);
float I_7(pointerFunctionType data);
float angle(pointerFunctionType data);

float F_1(pointerFunctionType data);
float F_2(pointerFunctionType data);
float F_3(pointerFunctionType data);

struct FunctionStruct {//because it somehow doesnt work without bewing in some sort of class, for now we'll leave it at that
	/*Vector of functions to be used for computing of attributes*/
	std::map<std::string, float(*)(pointerFunctionType)> extractingFunctions{
		{"whitePixelCount", &extractWhitePixelsCount},
		{"roundShapesCount", &extractRoundShapesCount},
		{"whitePixelOnBottomHalfCount", &extractWhitePixelsOnBottomHalfCount},
		{"whitePixelOnTopHalfCount", &extractWhitePixelsOnTopHalfCount},
		{"leftSideShape", &extractLeftSideShape},
		{"rightSideShape", &extractRightSideShape},
		{"topShape", &extractTopShape},
		{"bottomShape", &extractBottomShape},
		{"rectangleArea", &extractRectangleArea },
		{"pixelRectangleRatio", &pixelRectangleRatio },
		{"centerWidth", &centerWidth},
		{"centerHeight", &centerHeight},
		{"distanceCenter", &distanceCenter},
		{"wholeImage", &extractWholeImage},
		{"wholeImageInv", &extractWholeImageInverse},
		{"heightWidthRatio", &heightWidthRatio},
		{"I_1", &I_1},
		{"I_2", &I_2},
		{"I_3", &I_3},
		{"I_4", &I_4},
		{"I_5", &I_5},
		{"I_6", &I_6},
		{"I_7", &I_7},
		{"angle", &angle},
		{"F_1", &F_1},
		{"F_2", &F_2},
		{"F_3", &F_3}
	};

	static std::vector<std::string> getDefaultAttributesList() {
		return std::vector<std::string>{ "whitePixelOnTopHalfCount", "whitePixelOnBottomHalfCount",
			"leftSideShape", "rightSideShape",
			"topShape", "bottomShape",
			"distanceCenter", "heightWidthRatio"};
		/*, "wholeImage", "wholeImageInv"
	};*/
	};

	static std::vector<std::string> getStarAttributeList() {
		return std::vector<std::string>{ "I_1", "I_2", "I_3", "I_4", "I_5", "I_6", "I_7"};
	};
};






