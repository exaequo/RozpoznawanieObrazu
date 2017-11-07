#include "stdafx.h"
#include "FileSaver.h"
#include <sstream>
#include <iostream>
#include <iomanip>

FileSaver::FileSaver(std::string fileName) : fileName{fileName}
{
}

FileSaver::~FileSaver()
{
}

bool FileSaver::saveToFile(const std::vector<ClassifableObject>& data, const std::vector<std::string>& attributesToSave, int numberOfClasses) const
{
	std::ofstream iFile{ fileName }; //we open selected file

	if (iFile.is_open())
	{
		
		iFile.clear();		//if opened, then clear the contents
		
		iFile << numberOfClasses << "\n";
		for (int i = 0; i < attributesToSave.size(); ++i)//save the header
		{
			iFile << attributesToSave.at(i);
			if (i != attributesToSave.size() - 1) { iFile << ","; }
		}
		iFile << "\n";

		//save the data
		for (const ClassifableObject& obj : data)
		{
			//if size of attribute vector in obj is not equal to the given attributes vector, then there is an error
			if (obj.size() != attributesToSave.size()) 
			{
				iFile.close();
				throw new std::exception("Wrong number of attributes in object");
			}
			
			iFile << obj.toFileFormat() << "\n";
		}
		
		
		iFile.close();//close the file
		return true;
	}
	return false;
}

bool FileSaver::loadFromFile(std::vector<ClassifableObject>& data, std::vector<std::string>& attributesToUse, int& numberOfClasses) const
{
	std::ifstream iFile{ fileName }; // open selected file
	
	if (iFile.is_open())
	{
		std::string line; //string line
		data.clear(); //clear the given vectors
		attributesToUse.clear();

		//get number of classes 
		getline(iFile, line);
		numberOfClasses = std::stoi(line);

		//get attribute names from first line
		getline(iFile, line);
		attributesToUse = divideLine(line, ',');

		while (!iFile.eof())//iterate over whole file
		{
			getline(iFile, line);//gets next line in the file

			std::vector<std::string> att = FileSaver::divideLine(line, ','); 
			if (att.size() > 1) //check if not empty line
			{
				data.push_back({ att });//add new ClassifableObject to data
			}
		}

		iFile.close();
		return true;
	}
	return false;
}

std::vector<std::string> FileSaver::divideLine(const std::string & str, const char divider)
{
	std::vector<std::string> result{};
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, divider))
	{
		result.push_back(token);
	}
	return result;
}
