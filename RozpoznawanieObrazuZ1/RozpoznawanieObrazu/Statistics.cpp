#include "stdafx.h"
#include "Statistics.h"
#include <sstream>
#include <iomanip>
#include <iostream>

Statistics::~Statistics()
{
}

void Statistics::classPrediction(int proper, int prediction)
{
	//if (proper >= 0 && prediction >= 0)
	//{
	//std::cout << proper<<", "<<prediction<<"\n";
		++mistakesMatrix[proper][prediction];
	//}
		
	
	
}

void Statistics::createMistakesMatrix(int numberOfAttributesPerObject)
{
	this->numberOfAttributesPerObject = numberOfAttributesPerObject;

	mistakesMatrix = std::vector<std::vector<int> >{};

	for (int i = 0; i < numberOfAttributesPerObject; ++i)
	{
		mistakesMatrix.push_back(std::vector<int>(numberOfAttributesPerObject, 0));
	}
}

std::ostream& Statistics::printMistakesMatrix(std::ostream &s) const
{
	int setwSize = 7;
	float wholeSuccess = 0.f;

	s << color(FOREGROUND_BLUE | BACKGROUND_GREEN) << 
		std::setw(setwSize) << ""<<"\\ ";

	for (int i = 0; i < mistakesMatrix.size(); ++i)
	{
		s << std::setw(setwSize) << i << "|";
	}
	s << "\n";

	for (int i = 0; i < mistakesMatrix.size(); ++i)
	{
		s << color(FOREGROUND_BLUE | BACKGROUND_GREEN)<< 
			std::setw(setwSize) << i << ". " << white;

		int properCount{ 0 };
		int wholeCount{ 0 };

		for (int j = 0; j < mistakesMatrix.size(); ++j)
		{
			if (j == i)
			{
				properCount = mistakesMatrix[i][j];
				s << color(FOREGROUND_BLUE | BACKGROUND_GREEN);
			}
			wholeCount += mistakesMatrix[i][j];
			s << std::setw(setwSize) << mistakesMatrix[i][j] << white << "|";
		}
		float single = (float)properCount / (float)wholeCount;
		wholeSuccess += single;

		s << "success ratio: " << single << "\n";
	}

	s << "Success: " << (wholeSuccess / mistakesMatrix.size()) << "\n\n";
	
	return s;
}

