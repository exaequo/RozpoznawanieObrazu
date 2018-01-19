// RozpoznawanieObrazu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>

void printSuccess(Classifier& classifier, bool val = true)
{
	if (val)
	{
		int count = 0;
		for (auto& test : classifier.getTestSet())
		{
			//std::cout << test.toOutputFormat() << std::endl;
			count += test.getSuccessIdentifier();
		}
		std::cout << "\n\nSuccess rate: " << ((float)count / classifier.getTestSet().size()) << "\n";
	}
	Statistics::getInstance().printMistakesMatrix(std::cout);
}

int isGreen(cv::Scalar s) {

	using namespace cv;
	Mat rgb(1, 1, CV_8UC3, s);
	Mat hsv;
	cvtColor(rgb, hsv, COLOR_BGR2HSV);
	Scalar hsvS = hsv.at<cv::Vec3b>(0, 0);
	//std::cout << "S: " << s << std::endl;
	//std::cout <<  hsvS << std::endl;
	int backgroundDetector = 20;
	if (hsvS.val[1] < 40 && hsvS.val[2] > 150) {
		//std::cout << "GRAY!" << std::endl;
		return -1;
	}
	if (s.val[1] > 100) {
		//std::cout << "GREEN!" << std::endl;
	}
	else {
		//std::cout << "BLACK" << std::endl;
	}
	return s.val[1] > 100 ? 1 : 0;
}

std::vector<int> countGrapes(const std::string& file) {

	int lightGrapes = 0;
	int darkGrapes = 0;

	std::cout << "countGrapes method - Hi! Let's count some grapes!" << std::endl;
	using namespace cv;
	using namespace std;

	std::cout << "Loading image " << file << std::endl;
	Mat src = imread(file, 1);
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);
	medianBlur(src_gray, src_gray, 5);
	vector<Vec3f> circles;
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 2, 35, 100, 40, 20, 50);
	std::cout << circles.size() << std::endl;

	for (int i = 0; i < circles.size(); ++i)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		Mat1b mask(src.rows, src.cols, uchar(0));
		circle(mask, center, radius, Scalar(255), -1);
		Scalar average = mean(src, mask);

		if (isGreen(average) == 1) {
			Scalar colorForLightGrapes = Scalar(0, 0, 255);
			//colorForLightGrapes = average;
			circle(src, center, 3, colorForLightGrapes, -1, 8, 0);		//draw circle center
			circle(src, center, radius, colorForLightGrapes, 3, 8, 0);	//draw circle outline
			lightGrapes++;
		}
		else if (isGreen(average) == 0) {
			Scalar colorForDarkGrapes = Scalar(0, 255, 0);
			//colorForDarkGrapes = average;
			circle(src, center, 3, colorForDarkGrapes, -1, 8, 0);		//draw circle center
			circle(src, center, radius, colorForDarkGrapes, 3, 8, 0);	//draw circle outline
			darkGrapes++;
		}
	}
	std::cout << "There are " << lightGrapes << " light grapes on image" << std::endl;
	std::cout << "There are " << darkGrapes << " dark grapes on image" << std::endl;
	namedWindow("Window", WINDOW_AUTOSIZE);
	imshow("Window", src);
	waitKey(0);

	return { lightGrapes, darkGrapes };
}

void countAllObjectsFrom(const std::string& fpath, std::vector<int>(*countingFunction)(const std::string&))
{
	namespace fs = std::experimental::filesystem;
	
	for (auto & p : fs::recursive_directory_iterator(fpath))
	{
		auto dot = FileSaver::divideLine(p.path().filename().string(), '.');

		if (dot.size() == 2) //if lines size would be 1 it means that we are looking at a directory not a file
		{
			auto counts = FileSaver::divideLine(dot[0], '_');

			countingFunction(p.path().string());
		}
	}
}

