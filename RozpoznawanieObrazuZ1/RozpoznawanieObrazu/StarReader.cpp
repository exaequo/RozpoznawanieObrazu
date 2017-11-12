#include "stdafx.h"
#include "StarReader.h"
#include <filesystem>
#include <fstream>
#include <string>
#define cimg_use_png
#include "CImg.h"


namespace fs = std::experimental::filesystem;


StarReader::StarReader(const std::string & trainingLocation, const std::string & testLocation)
{
	addDataToSetFromFile(trainingSet, trainingLabels, trainingLocation); // we create the training set
	addDataToSetFromFile(testSet, testLabels, testLocation); // we create the test set
}

StarReader::~StarReader()
{
}


void StarReader::addDataToSetFromFile(dataVector & data, std::vector<unsigned char>& labels, const std::string & filesLocation)
{
	std::vector<std::string> stringLabels{};//needed to extract string labels

	for (auto & p : fs::recursive_directory_iterator(filesLocation))
	{
		auto lines = FileSaver::divideLine(p.path().filename().string(), '_');

		if (lines.size() > 1) //if lines size would be 1 it means that we are looking at a directory not a png file
		{
			stringLabels.push_back(lines[0]);
			//std::cout << lines[0];
			++labelsMap[lines[0]]; //we add an entry to the labelsMap that we'll later use to fill proper labels vector

			data.push_back(getDataVectorFromPngFile(p.path().string())); //we get the data vector for the given values
		}
	}

	int iter{ 0 };
	for (auto p = labelsMap.begin(); p != labelsMap.end(); ++p)
	{
		(*p).second = (unsigned char)(iter++);

		//std::cout << (*p).first << " -> " << (int)(*p).second << "\n";
	}


	for (int i = 0; i < stringLabels.size(); ++i) //we fill the labels with mapped values from string labels
	{
		labels.push_back(labelsMap[stringLabels[i]]);
	}
}

std::vector<std::string> StarReader::getAllFilesNamesWithinFolder(const std::string & folder) const
{
	//std::vector<std::string> result{};
	//for (auto & p : fs::recursive_directory_iterator(folder))
	//{
	//	result.push_back(p.path().filename().string());
	//	
	//}
	//return result;
}

std::vector<unsigned char> StarReader::getDataVectorFromPngFile(const std::string & filename) const
{
	std::vector<unsigned char> result{};

	cimg_library::CImg<unsigned char> src(filename.c_str());
	
	for (int i = 0; i < src.height(); ++i)
	{
		for (int j = 0; j < src.width(); j++)
		{
			result.push_back(*src.data(j, i, 0, 0));
		}
	}
	
	return result;
}
