// RozpoznawanieObrazu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>



int main()
{
	//just a simple example how to read digits from database and display them in terminal
	//you can wrap it if you want to

	std::string MNIST_DATA_LOCATION = "mnist/";				//it will be easier if i just push the files on repo
	std::cout << "MNIST data directory: " << MNIST_DATA_LOCATION << std::endl;

	mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset = 
		mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);

	std::cout << "MNIST LOADED\n";

	//std::cout << "Nbr of training images (train-images-idx3-ubyte) = " << dataset.training_images.size() << std::endl;	//this time we only use this
	//std::cout << "Nbr of training labels (train-labels-idx1-ubyte) = " << dataset.training_labels.size() << std::endl;	//and this
	/*std::cout << "Nbr of test images (t10k-images-idx3-ubyte) = " << dataset.test_images.size() << std::endl;
	std::cout << "Nbr of test labels (t10k-labels-idx1-ubyte) = " << dataset.test_labels.size() << std::endl;*/
	//int k = 0;
	//std::cout << "Which element do you want to see?\n Write number and press ENTER.\n";
	//std::cin >> k;
	//std::cout << "An raw cout is presented below." << std::endl;
	//while (k != -1) {
	//	for (int i = 0; i < 28; i++)				//size of every image is 28
	//	{
	//		for (int j = 0; j < 28; j++)			//by 28
	//		{
	//			//it's needed for proper display digits in terminal (but the dataset is correct)
	//			if ((int)dataset.training_images.at(k).at(i * 28 + j) != 10 &&	//ASCII code for new line (we don't want extra new line in digit!)
	//				(int)dataset.training_images.at(k).at(i * 28 + j) != 13 &&	//ASCII code for carriage return (part of digit is at the beggining of a line!)
	//					(int)dataset.training_images.at(k).at(i * 28 + j) != 9) //ASCII code for horizontal tab (it's just get messy!)
	//			{
	//				std::cout << dataset.training_images.at(k).at(i * 28 + j);		//yep, it is a struct of vectors of vectors, but it works fast
	//				//to get a 0-255 pixel value just cast to int (do we even need it?)
	//			}
	//			else
	//			{
	//				std::cout << (unsigned char)0;			//it's better to display nothing than some ASCII garbage		
	//			}
	//		}									
	//		std::cout << std::endl;
	//	}
	//	std::cout << "There is a " << (int)dataset.training_labels.at(k) << " on selected image." << std::endl;
	//	std::cout << "Which element do you want to see?\n Write number and press ENTER.\n If you want to finish write -1.\n";
	//	std::cin >> k;
	//}

		
	std::vector<ClassifableObject> data{};
	
	if (true)
	{
		int numberOfClasses{ 0 };/*
		Extractor extr{numberOfClasses};*/
		FileSaver sav{ "file.txt" };
		std::vector<std::string> att{};

		/*extr.extractAttributes(dataset.training_images, dataset.training_labels, att);
		sav.saveToFile(extr.getObjects(), att, numberOfClasses);
		std::cout << "SAVED\n";
		
*/
		sav.loadFromFile(data, att, numberOfClasses);

		Classifier classifier{ data, att, numberOfClasses };
		
		classifier.computeTestSet(dataset.test_images, dataset.test_labels);

		classifier.knn(3);
	}
	std::cout << "DONE\n";

	for (int i = 0; i < 100; ++i)
	{
		std::cout << "DATA " << i << ": " << data[i].toFileFormat() << "\n";
	}
	
	system("pause");
	return 0;
}
