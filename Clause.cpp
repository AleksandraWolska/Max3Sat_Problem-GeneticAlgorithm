#include "Clause.h"
#include <string>
#include <iostream>
using namespace std;

Clause::Clause() {
	val1 = 0;
	val2 = 0;
	val3 = 0;
}


Clause::Clause(int v1, int v2, int v3) {
	val1 = v1;
	val2 = v2;
	val3 = v3;
}

Clause::~Clause() {
}


void Clause::printClause() {
	cout << "<" << val1 << ", " << val2 << ", " << val3 << ">\n";
}


//getters and setters

int Clause::getVal1() {
	return val1;
}

int Clause::getVal2(){
	return val2;
}

int Clause::getVal3(){
	return val3;
}

void Clause::setVal1(bool newVal){
	val1 = newVal;
}

void Clause::setVal2(bool newVal){
	val2 = newVal;
}

void Clause::setVal3(bool newVal){
	val3 = newVal;
}


