#include "stdafx.h"
#include "Extractor.h"



Extractor::Extractor()
{
}

Extractor::~Extractor()
{
	//for (auto singleObject : extractedObjects)
	//{
	//	delete &singleObject;
	//}
}

void Extractor::extractAttributes(const dataVector& data, std::vector<unsigned char> &dataLabels, const std::vector<std::string> &whichAttributesToExtract)
{
	if (extractedObjects.size() > 0)
	{
		extractedObjects.clear();
	}
	attributesToExtract = { whichAttributesToExtract };
	extractedObjects = {};
	FunctionStruct func{};

	//We iterate over a vector of data
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		//Create a new ClassifableObject
		ClassifableObject obj = ClassifableObject(attributesToExtract.size(), (int)dataLabels[i]);// , data[i]));

		//Iterate over all attributes that we want to compute for the object
		for (unsigned int n = 0; n < attributesToExtract.size(); ++n)
		{
			//we compute the value of the nth attribute of object using function defined by nth argument of attributesToExtract
			obj[n] = func.extractingFunctions[attributesToExtract.at(n)](data[i]); 
		}
		//push created object to the vector
		extractedObjects.push_back(obj);

	}
}

std::vector<std::string> Extractor::getDefaultAttributesList()
{
	return std::vector<std::string>{"whitePixelCount", "roundShapesCount", "whitePixelOnBottomHalfCount", "whitePixelOnTopHalfCount", "leftSideShape"};
}

const std::vector<class ClassifableObject>& Extractor::getObjects() const
{
	return extractedObjects;
}

