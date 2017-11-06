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

struct FunctionStruct {//because it somehow doesnt work without bewing in some sort of class, for now we'll leave it at that
	/*Vector of functions to be used for computing of attributes*/
	std::map<std::string, float(*)(pointerFunctionType)> extractingFunctions{
		{"whitePixelCount", &extractWhitePixelsCount},
		{"roundShapesCount", &extractRoundShapesCount},
		{"whitePixelOnBottomHalfCount", &extractWhitePixelsOnBottomHalfCount},
		{"whitePixelOnTopHalfCount", &extractWhitePixelsOnTopHalfCount},
		{"leftSideShape", &extractLeftSideShape}
	};
};






