#pragma once
#include <vector>
#include <string>
#include <map>
#include "lodepng.h"
#include <iostream>


class StarReader
{
public:
	StarReader(const std::string & trainingLocation, const std::string & testLocation);
	~StarReader();


	/*adds data from folder to the given vectors*/
	void addDataToSetFromFile(dataVector& data, std::vector<unsigned char>& labels, const std::string& filesLocation);

	std::vector<unsigned char> testLabels;
	std::vector<unsigned char> trainingLabels;
	dataVector testSet;
	dataVector trainingSet;
	/*map used to map string characters to unsigned char*/
	std::map<std::string, unsigned char> labelsMap;


private:
	std::vector<std::string> getAllFilesNamesWithinFolder(const std::string & folder) const;
	std::vector<unsigned char> getDataVectorFromPngFile(const std::string & filename) const;
};

