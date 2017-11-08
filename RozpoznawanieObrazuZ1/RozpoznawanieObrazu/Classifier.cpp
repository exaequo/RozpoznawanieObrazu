#include "stdafx.h"
#include "Classifier.h"
#include <algorithm>
#include <math.h>
#include <thread>
#include <map>
#include <iostream>

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

void Classifier::knn(const int k, const int numberOfThreadsToUse)
{
	if (!testSet.empty()) //if testSet is not empty then the operations have meaning
	{
		std::vector<std::thread> threads(numberOfThreadsToUse);

		for (int i = 0; i < numberOfThreadsToUse; ++i)
		{
			std::vector<ClassifableObject> part;// (testSet.begin() + (testSet.size() / numberOfThreadsToUse) * i,
												//testSet.begin() + (testSet.size() / numberOfThreadsToUse) * (i + 1));
			if (i != numberOfThreadsToUse - 1)
			{
				part = std::vector<ClassifableObject>(testSet.begin() + (testSet.size() / numberOfThreadsToUse) * i,
													  testSet.begin() + (testSet.size() / numberOfThreadsToUse) * (i + 1));
			}
			else {
				part = std::vector<ClassifableObject>(testSet.begin() + (testSet.size() / numberOfThreadsToUse) * i, testSet.end() - 1);										
			}
			
			threads[i] = std::thread(&Classifier::knnPart, this, k, part); //start threads with parts of knn vector
		}

		for (auto& t : threads)
		{
			t.join();//join the threads
		}
	}
	else
	{
		throw new std::exception("Classifier wasn't initialized with data");
	}
}

void Classifier::knnPart(const int k, std::vector<ClassifableObject>::iterator start, std::vector<ClassifableObject>::iterator end)
{
	for (int i = 0; i < testSetPart.size(); ++i)
	{

		std::sort(trainingSet->begin(), trainingSet->end(), //sort the training vector
			[&](const ClassifableObject& a, const ClassifableObject& b) -> bool {
			//true if the first element should go before the second
			return metric(testSetPart[i], a) < metric(testSetPart[i], b);
		});

		std::map<int, int> counts{}; //create a map; first: class, second: quantitity
		std::vector<std::pair<int, int> >countsVec{}; //create a vector of pairs same as map

		for (int j = 0; j < k; ++j)
		{
			++counts[trainingSet->at(j).getClass()]; //create needed positions in map
		}
		for (auto elem : counts)
		{
			countsVec.push_back({ elem.first, elem.second });//transfer information to vector
		}

		std::sort(countsVec.begin(), countsVec.end(), //sort vector over quantity
			[&](std::pair<int, int> &l, std::pair<int, int> &r)->bool {
			return l.second > r.second;
		});


		testSetPart[i].predictClass(countsVec[0].first);//first in first elem in vector is the one with largest quantity
	}
	std::cout << "THREAD FINISHED\n";
}

const std::vector<class ClassifableObject>& Classifier::getTestSet() const
{
	return testSet;
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
	float result{ 0.f };

	for (int i = 0; i < first.size(); ++i)
	{
		result += fabsf(first[i] - second[i]);
	}
	return result;
}
