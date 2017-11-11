#pragma once
#include <vector>
#include <string>

/*Singleton to calculate all the data of the classification*/
class Statistics
{
public:
	static Statistics& getInstance() //still do not understand how this works but it does
	{
		static Statistics instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
	
	Statistics(Statistics const&) = delete;
	void operator=(Statistics const&) = delete;

	~Statistics();
	/*updates an entry in mistakesMatrix*/
	void classPrediction(int proper, int prediction);

	/*creates proper mistakes matrix*/
	void createMistakesMatrix(int);


	std::ostream& printMistakesMatrix(std::ostream &s) const;

private:
	Statistics() {}


	/*Number of attributes of each object*/
	int numberOfAttributesPerObject;

	std::vector<std::vector<int> > mistakesMatrix;
};

