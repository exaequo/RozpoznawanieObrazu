#pragma once
#include <vector>
#include <string>
typedef std::vector<std::vector<unsigned char> > dataVector;

class Extractor
{
public:
	
	Extractor();
	~Extractor();

	/*Function to extract attributes from the data given by reader of the file (like MNIST) and create objects to be saved in our file format*/
	void extractAttributes(const dataVector& data, std::vector<unsigned char> &labels, std::vector<std::string> &whichAttributesToExtract);
	
	/*Function to save extractedObjects vector to file*/
	void saveDataToFile(std::string fileName) const;

protected:
	
	/*attributes to extract(which function from extractingFunctions will be used) given to extractAttributes function*/
	std::vector<std::string> attributesToExtract;
	/*objects that are extracted (with proper computed attributes) from extractAttributes function*/
	std::vector<class ClassifableObject*> extractedObjects;
};

