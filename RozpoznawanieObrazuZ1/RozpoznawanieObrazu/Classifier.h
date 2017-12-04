#pragma once
#include <vector>
//#include "Statistics.h"

struct Pixel {
	unsigned char color;
	int properClass;
	int predictedClass;
	std::vector<int> predicitons;

	void predictClass();
};

class Classifier
{
public:
	Classifier(std::vector<class ClassifableObject>& trainingSet, const std::vector<std::string>& whichAttributesToExtract, int numberOfClasses);
	~Classifier();

	/*Creates test set of ClassifableObject out of data containing raw test data
	AND THEN computes attributes of the data*/
	void computeTestSet(const dataVector& data, std::vector<unsigned char> &labels);

	/*Computes values for each Pixel in data and then does the knn*/
	void computeTestSet(const dataVector& data, const dataVector &labels, int k);
	
	/*classifies test set using knn method with given k*/
	void knn(const int k, const int numberOfThreadsToUse = 1);
	/*computes knn for one object*/
	void knnForOneObject(const int k, class ClassifableObject & testedObj) const;


	void knnPart(const int k, std::vector<ClassifableObject>::iterator start, std::vector<ClassifableObject>::iterator end);
	
	const std::vector<class ClassifableObject>&  getTestSet() const;

	/*Normalizes single object depending on attributeNormalizingValues vector*/
	void normalizeObject(class ClassifableObject& obj) const;

	void classifyPixels(std::vector<Pixel> & pixels) const;
private:
	std::vector<class ClassifableObject>* trainingSet;
	std::vector<class ClassifableObject> testSet;
	/*String names of functions to use in extracting attributes*/
	std::vector<std::string> attributesToExtract;

	void normalizeTrainingSet();

	/*To be used with attributes on every object in test set*/
	std::vector<std::pair<float,float>> attributeNormalizingValues;

	/*computes distance between two objects*/
	float metric(const class ClassifableObject& first, const class ClassifableObject& second) const;


	int definedK;
	//Statistics* classStatistics;
};

