#include "stdafx.h"
#include "ClassifableObject.h"
#include <exception>

ClassifableObject::ClassifableObject(int numOfAtt, int objectClass, const std::vector<unsigned char>& data) : numberOfAttributes{numOfAtt}, objectClass{ objectClass }, predictedClass{-1}, data{data}
{
	attributes = new float[numberOfAttributes];
}

ClassifableObject::ClassifableObject(std::string line)
{
	//TODO
}

ClassifableObject::~ClassifableObject()
{
	delete attributes;
}

float & ClassifableObject::operator[](int n)
{
	if (n < numberOfAttributes && n >= 0)
	{
		return attributes[n];
	}
	throw new std::exception("ClassifableObject:: wrong number of attributes");
}
