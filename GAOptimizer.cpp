#include "GAOptimizer.h"


GAOptimizer::GAOptimizer(Max3SatProblem _problem, int _populationSize, int _crossoverProbability, int _mutationProbability ) {
	problem = _problem;
	populationSize = _populationSize;
	crossoverProbability = _crossoverProbability;
	mutationProbability = _mutationProbability;
}
 
GAOptimizer::~GAOptimizer() {
	for (int i = 0; i < pPopulation.size(); i++) {
		delete pPopulation[i];
	}

	if (!clauses.empty()) {
		for (int i = 0; i < CLAUSES_AMOUNT; i++) {
			delete clauses[i];
		}
	}

	pPopulation.clear();
	clauses.clear();
}




bool GAOptimizer::initialize(string filename) {
	srand(time(NULL));

	clauses = problem.load(filename, clauses);				//fills the clause vector with values given in the file

	for (int i = 0; i < populationSize; i++) {
		bool* pNewGenotype = new bool[PROBLEM_SIZE];				//for each 

		for (int j = 0; j < PROBLEM_SIZE; j++) {
			int random = std::rand() % 2;
			pNewGenotype[j] = random;
		}
		pPopulation.push_back(new GAIndividual(pNewGenotype));
	}
	return clauses.empty() ? false : true;
}





void GAOptimizer::runIteration() {
	//srand(time(NULL));

	std::vector<GAIndividual*> newPopulation;

	GAIndividual* parent1 = nullptr;
	GAIndividual* parent2 = nullptr;
	GAIndividual* child1 = nullptr;
	GAIndividual* child2 = nullptr;

	while (newPopulation.size() < pPopulation.size()) {			//while new population is smaller than current
		
		parent1 = selectParentByTournament(pPopulation);				//selecting parents by tournament selection
		parent2 = selectParentByTournament(pPopulation);
	
		while (parent2 == parent1) {
			parent2 = selectParentByTournament(pPopulation);
		}
		srand(time(NULL));

		int random = (rand() % 100 + 1);					//random number from 0-100

		
		if (random < crossoverProbability) {					//if random fits the probability then crossing occurs 
			bool** children = parent1->makeCrossover(*parent2);	//function returns 2D table, each row corresponding to one child's genotype

			child1 = new GAIndividual(children[0]);
			child2 = new GAIndividual(children[1]);

			children[0] = NULL;									
			children[1] = NULL;
			delete[] children;
			children = NULL;


		} else {

			child1 = new GAIndividual(*parent1);				//if individuals don't cross, parents are selected to be in new population vecto
			child2 = new GAIndividual(*parent2);
		}
		child1->makeMutation(mutationProbability);				//mutation
		child2->makeMutation(mutationProbability);

		newPopulation.push_back(child1);
		newPopulation.push_back(child2);
	}

	for (int i = 0; i < populationSize; i++) {					//delete current population
		delete pPopulation[i];
	}
	pPopulation = newPopulation;								//replace current population with new one
	
}




GAIndividual* GAOptimizer::selectParentByTournament(vector<GAIndividual*> givenPopulation)
{
	
	bool* candidatesForTournament = new bool[populationSize];			//draw individuals to compete in tournament
	for (int j = 0; j < populationSize; j++)
		candidatesForTournament[j] = false;

	std::vector<GAIndividual*> qualifiedForTournament;
	int i = 0;
	GAIndividual* candidate;

	while (i < TOURNAMENT_GROUP_SIZE) {									//look for individual that qualifies to tournament
		int index = std::rand() % populationSize;

		if (!candidatesForTournament[index]) {							//check if the individual already takes place in tournament
			candidate = givenPopulation.at(index);
			candidatesForTournament[index] = true;
			qualifiedForTournament.push_back(candidate);
			i++;
		}
	}
	
	GAIndividual* temporaryWinner = qualifiedForTournament[0];					
	int bestScoreSoFar = temporaryWinner->getFitness(clauses, problem);

	for (int j = 1; j < TOURNAMENT_GROUP_SIZE; j++) {					//get winner within members of a tournament
		int participantScore = qualifiedForTournament.at(j)->getFitness(clauses, problem);
		
		if (participantScore > bestScoreSoFar) {
			bestScoreSoFar = participantScore;
			temporaryWinner = qualifiedForTournament.at(j);
		}
	}

	delete[] candidatesForTournament;									//take care of memory leakage
	qualifiedForTournament.clear();
	candidate = NULL;

	return temporaryWinner;
}



void GAOptimizer::printBestIndividual() {

	int bestScoredSoFar = pPopulation[0]->getFitness(clauses, problem);
	int candidate = bestScoredSoFar;
	bool* bestGenotypeSoFar = pPopulation[0]->getGenotype();

	for (int i = 1; i < populationSize; i++) {
		candidate = pPopulation[i]->getFitness(clauses, problem);
		if (candidate > bestScoredSoFar) {
			bestGenotypeSoFar = pPopulation[i]->getGenotype();
			bestScoredSoFar = candidate;
		}
	}
	std::cout << "Best fitness: " << candidate << " for individual with genotype: ";
	for (int i = 0; i < PROBLEM_SIZE; i++) {
		std::cout << bestGenotypeSoFar[i] ? 1 : 0;
	}
	bestGenotypeSoFar = NULL;
}



void GAOptimizer::printCurrentPopulation() {
	for (int i = 0; i < populationSize; i++) {

		if ((pPopulation.at(i)->getGenotype()) != nullptr) {
			pPopulation.at(i)->printGenotype();
		}
		else {
			cout << "Individual not found";
		}
	}
}