int main()
{
	std::cout << "Zadanie 3 - Welcome!" << std::endl;
	//countGrapes();
	countAllObjectsFrom("grapes/", &countGrapes);
	system("pause");
	return 0;


	std::cout << "1. EXTRACTOR:\n";
	std::cout << "2. CLASIFFIER:\n\n";
	char option;
	std::cin >> option;

	if (option == '1')
	{
		std::vector<std::string> att;
		std::vector<ClassifableObject> data{};
		Extractor extr{};

		char choice = -1;
		std::string filename{};

		std::cout << "EXTRACTOR:\n\n ";
		std::cout << "Choose:\n" <<
			"(1) MNIST\n" <<
			"(2) STAR\n" <<
			"(3) TEXTURES\n";
		
		while (choice != '1' && choice != '2' && choice != '3')
		{
			choice = std::cin.get();	
		}
		std::cin.get();
		std::cout << "\nfilename:\n";
		std::cin >> filename;

		std::cout << "\nCHOSEN_FILENAME: " << filename << "\n";

		auto startClock = std::chrono::steady_clock::now();
		FileSaver sav{ filename };

		if (choice == '1')	// MNIST
		{
			std::cout << "MNIST PROCESSING...\n";
			att = FunctionStruct::getDefaultAttributesList();

			std::string MNIST_DATA_LOCATION = "mnist/";				
			std::cout << "MNIST data directory: " << MNIST_DATA_LOCATION << std::endl;

			mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset =
				mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);

			std::cout << "MNIST LOADED\n";


			extr.extractAttributes(dataset.training_images, dataset.training_labels, att);
			sav.saveToFile(extr.getObjects(), att);

		}
		else if (choice == '2')				//STAR
		{
			std::cout << "STAR PROCESSING...\n";
			att = FunctionStruct::getStarAttributeList();

			StarReader starDataset{ "STaR_database/train", "STaR_database/test" };

			std::cout << "DONE STAR PROCESSING\n";

			extr.extractAttributes(starDataset.trainingSet, starDataset.trainingLabels, att);
			sav.saveToFile(extr.getObjects(), att);

		}
		else if (choice == '3')		//TEXTURES
		{
			std::cout << "TEXTURES PROCESSING...\n";
			att = FunctionStruct::getTexturesAttributeList();

			TexturesReader texturesDataset{ "textures/texture-train", "textures/texture-test" }; //TODO: texture-test

			std::cout << "DONE TEXTURES PROCESSING\n";
			std::cout << "EXTRACTING ATTRIBUTES\n";
			extr.extractAttributes(texturesDataset.trainingSet, texturesDataset.trainingLabels, att);
			std::cout << "DONE EXTRACTING ATTRIBUTES\n";
			sav.saveToFile(extr.getObjects(), att);
		}
		auto endClock = std::chrono::steady_clock::now();
		std::cout << "SAVED to "<<filename<<" in ["<< std::chrono::duration <double, std::milli>(endClock - startClock).count() <<"ms]\n";
	}
	else 
	{
		std::vector<std::string> att;
		std::vector<ClassifableObject> data{};
		Extractor extr{};

		char choice = -1;
		int k = 1;
		std::string filename{};

		std::cout << "CLASSIFIER:\n\n ";
		std::cout << "Choose:\n" <<
			"(1) MNIST\n" <<
			"(2) STAR\n" <<
			"(3) TEXTURES\n";

		while (choice != '1' && choice != '2' && choice != '3')
		{
			choice = std::cin.get();
		}
		std::cout << "\nk: ";
		std::cin >> k;
		std::cout << "\nChosen k: " << k << " \n";

		std::cin.get();
		std::cout << "\nfilename:\n";
		std::cin >> filename;

		std::cout << "\nCHOSEN_FILENAME: " << filename << "\n";

		auto startClock = std::chrono::steady_clock::now();
		FileSaver sav{ filename };

		sav.loadFromFile(data, att);

		if (choice == '1')	// MNIST
		{
			Classifier classifier{ data, att, 10 };
			std::cout << "MNIST PROCESSING...\n";
			att = FunctionStruct::getDefaultAttributesList();

			std::string MNIST_DATA_LOCATION = "mnist/";
			std::cout << "MNIST data directory: " << MNIST_DATA_LOCATION << std::endl;

			mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset =
				mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);

			std::cout << "MNIST LOADED\n";

			int size = dataset.test_images.size();

			dataVector imag = dataVector{ dataset.test_images.begin(), dataset.test_images.begin() + size };
			std::vector<unsigned char> lab{ dataset.test_labels.begin(), dataset.test_labels.begin() + size };
			classifier.computeTestSet(imag, lab);


			classifier.knn(k, 32);

			printSuccess(classifier);
		}
		else if (choice == '2')				//STAR
		{
			std::cout << "STAR DATASET PROCESSING...\n";
			att = FunctionStruct::getStarAttributeList();

			StarReader starDataset{ "STaR_database/train", "STaR_database/test" };

			std::cout << "DONE STAR PROCESSING\n";

			sav.loadFromFile(data, att);

			int size = starDataset.testSet.size();

			Classifier classifier{ data, att, 10 };
			dataVector imag = dataVector{ starDataset.testSet.begin(), starDataset.testSet.begin() + size };
			std::vector<unsigned char> lab{ starDataset.testLabels.begin(), starDataset.testLabels.begin() + size };
			classifier.computeTestSet(imag, lab);

			classifier.knn(k, 32);

			printSuccess(classifier);
		}
		else if (choice == '3')
		{
			std::cout << "TEXTURES DATASET PROCESSING...\n";
			att = FunctionStruct::getTexturesAttributeList();

			TexturesReader texturesDataset{ "textures/texture-train", "textures/texture-test" };

			std::cout << "DONE TEXTURES PROCESSING\n";

			sav.loadFromFile(data, att);

			int size = texturesDataset.testSet.size();

			Classifier classifier{ data, att, 4 };
			dataVector imag{ texturesDataset.testSet.begin(), texturesDataset.testSet.begin() + size };
			dataVector lab{ texturesDataset.testLabels.begin(), texturesDataset.testLabels.begin() + size };
			
			std::cout << "STARTING CLASSIFIER PROCESSING\n";
			classifier.computeTestSet(imag, lab, k);

			//classifier.knn(k, 32);

			//printSuccess(classifier, false);
		}

		auto endClock = std::chrono::steady_clock::now();
		std::cout << "SAVED to " << filename << " in [" << std::chrono::duration <double, std::milli>(endClock - startClock).count() << "ms]\n";
		
	}
	system("pause");
	return 0;
}
