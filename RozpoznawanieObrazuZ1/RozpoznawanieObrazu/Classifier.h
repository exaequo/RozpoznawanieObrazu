#pragma once
#include <vector>
class Classifier
{
public:
	Classifier(std::vector<class ClassifableObject>& trainingSet, const std::vector<std::string>& whichAttributesToExtract);
	~Classifier();

	/*Creates test set of ClassifableObject out of data containing raw test data
	AND THEN computes attributes of the data*/
	void computeTestSet(const dataVector& data, std::vector<unsigned char> &labels);
	
	/*classifies test set using knn method with given k*/
	void knn(int k);

	/*Normalizes single object depending on attributeNormalizingValues vector*/
	void normalizeObject(class ClassifableObject& obj) const;
private:
	std::vector<class ClassifableObject>* trainingSet;
	std::vector<class ClassifableObject> testSet;
	/*String names of functions to use in extracting attributes*/
	std::vector<std::string> attributesToExtract;

	/*To be used with attributes on every object in test set*/
	std::vector<float> attributeNormalizingValues;

};
