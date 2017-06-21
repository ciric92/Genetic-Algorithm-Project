#include "ContinuousCrossover.h"

#include <algorithm>
#include <set>

/* function prototypes */
std::vector<Individual*>* selectElites1(std::vector<Individual*>* population, int numberOfElites);
std::vector<Individual*>* produceOffspring(std::vector<Individual*>* population, RandomNumberSupplier* rnd, double crossProb, double a);

std::vector<Individual*>* ContinuousCrossover::performCrossover(std::vector<Individual*>* population) {
	std::vector<Individual*>* crossoverPopulation = new std::vector<Individual*>();

	if (this->getNumberOfEliteIndividuals()) {
		crossoverPopulation = selectElites1(population, this->getNumberOfEliteIndividuals());
	}

	while (crossoverPopulation->size() < this->getNumberOfIndividualsToGenerate()) {
		std::vector<Individual*>* offsprings = produceOffspring(population, this->rnd, this->getCrossoverProbability(), this->alpha);
		for (int i = 0; i < offsprings->size(); i++) {
			crossoverPopulation->push_back(offsprings->at(i));
			if (crossoverPopulation->size() == this->getNumberOfIndividualsToGenerate()) {
				break;
			}
		}
	}

	return crossoverPopulation;
}

std::vector<Individual*>* selectElites1(std::vector<Individual*>* population, int numberOfElites) {
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

std::vector<Individual*>* produceOffspring(std::vector<Individual*>* population, RandomNumberSupplier* rnd, double crossProb, double a) {
	std::vector<Individual*>* selectedForCrossover = new std::vector<Individual*>();
	std::vector<Individual*>* offsprings = new std::vector<Individual*>();

	while (selectedForCrossover->size() < 2) {
		int index = rnd->getRandomNumber(population->size());
		Individual* selected = population->at(index);
		if (std::find(selectedForCrossover->begin(), selectedForCrossover->end(), selected) == selectedForCrossover->end()) {
			selectedForCrossover->push_back(selected);
		}
	}

	int valueCount = population->at(0)->getNumberOfDimensions();
	double cross = rnd->getRandomNumber0to1();
	if (cross < crossProb) {
		double* values1 = new double[valueCount];
		double* values2 = new double[valueCount];

		for (int i = 0; i < valueCount; i++) {
			values1[i] = selectedForCrossover->at(1)->getValues()[i] + a * (selectedForCrossover->at(0)->getValues()[i] - selectedForCrossover->at(1)->getValues()[i]);
			values2[i] = selectedForCrossover->at(1)->getValues()[i] - a * (selectedForCrossover->at(0)->getValues()[i] - selectedForCrossover->at(1)->getValues()[i]);
		}

		offsprings->push_back(new Individual(values1, valueCount));
		offsprings->push_back(new Individual(values2, valueCount));
	} else {
		for (int i = 0; i < selectedForCrossover->size(); i++) {
			offsprings->push_back(new Individual(selectedForCrossover->at(i)));
		}
	}



	return offsprings;
}

