#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include "Individual.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"
#include "FitnessFunction.h"
#include <vector>

class GeneticAlgorithm {

	Selection* selection;
	Crossover* crossover;
	Mutation* mutation;
	FitnessFunction* fitnessFunction;

public:

	GeneticAlgorithm(Selection* selection, Crossover* crossover, Mutation* mutation, FitnessFunction* fitnessFunction) :
		selection(selection),
		crossover(crossover),
		mutation(mutation),
		fitnessFunction(fitnessFunction) {}

	~GeneticAlgorithm() {}

	Individual* run(int numberOfGenerations, std::vector<Individual*>* population);
	
};

#endif // !__GENETIC_ALGORITHM_H__
