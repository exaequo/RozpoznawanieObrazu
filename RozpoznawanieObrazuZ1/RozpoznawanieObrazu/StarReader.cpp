#include "stdafx.h"
#include "StarReader.h"
#include <filesystem>
#include <fstream>
#include <string>



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
		auto dot = FileSaver::divideLine(p.path().filename().string(), '.');

		if (dot.size() == 2) //if lines size would be 1 it means that we are looking at a directory not a png file
		{
			stringLabels.push_back(lines[0]);
			//std::cout << lines[0];
			++labelsMap[lines[0]]; //we add an entry to the labelsMap that we'll later use to fill proper labels vector
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

using namespace cv;

std::vector<unsigned char> StarReader::getDataVectorFromPngFile(const std::string & filename) const
{
	std::vector<unsigned char> result{};

	Mat src = imread(filename, 1);
	
	Mat dst = src.clone();
	int MAX_KERNEL_LENGTH = 7;
	GaussianBlur(src, dst, Size(MAX_KERNEL_LENGTH, MAX_KERNEL_LENGTH), 3, 3);
	MAX_KERNEL_LENGTH = 17;
	bilateralFilter(dst, src, MAX_KERNEL_LENGTH, MAX_KERNEL_LENGTH * 2, MAX_KERNEL_LENGTH / 2);

	Mat samples(src.rows * src.cols, 3, CV_32F);
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			for (int z = 0; z < 3; z++)
				samples.at<float>(y + x * src.rows, z) = src.at<Vec3b>(y, x)[z];


	int clusterCount = 2;
	Mat labels;
	int attempts = 2;
	Mat centers;
	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

	float avg = { 0.0f };

	for (int y = 0; y < dst.rows; y++)
	{
		for (int x = 0; x < dst.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x * dst.rows, 0);
			avg += centers.at<float>(cluster_idx, 0);
			//result.push_back(centers.at<float>(cluster_idx, 0));
			src.at<Vec3b>(y, x)[0] = centers.at<float>(cluster_idx, 0);
			src.at<Vec3b>(y, x)[1] = centers.at<float>(cluster_idx, 1);
			src.at<Vec3b>(y, x)[2] = centers.at<float>(cluster_idx, 2);
		}
	}

	avg /= (src.rows * src.cols);

	threshold(src, dst, avg, 255, THRESH_BINARY);

	//imshow("test", dst);
	//waitKey(0);

	for (int y = 0; y < dst.rows; y++)
	{
		for (int x = 0; x < dst.cols; x++)
		{
			result.push_back(dst.at<Vec3b>(y, x)[0]);
		}
	}

	//std::vector<unsigned char> image; //the raw pixels
	//unsigned width, height;

	//decode
	//std::cout << "filename: " << filename << std::endl;
	//unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	//if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA

	//we only need first of this RGBA sequence so i+=4
	//for (int i = 0; i < image.size(); i += 4)
	//{
	//	result.push_back(image.at(i));
	//}

	return result;
}