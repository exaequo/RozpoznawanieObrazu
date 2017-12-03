// RozpoznawanieObrazu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>

void printSuccess(Classifier& classifier)
{
	int count = 0;
	for (auto& test : classifier.getTestSet())
	{
		//std::cout << test.toOutputFormat() << std::endl;
		count += test.getSuccessIdentifier();
	}
	std::cout << "\n\nSuccess rate: " << ((float)count / classifier.getTestSet().size()) << "\n";

	Statistics::getInstance().printMistakesMatrix(std::cout);
}

int main()
{
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

			TexturesReader texturesDataset{ "textures/texture-train", "textures/testonly" }; //TODO: texture-test

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

			TexturesReader texturesDataset{ "textures/texture-train", "textures/testonly" };

			std::cout << "DONE TEXTURES PROCESSING\n";

			sav.loadFromFile(data, att);

			int size = texturesDataset.testSet.size();

			Classifier classifier{ data, att, 4 };
			dataVector imag = dataVector{ texturesDataset.testSet.begin(), texturesDataset.testSet.begin() + size };
			std::vector<unsigned char> lab{ texturesDataset.testLabels.begin(), texturesDataset.testLabels.begin() + size };
			classifier.computeTestSet(imag, lab);

			classifier.knn(k, 32);

			printSuccess(classifier);
		}

		auto endClock = std::chrono::steady_clock::now();
		std::cout << "SAVED to " << filename << " in [" << std::chrono::duration <double, std::milli>(endClock - startClock).count() << "ms]\n";


		system("pause");
		return 0;
	}
}
