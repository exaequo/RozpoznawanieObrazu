#include "stdafx.h"
#include "ClassifableObject.h"
#include <exception>
#include <sstream>
#include <iostream>

ClassifableObject::ClassifableObject(int numOfAtt, int objectClass) : numberOfAttributes{numOfAtt}, objectClass{ objectClass }, predictedClass{-1} //, data{data}
{
	attributes = std::vector<float>( numberOfAttributes, 0.f );
}

ClassifableObject::ClassifableObject(const std::vector<std::string> & line) : predictedClass{-1}//, data{}
{
	std::cout << "LOADING OBJ: " << line.size() << "\n";
	
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

void ClassifableObject::predictClass(int prediction)
{
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
	
	ss << objectClass << ","; //add the class

	for (int i = 0; i < numberOfAttributes; ++i) //iterate over attributes adding them to stream
	{
		ss << attributes[i];
		if (i != numberOfAttributes - 1) { ss << ","; } //if its not the last attribute, add "," between
	}

	return ss.str();
}

int ClassifableObject::size() const
{
	return numberOfAttributes;
}
