#pragma once
#include <vector>
#include <string>

class ClassifableObject
{
public:
	/*To be used by extractor*/
	ClassifableObject(int numOfAtt, int objectClass);//, const std::vector<unsigned char> & data);
	/*To be used by classifier when getting objects from the file*/
	ClassifableObject(const std::vector<std::string> & line);
	~ClassifableObject();
	//ClassifableObject(ClassifableObject&&); //move operator

	/* Predicts class of the object and transfers the information to the statistics object */
	void predictClass(int prediction);

	/* We can use [] to get attribute on nth place*/
	const float& operator[](int n) const;
	float& operator[](int n);

	/* Returns string to be placed in file 
	FORMAT: class, att1, att2, ...*/
	std::string toFileFormat() const;
	/*returns the size of the attribute vector*/
	int size() const;
	/*returns what class this object SHOULD be*/
	int getClass() const;

protected:
	int numberOfAttributes;
	int objectClass;
	int predictedClass;
	
	//std::vector<unsigned char> data;	
	std::vector<float> attributes;
};

