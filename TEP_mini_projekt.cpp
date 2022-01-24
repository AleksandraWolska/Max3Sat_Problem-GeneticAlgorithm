// TEP_mini_projekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Max3SatProblem.h"
#include "GAIndividual.h"
#include "GAOptimizer.h"
using namespace std;

int main()
{
    //creating an instance of the problem
    Max3SatProblem problem = Max3SatProblem();
   

    //creating an optimizer with parameters: population size, crossover probability, mutation probability, and a problem instance
    GAOptimizer* optimizer = new GAOptimizer(problem, 20, 30, 10 );

    if (optimizer->initialize("C:\\Users\\Aleksandra\\source\\repos\\TEP_mini_projekt\\wsadowe\\50\\m3s_50_0.txt")) {
 
        cout << "\nPopulacja przed: " << std::endl;
        optimizer->printCurrentPopulation();
        optimizer->printBestIndividual();


        cout << "\n\nIteracja trwa........: " << std::endl;
        optimizer->runIteration();
      

        cout << "Populacja po 1 iteracji: " << std::endl;
        optimizer->printCurrentPopulation();
        optimizer->printBestIndividual();
        cout << "\n\n";


        cout << "Populacja po 2 iteracji: " << std::endl;
        optimizer->runIteration();
        optimizer->printCurrentPopulation();
        optimizer->printBestIndividual();
        cout << endl;



        for (int i = 0; i < 10000; i++)
        {
            cout << endl;
            optimizer->runIteration();
            optimizer->printBestIndividual();
        }
    }
    else {
        cout << "Nie udalo sie wczytac pliku. Zakonczenie programu";
    }
    delete optimizer;
    
    
   

}

