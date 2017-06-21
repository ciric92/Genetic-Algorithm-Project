#ifndef __INITIAL_POPULATION_GENERATOR_H__
#define __INITIAL_POPULATION_GENERATOR_H__

#include "RandomNumberSupplier.h"
#include "Individual.h"

class InitialPopulationGenerator {

	RandomNumberSupplier* rnd;
public:

	InitialPopulationGenerator(RandomNumberSupplier* rnd) : rnd(rnd) {}

	virtual ~InitialPopulationGenerator() {};

	virtual std::vector<Individual*>* generate(int populationSize, int numberOfGenes, double min, double max) {
		std::vector<Individual*>* population = new std::vector<Individual*>();
		for (int i = 0; i < populationSize; i++) {
			population->push_back(generateSingleIndividual(numberOfGenes, min, max));
		}
		return population;
	}

	virtual Individual* generateSingleIndividual(int numberOfGenes, double min, double max) {
		double* values = new double[numberOfGenes];
		for (int i = 0; i < numberOfGenes; i++) {
			values[i] = getRandomGeneValue(min, max);
		}
		return new Individual(values, numberOfGenes);
	}

private:

	double getRandomGeneValue(double min, double max) {
		return min + rnd->getRandomNumber0to1() * (max - min);
	}
};

#endif // !__INITIAL_POPULATION_GENERATOR_H__

