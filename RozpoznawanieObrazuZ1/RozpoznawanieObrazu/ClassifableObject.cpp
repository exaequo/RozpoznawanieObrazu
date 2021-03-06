#include "stdafx.h"
#include "ClassifableObject.h"
#include <exception>
#include <sstream>
#include <iomanip>

ClassifableObject::ClassifableObject(int numOfAtt, int objectClass) : numberOfAttributes{numOfAtt}, objectClass{ objectClass }, predictedClass{-1} //, data{data}
{
	attributes = std::vector<float>( numberOfAttributes, 0.f );
}

ClassifableObject::ClassifableObject(const std::vector<std::string> & line) : predictedClass{-1}//, data{}
{
	numberOfAttributes = line.size() - 1; // first information in the data is about the object class
	attributes = std::vector<float>(numberOfAttributes, 0.f); //create array of attributes filled with zeroes

	objectClass = std::stoi(line[0]);
	
	for (int i = 1; i < line.size(); ++i)
	{
		attributes[i - 1] = std::stof(line[i]);
	}

}

ClassifableObject::~ClassifableObject()
{
}

//ClassifableObject::ClassifableObject(ClassifableObject && other):numberOfAttributes{other.numberOfAttributes}, objectClass{other.objectClass}, predictedClass{other.predictedClass}
//{
//	attributes = std::move(other.attributes);
//}

void ClassifableObject::predictClass(int prediction)
{
	predictedClass = prediction;
	Statistics::getInstance().classPrediction(objectClass, prediction);
}

const float & ClassifableObject::operator[](int n) const
{
	if (n < numberOfAttributes && n >= 0)
	{
		return attributes[n];
	}
	//std::stringstream ss{};
	std::cout << "ClassifableObject:: wrong number of attributes (n:" << n << ",att:" << numberOfAttributes<<")\n";
	//throw new std::exception(ss.str().c_str());
}

float & ClassifableObject::operator[](int n)
{
	if (n < numberOfAttributes && n >= 0)
	{
		return attributes[n];
	}
	throw new std::exception("ClassifableObject:: wrong number of attributes");
}

std::string ClassifableObject::toFileFormat() const
{
	std::ostringstream ss; //create stream
	
	ss << std::setw(2) << objectClass << ","; //add the class

	for (int i = 0; i < numberOfAttributes; ++i) //iterate over attributes adding them to stream
	{
		ss << std::setw(4) << attributes[i];
		if (i != numberOfAttributes - 1) { ss << ","; } //if its not the last attribute, add "," between
	}

	return ss.str();
}

std::string ClassifableObject::toOutputFormat() const
{
	std::ostringstream ss;

	ss << toFileFormat() << "||" << objectClass << "/" << predictedClass;

	return ss.str();
}

int ClassifableObject::size() const
{
	return numberOfAttributes;
}

int ClassifableObject::getClass() const
{
	return objectClass;
}

int ClassifableObject::getNumberOfAttributes() const
{
	return numberOfAttributes;
}

int ClassifableObject::getSuccessIdentifier() const
{
	int val = -1;
	if (predictedClass != -1)
	{
		val = (objectClass == predictedClass) ? 1 : 0;
	}

	return val;
}
