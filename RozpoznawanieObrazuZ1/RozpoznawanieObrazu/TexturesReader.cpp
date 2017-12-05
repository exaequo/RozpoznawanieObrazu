#include "stdafx.h"
#include "TexturesReader.h"
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::experimental::filesystem;

TexturesReader::TexturesReader(const std::string & trainingLocation, const std::string & testLocation)
{
	addDataToSetFromFile(trainingSet, trainingLabels, trainingLocation); // we create the training set
	addDataToTestSetFromFile(testSet, testLabels, testLocation); // we create the test set
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
			data.push_back(getDataVectorFromPngFile(filename,true)); //we get the data vector for the given values
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

void TexturesReader::addDataToTestSetFromFile(dataVector & data, dataVector & labels, const std::string & filesLocation)
{
	std::vector<std::string> stringLabels{};//needed to extract string labels

	for (auto & p : fs::recursive_directory_iterator(filesLocation))
	{
		std::string line = p.path().filename().string().substr(0, p.path().filename().string().size() - 7);
		auto dot = FileSaver::divideLine(p.path().filename().string(), '.');

		if (dot.size() == 2) //if lines size would be 1 it means that we are looking at a directory not a png file
		{
			std::string filename = p.path().string();
			std::replace(filename.begin(), filename.end(), '\\', '/');

			//std::cout << filename << "\n";
			auto v = FileSaver::divideLine(filename, '/');
			std::string sName = v[v.size() - 1];

			if (sName[0] == 'l')
			{
				//std::cout << "Adding label\n";
				labels.push_back(getDataVectorFromPngFile(filename, false)); //we get the data vector for the given values
			}
			else
			{
				//std::cout << "Adding data\n";
				data.push_back(getDataVectorFromPngFile(filename, true)); //we get the data vector for the given values
			}
		}
	}
}

int TexturesReader::mapColorToClass(unsigned char color)
{
	switch ((int)color)//len (224), sól (160), s³oma (96) i drewno (32))
	{
	case 224:
	case 227:
		return 0;
	case 160:
	case 163:
		return 1;
	case 96:
	case 99:
		return 2;
	case 32:
		return 3;
	}
	return -1;
}

unsigned char TexturesReader::mapClassToColor(int classNum)
{
	switch (classNum)
	{
	case 0:
		return 224;
	case 1:
		return 160;
	case 2: 
		return 96;
	case 3:
		return 32;
	}
	return 0;
}

void TexturesReader::displayImage(const std::vector<unsigned char>& imag)
{
	using namespace cv;
	Mat src = imread("textures/texture-test/label1.bmp", 1);
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			unsigned char t = imag.at(y * src.rows + x);
			src.at<Vec3b>(y, x)[0] = t;
			src.at<Vec3b>(y, x)[1] = t;
			src.at<Vec3b>(y, x)[2] = t;
		}
	}

	imwrite(std::to_string(rand()%10000) + ".bmp", src);
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

std::vector<unsigned char> TexturesReader::getDataVectorFromPngFile(const std::string & filename, bool shouldNormalize) const
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
	/*auto path = FileSaver::divideLine(filename, '\\');
	std::cout << filename <<"\n";*/
	if (shouldNormalize)
	{
		normalizePicture(result);
	}
	
	return result;
}


