#include <stdlib.h>
#include <cstdio>
#include <iostream>

#include "GeneticAlgorithm.h"


int main() {

	std::vector<Individual*> pop;
	double *values = new double[5];
	values[0] = 0; values[1] = 1; values[2] = 2; values[3] = 3; values[4] = 4;

	for (int i = 0; i < 10; i++) {
		Individual* ind = new Individual(values, 5);
		ind->setFitness(i);
		pop.push_back(ind);
	}

	Selection* selection = new DecimationSelection(5);

	selection->select(&pop);

	for (int i = 0; i < pop.size(); i++) {
		std::cout << pop.at(i)->getFitness() << " ";
	}

	return 0;
}