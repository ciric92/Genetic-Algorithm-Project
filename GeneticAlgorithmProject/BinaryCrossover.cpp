#include "BinaryCrossover.h"
#include <algorithm>
#include <set>

/* function prototypes */
std::vector<Individual*>* selectElites(std::vector<Individual*>* population, int numberOfElites);
Individual* produceOffspring(std::vector<Individual*>* population, RandomNumberSupplier* rnd, int crossSize);

std::vector<Individual*>* BinaryCrossover::performCrossover(std::vector<Individual*>* population) {
	std::vector<Individual*>* crossoverPopulation = new std::vector<Individual*>();

	if (this->getNumberOfEliteIndividuals()) {
		crossoverPopulation = selectElites(population, this->getNumberOfEliteIndividuals());
	}

	while (crossoverPopulation->size() < this->getNumberOfIndividualsToGenerate()) {
		crossoverPopulation->push_back(produceOffspring(population, this->rnd, this->getNumberOfIndividualsToCross()));
	}

	return crossoverPopulation;
}

std::vector<Individual*>* selectElites(std::vector<Individual*>* population, int numberOfElites) {
	std::vector<Individual*>* elites = new std::vector<Individual*>();
	if (numberOfElites) {
		sort(population->begin(), population->end(), [](Individual* lhs, Individual* rhs) {
			return lhs->getFitness() > rhs->getFitness();
		});

		for (int i = 0; i < numberOfElites; i++) {
			elites->push_back(population->at(i));
		}
	}
	return elites;
}

Individual* produceOffspring(std::vector<Individual*>* population, RandomNumberSupplier* rnd, int crossSize) {
	std::set<Individual*>* selected = new std::set<Individual*>();
	std::set<int>* splitIndexes = new std::set<int>();

	int maxSplit = population->at(0)->getNumberOfDimensions();

	while (selected->size() < crossSize) {
		int num = rnd->getRandomNumber(population->size());
		Individual* select = population->at(num);
		if (selected->count(select) == 0) {
			selected->insert(select);
		}
	}

	while (splitIndexes->size() < crossSize - 1) {
		int num = rnd->getRandomNumber(maxSplit);
		if (splitIndexes->count(num) == 0) {
			splitIndexes->insert(num);
		}
	}

	double* values = new double[maxSplit];
	std::set<int>::iterator sIt = splitIndexes->begin();
	std::set<Individual*>::iterator iIt = selected->begin();
	for (int i = 0; i < maxSplit; i++) {
		if (sIt != splitIndexes->end() && i == *sIt) {
			sIt++;
			iIt++;
		}
		values[i] = (*iIt)->getValues()[i];
	}

	return new Individual(values, maxSplit);
}
