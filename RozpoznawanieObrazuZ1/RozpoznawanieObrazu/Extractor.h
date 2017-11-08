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
	void extractAttributes(const dataVector& data, std::vector<unsigned char> &labels, const std::vector<std::string> &whichAttributesToExtract);
	
	/*Extracts attributes and saves it on given vectors*/
	static void staticAttributesExtraction(const dataVector& data, std::vector<unsigned char> &labels, const std::vector<std::string> &whichAttributesToExtract, 
		std::vector<class ClassifableObject> &extractedObjects);

	static std::vector<std::string> getDefaultAttributesList();

	const std::vector<class ClassifableObject>& getObjects() const;

	const std::vector<std::string>& getAttributesToExtract() const;
protected:
	/*attributes to extract(which function from extractingFunctions will be used) given to extractAttributes function*/
	std::vector<std::string> attributesToExtract;
	/*objects that are extracted (with proper computed attributes) from extractAttributes function*/
	std::vector<class ClassifableObject> extractedObjects;
};

