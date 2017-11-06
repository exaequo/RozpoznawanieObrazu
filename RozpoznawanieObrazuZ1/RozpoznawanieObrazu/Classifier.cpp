#include "stdafx.h"
#include "Classifier.h"


Classifier::Classifier(std::vector<class ClassifableObject>& trainingSet, const std::vector<std::string>& whichAttributesToExtract) : attributesToExtract{whichAttributesToExtract}
{
	this->trainingSet = &trainingSet;
	
	//TODO training set normalization
}

Classifier::~Classifier()
{
}

void Classifier::computeTestSet(const dataVector & data, std::vector<unsigned char>& labels)
{
	Extractor::staticAttributesExtraction(data, labels, attributesToExtract, testSet);
}

void Classifier::knn(int k)
{

	//TODO
}

void Classifier::normalizeObject(ClassifableObject & obj) const
{
	for (int i = 0; i < obj.size(); ++i)
	{
		obj[i] *= attributeNormalizingValues.at(i);
	}
}
