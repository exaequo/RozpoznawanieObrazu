#pragma once
#include <vector>
typedef const std::vector<unsigned char> & pointerFunctionType;

//CONTAINS all functions to be used for computing attributes

/*counts white pixels in an image*/
float extractWhitePixelsCount(pointerFunctionType);
/*counts circles in an image*/
float extractRoundShapesCount(pointerFunctionType);


struct FunctionStruct {//because it somehow doesnt work without bewing in some sort of class, for now we'll leave it at that
	/*Vector of functions to be used for computing of attributes*/
	std::vector<float(*)(pointerFunctionType)> extractingFunctions{
		&extractWhitePixelsCount,
		&extractRoundShapesCount //etc...
	};
};






