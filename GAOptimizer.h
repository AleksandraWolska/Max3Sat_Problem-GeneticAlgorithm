#pragma once
#include <vector>
#include "Max3SatProblem.h"
#include "GAIndividual.h"
using namespace std;

const int TOURNAMENT_GROUP_SIZE = 5;


class GAOptimizer {

private:
	int populationSize;
	int crossoverProbability;
	int mutationProbability;


	vector<GAIndividual*> pPopulation;
	vector<Clause*> clauses;
	Max3SatProblem problem;

public:
	
	GAOptimizer(Max3SatProblem problem, int populationSize, int crossoverProbability, int mutationProbability);
	~GAOptimizer();
	bool initialize(string fileName);

	void runIteration();
	GAIndividual* selectParentByTournament(vector<GAIndividual*> givenPopulation);

	void printCurrentPopulation();
	void printBestIndividual();

};

