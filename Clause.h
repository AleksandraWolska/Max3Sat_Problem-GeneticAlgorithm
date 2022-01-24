#pragma once
#include <string>
using namespace std;


class Clause
{
private:
	int val1;
	int val2;
	int val3;

public:
	Clause(int x, int y, int z);
	Clause();
	~Clause();

	int getVal1();
	int getVal2();
	int getVal3();

	void setVal1(bool newVal);
	void setVal2(bool newVal);
	void setVal3(bool newVal);

	void printClause();
};

