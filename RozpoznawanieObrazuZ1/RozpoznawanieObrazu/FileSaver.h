#pragma once
#include <vector>
#include <string>
#include <sstream>

class FileSaver
{
public:
	FileSaver(std::string fileName);
	~FileSaver();
	/*Saves vector of classifableObjectData to file given by the fileName in constructor*/
	bool saveToFile(const std::vector<class ClassifableObject> &data, const std::vector<std::string> & attributesToSave) const;
	
	/*Loads the data from file into given vectors*/
	bool loadFromFile(std::vector<class ClassifableObject> &data, std::vector<std::string> & attributesToUse) const;

	static std::vector<std::string> divideLine(const std::string &str, const char divider);
private:
	std::string fileName;
	
};

