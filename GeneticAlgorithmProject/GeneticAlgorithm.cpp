#include "GeneticAlgorithm.h"
#include <algorithm>

#include <iostream>

/* function prototypes */
Individual* selectBestIndividual(std::vector<Individual*>* population);

Individual * GeneticAlgorithm::run(int numberOfGenerations, std::vector<Individual*>* population) {
	for (int i = 0; i < numberOfGenerations; i++) {
		std::cout << "Generation: " << i << "\n";

		std::for_each(population->begin(), population->end(), [&](Individual* ind) {
			double fitness = this->fitnessFunction->function(ind->getValues());
			ind->setFitness(fitness);
		});

		Individual* best = selectBestIndividual(population);
		std::cout << "Best individual: ";
		for (int i = 0; i < best->getNumberOfDimensions(); i++) {
			std::cout << best->getValues()[i] << " ";
		}
		std::cout << "\n";

		std::cout << "Finished calculating fitness" << '\n';

		population = this->selection->select(population);

		std::cout << "Finished selection stage" << '\n';

		population = this->crossover->performCrossover(population);

		std::cout << "Finished crossover stage" << '\n';

		std::for_each(population->begin(), population->end(), [&](Individual* ind) {
			this->mutation->mutate(ind);
		});
		
		std::cout << "Finished mutation stage" << "\n";
	}
	return selectBestIndividual(population);
}

Individual * selectBestIndividual(std::vector<Individual*>* population) {
	double max = -DBL_MAX;
	Individual* best = nullptr;

	for (int i = 0; i < population->size(); i++) {
		Individual* ind = population->at(i);
		if (ind->getFitness() > max) {
			max = ind->getFitness();
			best = ind;
		}
	}
	return best;
}
