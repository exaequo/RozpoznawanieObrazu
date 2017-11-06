#pragma once
#include <vector>

/*Singleton to calculate all the data of the classification*/
class Statistics
{
public:
	Statistics(int numberOfAttributesPerObject);
	~Statistics();


private:
	/*Number of attributes of each object*/
	int numOfAtt;

	/*Number of proper classification of each of the classes*/
	int* properClassificationPerClassNumber;


};

