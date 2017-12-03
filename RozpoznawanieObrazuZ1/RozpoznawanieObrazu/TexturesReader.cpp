#include "stdafx.h"
#include "TexturesReader.h"
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::experimental::filesystem;

TexturesReader::TexturesReader(const std::string & trainingLocation)//, const std::string & testLocation)
{
	addDataToSetFromFile(trainingSet, trainingLabels, trainingLocation); // we create the training set
	//addDataToSetFromFile(testSet, testLabels, testLocation); // we create the test set
}


TexturesReader::~TexturesReader()
{
}

void TexturesReader::addDataToSetFromFile(dataVector & data, std::vector<unsigned char>& labels, const std::string & filesLocation)
{
	std::vector<std::string> stringLabels{};//needed to extract string labels

	for (auto & p : fs::recursive_directory_iterator(filesLocation))
	{
		std::string line = p.path().filename().string().substr(0, p.path().filename().string().size() - 7);
		auto dot = FileSaver::divideLine(p.path().filename().string(), '.');

		if (dot.size() == 2) //if lines size would be 1 it means that we are looking at a directory not a png file
		{
			stringLabels.push_back(line);
			//std::cout << lines[0];
			++labelsMap[line]; //we add an entry to the labelsMap that we'll later use to fill proper labels vector
			std::string filename = p.path().string();
			std::replace(filename.begin(), filename.end(), '\\', '/');
			data.push_back(getDataVectorFromPngFile(filename)); //we get the data vector for the given values
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

std::vector<std::string> TexturesReader::getAllFilesNamesWithinFolder(const std::string & folder) const
{
	std::vector<std::string> result{};
	for (auto & p : fs::recursive_directory_iterator(folder))
	{
		result.push_back(p.path().filename().string());
	}
	return result;
}

std::vector<unsigned char> TexturesReader::getDataVectorFromPngFile(const std::string & filename) const
{
	using namespace cv;

	std::vector<unsigned char> result{};
	//std::cout << filename << std::endl;
	Mat src = imread(filename, 1);
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			result.push_back(src.at<Vec3b>(y, x)[0]);
		}
	}

	return result;
}