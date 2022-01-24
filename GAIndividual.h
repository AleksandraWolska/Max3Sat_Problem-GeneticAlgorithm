#pragma once
using namespace std;
#include "Max3SatProblem.h"
#include <iostream>
class GAIndividual
{

private:
	bool* pGenotype;
	int fitness = 0;

public:

	GAIndividual();
	GAIndividual(bool value);
	GAIndividual(bool* pNewGenotype);
	GAIndividual(const GAIndividual& other);
	~GAIndividual();

	int getFitness(vector<Clause*> clauses, Max3SatProblem problem);
	bool** makeCrossover(GAIndividual& other);
	void makeMutation(int probability);

	bool* getGenotype();
	void printGenotype();
};

