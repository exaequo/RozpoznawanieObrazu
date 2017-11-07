#include "stdafx.h"
#include "Classifier.h"
#include <algorithm>

Classifier::Classifier(std::vector<class ClassifableObject>& trainingSet, const std::vector<std::string>& whichAttributesToExtract) : attributesToExtract{whichAttributesToExtract}
{
	testSet = {};

	this->trainingSet = &trainingSet; 
	
	attributeNormalizingValues = std::vector<float>(whichAttributesToExtract.size(), 1.f);
	//TODO training set normalization
}

Classifier::~Classifier()
{
}

void Classifier::computeTestSet(const dataVector & data, std::vector<unsigned char>& labels)
{
	Extractor::staticAttributesExtraction(data, labels, attributesToExtract, testSet);

	for (auto& obj : testSet)//we normalize each object given in the test set
	{
		normalizeObject(obj);
	}
}

void Classifier::knn(int k)
{
	if (!testSet.empty()) //if testSet is not empty then the operations have meaning
	{
		for (int i = 0; i < testSet.size(); ++i)
		{
			
			std::sort(trainingSet->begin(), trainingSet->end(), //sort the training vector
				[&](const ClassifableObject& a, const ClassifableObject& b) -> bool {
				//true if the first element should go before the second
				return metric(testSet[i], a) < metric(testSet[i], b);
			}); 

			std::vector<int> counts = std::vector<int>(attributesToExtract.size(), 0);
			for (int j = 0; j < k; ++j)
			{
				++counts[trainingSet->at(j).getClass()];
			}
			std::sort(counts.begin(), counts.end());

			testSet[i].predictClass(counts[0]);
		}
	}
	else
	{
		throw new std::exception("Classifier wasn't initialized with data");
	}
}

void Classifier::normalizeObject(ClassifableObject & obj) const
{
	for (int i = 0; i < obj.size(); ++i)
	{
		obj[i] *= attributeNormalizingValues.at(i);
	}
}

float Classifier::metric(const ClassifableObject & first, const ClassifableObject & second) const
{
	throw new std::exception("UNIMPLEMENTED BOI");
	return 0.0f;
}
