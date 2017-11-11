#pragma once
#include <vector>
#include <map>
#include <string>
typedef const std::vector<unsigned char> & pointerFunctionType;

//CONTAINS all functions to be used for computing attributes

/*counts white pixels in an image*/
float extractWhitePixelsCount(pointerFunctionType);
/*counts circles in an image*/
float extractRoundShapesCount(pointerFunctionType);
/*count white pixels on bottom half*/
float extractWhitePixelsOnBottomHalfCount(pointerFunctionType);
/*count white pixels on top half*/
float extractWhitePixelsOnTopHalfCount(pointerFunctionType);
/*some special idea*/
float extractLeftSideShape(pointerFunctionType);

float extractRightSideShape(pointerFunctionType);

float extractTopShape(pointerFunctionType);

float extractBottomShape(pointerFunctionType);

float extractArea(pointerFunctionType);

float test(pointerFunctionType);

float centerWidth(pointerFunctionType data);

float centerHeight(pointerFunctionType data);

float distanceCenter(pointerFunctionType data);
/*extracts data from whole image 28x28 and coverts it to float*/
float extractWholeImage(pointerFunctionType data);
/*extracts data from whole image 28x28 and coverts it to float but starts from the end of vector*/
float extractWholeImageInverse(pointerFunctionType data);

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
		{"area", &extractArea},
		{"ratio", &test},
		{"centerWidth", &centerWidth},
		{"centerHeight", &centerHeight},
		{"distanceCenter", &distanceCenter},
		{"wholeImage", &extractWholeImage},
		{"wholeImageInv", &extractWholeImageInverse}
	};

	static std::vector<std::string> getDefaultAttributesList() {
		return std::vector<std::string>{ "whitePixelOnTopHalfCount", "whitePixelOnBottomHalfCount", "leftSideShape", "rightSideShape",
			"topShape", "bottomShape", "area", "ratio", "distanceCenter"};
		/*, "wholeImage", "wholeImageInv"
	};*/
	};
};






