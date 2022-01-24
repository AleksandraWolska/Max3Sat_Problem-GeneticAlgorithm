#pragma once
#include "Clause.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

const int PROBLEM_SIZE = 50;
const int CLAUSES_AMOUNT = 213;

class Max3SatProblem {
private:
public:

	Max3SatProblem() {}
	~Max3SatProblem() {}

	vector<Clause*> load(string filename, vector<Clause*>clauses);
	int compute(bool* pGenotype, vector<Clause*>& clauses);
};

