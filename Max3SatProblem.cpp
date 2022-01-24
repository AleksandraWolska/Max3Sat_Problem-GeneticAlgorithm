#include "Max3SatProblem.h"
#include <string>
using namespace std;


vector<Clause*> Max3SatProblem::load(string filename, vector<Clause*>clauses) {

	fstream stream;
	stream.open(filename, fstream::in);

	if (stream.is_open()) {
		cout << " stream otwarty ";
		string temp1, temp2, temp3;
		char bracket;

		while (stream.good()) {

			stream >> bracket;

			if (bracket != '(') {
				stream.setstate(ios::failbit);
			}
			stream >> temp1;			//zmienna w pliku >> zmiwnna gdzie mamy zapisac
			stream >> temp2;
			stream >> temp3;

			clauses.push_back(new Clause(stoi(temp1), stoi(temp2), stoi(temp3)));

			stream >> bracket;

			if (bracket != ')') {
				stream.setstate(ios::failbit);
			}

		}
	}
	stream.close();
	return clauses;
}



int Max3SatProblem::compute(bool* individualGenotype, vector<Clause*>& clauses) {
	int score = 0;

	for (int i = 0; i < CLAUSES_AMOUNT; i++) {

		int clause_1 = clauses.at(i)->getVal1();					//get first number in first clause

		if (clause_1 >= 0 && individualGenotype[clause_1]) {						//it is positive and individual has true gene on this index
			score++;
			continue;
		}
		else if (clause_1 < 0 && !individualGenotype[abs(clause_1)]) {				//it is negative and individual is false gene on this index
			score++;
			continue;
		}

		int clause_2 = clauses.at(i)->getVal2();

		if (clause_2 >= 0 && individualGenotype[clause_2]) {
			score++;
			continue;
		}
		else if (clause_2 < 0 && !individualGenotype[abs(clause_2)]) {
			score++;
			continue;
		}

		int clause_3 = clauses.at(i)->getVal3();

		if (clause_3 >= 0 && individualGenotype[clause_3])
			score++;
		else if (clause_3 < 0 && !individualGenotype[abs(clause_3)]) {

			score++;
		}
	}

	return score;
	}
