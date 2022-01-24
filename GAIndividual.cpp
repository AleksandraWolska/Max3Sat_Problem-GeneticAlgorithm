#include "GAIndividual.h"
#include "Max3SatProblem.h"
#include <ctime>
#include <random>
#include <vector>
using namespace std;

GAIndividual::GAIndividual() {
	pGenotype = NULL;
}



GAIndividual::GAIndividual(bool value) {
	pGenotype = new bool[PROBLEM_SIZE];

	for (int i = 0; i < PROBLEM_SIZE; i++) {
		pGenotype[i] = value;
	}
}



GAIndividual::GAIndividual(bool* newGen) {
	if (pGenotype != NULL) {
		delete[] pGenotype;
	}
	pGenotype = newGen;
}



GAIndividual::GAIndividual(const GAIndividual& other) {				//konstruktor kopiuj¹cy
	if (pGenotype != NULL) {
		delete[] pGenotype;
	}
	bool* newGenotype = new bool[PROBLEM_SIZE];

	for (int i = 0; i < PROBLEM_SIZE; i++) {						//przepisujê genotyp
		newGenotype[i] = other.pGenotype[i];
	}
	pGenotype = newGenotype;
}

GAIndividual::~GAIndividual() {
	delete[] pGenotype;
}




bool** GAIndividual::makeCrossover(GAIndividual& other) {		//krzy¿owanie od indeksu
	srand(time(0));		

	int indexOfCrossing;
	bool** result = new bool* [2];							//dwuwymiarowa tablica o dwóch rzêdach

	result[0] = new bool[PROBLEM_SIZE];					//zadeklarowanie iloœci kolumn na 50
	result[1] = new bool[PROBLEM_SIZE];					//zadeklarowanie iloœci kolumn na 50

	indexOfCrossing = (rand() % 50);	

	for (int i = 0; i < PROBLEM_SIZE; i++) {

		if (i < indexOfCrossing) {							//jesli gen ma nizszy indeks od indeksu krzy¿owania, to nie krzyuj
			result[0][i] = pGenotype[i];
			result[1][i] = other.pGenotype[i];
		} else {
			result[0][i] = other.pGenotype[i];			//jesli gen ma wyzszy/rowny indeks od indeksu krzy¿owania, to krzyuj
			result[1][i] = pGenotype[i];
		}
	 }
	return result;
}

//
//bool** GAIndividual::makeCrossover(GAIndividual& other) {			//krzyzowanie jednostajne
//	srand(time(0));
//
//	int randomIndex;
//	bool** result = new bool* [2];							//dwuwymiarowa tablica o dwóch rzêdach
//
//	result[0] = new bool[PROBLEM_SIZE];					//zadeklarowanie iloœci kolumn na 50
//	result[1] = new bool[PROBLEM_SIZE];					//zadeklarowanie iloœci kolumn na 50
//
//
//	for (int i = 0; i < PROBLEM_SIZE; i++) {
//		randomIndex = (rand() % 2);						//generowanie 0 i 1
//
//		if (randomIndex == 0) {							//jeœli 0, to nie krzy¿uj
//			result[0][i] = pGenotype[i];
//			result[1][i] = other.pGenotype[i];
//		}
//		else {
//			result[0][i] = other.pGenotype[i];			//jeœli 1 to krzy¿uj
//			result[1][i] = pGenotype[i];
//
//		}
//	}
//	return result;
//}



void GAIndividual::makeMutation(int probability) {
	srand(time(0));
	int random;

	for (int i = 0; i < PROBLEM_SIZE; i++) {
		random = (rand() % 100 + 1);

		if (random < probability) {
			pGenotype[i] = !pGenotype[i];
		}
	}
}

void GAIndividual::printGenotype() {
	for (int i = 0; i < PROBLEM_SIZE; i++) {
		cout <<  (pGenotype[i] == 1 ? 1 : 0);
	}
	std::cout << std::endl;
}


int GAIndividual::getFitness(vector<Clause*> clauses, Max3SatProblem problem ) {
	return problem.compute(pGenotype, clauses);
}

bool* GAIndividual::getGenotype(){
	return pGenotype;
}




