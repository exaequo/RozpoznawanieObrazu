#include "stdafx.h"
#include "Classifier.h"
#include <algorithm>
#include <math.h>
#include <thread>
#include <map>
#include <limits>
#include <iostream>

Classifier::Classifier(std::vector<class ClassifableObject>& trainingSet, const std::vector<std::string>& whichAttributesToExtract, int numberOfClassess) : attributesToExtract{whichAttributesToExtract}, classes{ numberOfClassess }
{
	testSet = {};

	this->trainingSet = &trainingSet; 
	
	attributeNormalizingValues = std::vector<std::pair<float, float>>(whichAttributesToExtract.size(), { 0.f, 1.f });

	normalizeTrainingSet();

	//classStatistics = &Statistics::getInstance();
	Statistics::getInstance().createMistakesMatrix(numberOfClassess);
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

void Classifier::computeTestSet(const dataVector & data, const dataVector & labels, int k)
{
	definedK = k;
	for (int i = 0; i < data.size(); ++i)
	{
		std::cout << "PREDICTING IMAGE "<< i <<"...\n";
		std::vector<Pixel> pixels;
		for (int j = 0; j < data[i].size(); ++j)
		{
			pixels.push_back({
				data[i][j],//color
				TexturesReader::mapColorToClass(labels[i][j]),//properClass
				-1,//predictedClass
				{0,0,0,0} //predicitons
			});
		}

		classifyPixels(pixels); //compute knn for pixels of the image

		for (int j = 0; j < pixels.size(); ++j)
		{
			//std::cout << j << ". ";
			pixels[j].predictClass();
		}

		Statistics::getInstance().printMistakesMatrix(std::cout);
	}
}

void Classifier::knn(const int k, const int numberOfThreadsToUse)
{
	if (!testSet.empty()) //if testSet is not empty then the operations have meaning
	{
		std::vector<std::thread> threads(numberOfThreadsToUse);

		for (int i = 0; i < numberOfThreadsToUse; ++i)
		{		
			auto start = testSet.begin() +(testSet.size() / numberOfThreadsToUse) * i;
			auto end = testSet.begin();// +(testSet.size() / numberOfThreadsToUse) * (i + 1);

			if (i != numberOfThreadsToUse - 1)
			{
				end = testSet.begin() +(testSet.size() / numberOfThreadsToUse) * (i + 1);
			}
			else
			{
				end = testSet.end();
			}

			threads[i] = std::thread(&Classifier::knnPart, this, k, start, end); //start threads with parts of knn vector
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
	std::vector<ClassifableObject*> trainingSetCopy{};

	for (auto i = trainingSet->begin(); i < trainingSet->end(); ++i)
	{
		trainingSetCopy.push_back(&(*i));
	}

	bool toSortOrNotToSort = 54 < k;//log2(trainingSet->size()) < k;


	for (auto i = start; i < end; ++i)
	{
		if (toSortOrNotToSort)
		{
			std::sort(trainingSetCopy.begin(), trainingSetCopy.end(), //sort the training vector
				[&](const ClassifableObject* a, const ClassifableObject* b) -> bool {
				//true if the first element should go before the second
				if (b->getNumberOfAttributes() > 0) { return metric((*i), *a) < metric((*i), *b); }
				return false;
			});

			std::map<int, int> counts{}; //create a map; first: class, second: quantitity
			std::vector<std::pair<int, int> >countsVec{}; //create a vector of pairs same as map

			for (int j = 0; j < k; ++j)
			{
				++counts[trainingSetCopy.at(j)->getClass()]; //create needed positions in map
			}
			for (auto elem : counts)
			{
				countsVec.push_back({ elem.first, elem.second });//transfer information to vector
			}

			std::sort(countsVec.begin(), countsVec.end(), //sort vector over quantity
				[&](std::pair<int, int> &l, std::pair<int, int> &r)->bool {
				return l.second > r.second;
			});


			(*i).predictClass(countsVec[0].first);//first in first elem in vector is the one with largest quantity
		}
		else
		{
			std::map<int, int> counts{}; //create a map; first: class, second: quantitity
			std::vector<std::pair<int, int> >countsVec{}; //create a vector of pairs same as map

			float prevDist = (std::numeric_limits<float>::min)();
			for (int kIter = 0; kIter < k; ++kIter)
			{
				float dist = (std::numeric_limits<float>::max)();
				ClassifableObject* obj = trainingSetCopy[0];

				for (int iter = 0; iter < trainingSetCopy.size(); ++iter)
				{
					float tmpDist = metric((*i), *trainingSetCopy.at(iter));
					if (tmpDist < dist && tmpDist > prevDist)
					{
						dist = tmpDist;
						obj = trainingSetCopy.at(iter);
					}
				}
				prevDist = dist;
				++counts[obj->getClass()];
			}

			for (auto elem : counts)
			{
				countsVec.push_back({ elem.first, elem.second });//transfer information to vector
			}

			std::sort(countsVec.begin(), countsVec.end(), //sort vector over quantity
				[&](std::pair<int, int> &l, std::pair<int, int> &r)->bool {
				return l.second > r.second;
			});

			(*i).predictClass(countsVec[0].first);
			//(*i).predictClass(obj->getClass());
		}
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
		obj[i] = (obj[i] - attributeNormalizingValues.at(i).first) / (attributeNormalizingValues.at(i).second - attributeNormalizingValues.at(i).first);
	}
}

void Classifier::classifyPixels(std::vector<Pixel>& pixels) const
{
	FunctionStruct func{};
	int s = sqrt(pixels.size()); //compute height and width (square image)
	int windowSize = 64; //window we look at

	auto startClock = std::chrono::steady_clock::now();

	for (int i = 0; i <= s - windowSize; i = i + 16)
	{
		for (int j = 0; j <= s - windowSize; j = j + 16)
		{		
			std::vector<unsigned char> window{};
			//std::cout << "\n\nWINDOW!!!1\n";
			//create a window
			for (int m = 0; m < windowSize; ++m)
			{
				
				for (int n = 0; n < windowSize; ++n)
				{
					window.push_back(pixels[j + n + (i + m) * (s)].color);
					//std::cout << std::setw(3) << (int)window[window.size() - 1];
				}
				//std::cout << "\n";
			}

			//create classifable object and compute attributes for it
			ClassifableObject obj{ (int)attributesToExtract.size(), -1 };

			for (unsigned int n = 0; n < attributesToExtract.size(); ++n)
			{
				obj[n] = func.extractingFunctions[attributesToExtract.at(n)](window);
			}
			
			normalizeObject(obj);

			//compute knn
			
			//knnForOneObject( definedK, obj);
			MarcinkovskyVroblevskyMethod(obj);
			
			//add pixel predictions
			for (int m = 0; m < windowSize; ++m)
			{
				for (int n = 0; n < windowSize; ++n)
				{
					++pixels[j + n + (i + m) * s].predicitons[obj.PredictedClass()];
				}
			}
		}

		std::cout << (i + 1)*(s - windowSize) << "/" << (s - windowSize)*(s - windowSize) << 
			"["<< std::chrono::duration <double>(std::chrono::steady_clock::now() - startClock).count() <<"ms]\n";

		//Statistics::getInstance().printMistakesMatrix(std::cout);
	}
}

void Classifier::knnForOneObject(const int k, ClassifableObject & testedObj) const
{
	std::map<int, int> counts{}; //create a map; first: class, second: quantitity
	std::vector<std::pair<int, int> >countsVec{}; //create a vector of pairs same as map

	float prevDist = (std::numeric_limits<float>::min)();
	for (int kIter = 0; kIter < k; ++kIter)
	{
		float dist = (std::numeric_limits<float>::max)();
		ClassifableObject* obj = &((*trainingSet)[0]);

		for (int iter = 0; iter < trainingSet->size(); ++iter)
		{
			float tmpDist = metric(testedObj, trainingSet->at(iter));
			if (tmpDist < dist && tmpDist > prevDist)
			{
				dist = tmpDist;
				obj = &(trainingSet->at(iter));
			}
		}
		prevDist = dist;
		++counts[obj->getClass()];
	}

	for (auto elem : counts)
	{
		countsVec.push_back({ elem.first, elem.second });//transfer information to vector
	}

	std::sort(countsVec.begin(), countsVec.end(), //sort vector over quantity
		[&](std::pair<int, int> &l, std::pair<int, int> &r)->bool {
		return l.second > r.second;
	});

	testedObj.PredictedClass() = countsVec[0].first;
	
}

void Classifier::MarcinkovskyVroblevskyMethod(ClassifableObject & obj) const
{
	static std::vector<ClassifableObject> centers;
	
	static std::vector<std::vector<ClassifableObject *> > classesVec;

	if (classesVec.empty())
	{
		centers = std::vector<ClassifableObject>{};
		classesVec = std::vector<std::vector<ClassifableObject *> >{};

		for (int i = 0; i < classes; ++i)
		{
			centers.push_back({ (int)attributesToExtract.size(), i });
		}


		for (int i = 0; i < classes; ++i)
		{
			std::vector<ClassifableObject*> singleClass{};
			classesVec.push_back(singleClass);
		}

		for (int i = 0; i < trainingSet->size(); ++i)
		{
			classesVec[trainingSet->at(i).getClass()].push_back(&(trainingSet->at(i)));
		}

		for (int i = 0; i < classes; ++i)
		{
			for (int j = 0; j < classesVec[i].size(); ++j)
			{
				for (int k = 0; k < attributesToExtract.size(); ++k)
				{
					centers[i][k] += (*(classesVec[i][j]))[k] / classesVec[i].size();
				}				
			}
		}
	}

	std::vector<float> distances(classes, 0.f);
	float minDist = std::numeric_limits<float>::max();
	int at = -1;

	for (int i = 0; i < classes; ++i)
	{
		distances[i] = metric(obj, centers[i]);
		if (distances[i] < minDist)
		{
			minDist = distances[i];
			at = i;
		}
	}

	obj.PredictedClass() = at;
}

void Classifier::normalizeTrainingSet()//normalizes to range 0 - 1
{
	std::vector<std::pair<float, float>> values(attributesToExtract.size(), { (std::numeric_limits<float>::max)(), (std::numeric_limits<float>::min)() });

	for (const auto &item : *trainingSet) //iterate over whole training set
	{
		for (int i = 0; i < attributesToExtract.size(); ++i) //iterate over attributes of each item
		{
			if (values[i].first > item[i]) //if the value of an attribute is greater than the biggest one yet, it becomes new greatest value
			{
				values[i].first = item[i];
			}

			if (values[i].second < item[i])
			{
				values[i].second = item[i];
			}
		}
	}

	for (int i = 0; i < attributeNormalizingValues.size(); ++i) //iterate over attributeNormalizing vector
	{
		attributeNormalizingValues[i].first = values[i].first; //change values at the vector to inverse of max values in the training set
		attributeNormalizingValues[i].second = values[i].second;
	}

	for (auto &item : *trainingSet)//iterate over whole training set again to normalize
	{
		normalizeObject(item);//normalize the object
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

void Pixel::predictClass()
{
	int p = -1;
	int val = -1;

	//std::cout << "[";
	for (int i = 0; i < 4; ++i)
	{
		//std::cout << predicitons[i] << ",";
		if (predicitons[i] > val)
		{
			p = i;
			val = predicitons[i];
		}
		
	}
	//std::cout << "]\n";
	predictedClass = p;
	Statistics::getInstance().classPrediction(properClass, p);
}