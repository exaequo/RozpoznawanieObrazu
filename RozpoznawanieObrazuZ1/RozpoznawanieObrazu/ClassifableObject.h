#pragma once
#include <vector>
#include <string>

class ClassifableObject
{
public:
	/*To be used by extractor*/
	ClassifableObject(int numOfAtt, int objectClass, const std::vector<unsigned char> & data);
	/*To be used by classifier when getting objects from the file*/
	ClassifableObject(std::string line);
	~ClassifableObject();
	
	/* Predicts class of the object and transfers the information to the statistics object */
	void predictClass(int prediction);

	/* We can use [] to get attribute on nth place*/
	float& operator[](int n);

	/* Returns string to be placed in file */
	std::string toFileFormat() const;

protected:
	int numberOfAttributes;
	int objectClass;
	int predictedClass;
	
	std::vector<unsigned char> data;	
	float* attributes;
};

