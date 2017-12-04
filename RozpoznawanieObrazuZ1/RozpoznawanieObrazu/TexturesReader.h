#pragma once
class TexturesReader
{
public:
	TexturesReader(const std::string & trainingLocation , const std::string & testLocation);
	~TexturesReader();

	/*adds data from folder to the given vectors*/
	void addDataToSetFromFile(dataVector& data, std::vector<unsigned char>& labels, const std::string& filesLocation);

	void addDataToTestSetFromFile(dataVector& data, dataVector& labels, const std::string& filesLocation);

	//std::vector<unsigned char> testLabels;
	std::vector<unsigned char> trainingLabels;
	dataVector testSet;
	dataVector trainingSet;
	dataVector testLabels;
	/*map used to map string characters to unsigned char*/
	std::map<std::string, unsigned char> labelsMap;

	static int mapColorToClass(unsigned char color);

private:
	std::vector<std::string> getAllFilesNamesWithinFolder(const std::string & folder) const;
	std::vector<unsigned char> getDataVectorFromPngFile(const std::string & filename) const;
};

