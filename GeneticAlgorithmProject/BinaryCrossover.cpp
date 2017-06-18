#include "BinaryCrossover.h"
#include <algorithm>
#include <set>

/* function prototypes */
std::vector<Individual*>* selectElites(std::vector<Individual*>* population, int numberOfElites);
std::vector<Individual*>* produceOffspring(std::vector<Individual*>* population, RandomNumberSupplier* rnd, int crossSize, double crossProb);

std::vector<Individual*>* BinaryCrossover::performCrossover(std::vector<Individual*>* population) {
	std::vector<Individual*>* crossoverPopulation = new std::vector<Individual*>();

	if (this->getNumberOfEliteIndividuals()) {
		crossoverPopulation = selectElites(population, this->getNumberOfEliteIndividuals());
	}

	while (crossoverPopulation->size() < this->getNumberOfIndividualsToGenerate()) {
		std::vector<Individual*>* offsprings = produceOffspring(population, this->rnd, this->getNumberOfIndividualsToCross(), this->getCrossoverProbability());
		for (int i = 0; i < offsprings->size(); i++) {
			crossoverPopulation->push_back(offsprings->at(i));
			if (crossoverPopulation->size() == this->getNumberOfIndividualsToGenerate()) {
				break;
			}
		}
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

std::vector<Individual*>* produceOffspring(std::vector<Individual*>* population, RandomNumberSupplier* rnd, int crossSize, double crossProb) {
	std::vector<Individual*>* selectedForCrossover = new std::vector<Individual*>();
	std::vector<Individual*>* offsprings = new std::vector<Individual*>();

	while (selectedForCrossover->size() < crossSize) {
		int index = rnd->getRandomNumber(population->size());
		Individual* selected = population->at(index);
		if (std::find(selectedForCrossover->begin(), selectedForCrossover->end(), selected) == selectedForCrossover->end()) {
			selectedForCrossover->push_back(selected);
		}
	}

	double cross = rnd->getRandomNumber0to1();
	if (cross < crossProb) {
		std::vector<int>* splitIndexes = new std::vector<int>();
		int maxSplit = population->at(0)->getNumberOfDimensions();
		while (splitIndexes->size() < crossSize - 1) {
			int index = rnd->getRandomNumber(maxSplit);
			if (std::find(splitIndexes->begin(), splitIndexes->end(), index) == splitIndexes->end()) {
				splitIndexes->push_back(index);
			}
		}
		std::sort(splitIndexes->begin(), splitIndexes->end());

		double** values = new double*[crossSize];
		for (int i = 0; i < crossSize; i++) {
			values[i] = new double[maxSplit];
		}

		int offset = 0;
		for (int i = 0; i < maxSplit; i++) {
			if (splitIndexes->size() > offset && i == splitIndexes->at(offset)) {
				offset++;
			}

			for (int j = 0; j < crossSize; j++) {
				values[j][i] = selectedForCrossover->at((j + offset) % crossSize)->getValues()[i];
			}
		}

		for (int i = 0; i < crossSize; i++) {
			offsprings->push_back(new Individual(values[i], maxSplit));
		}

	} else {
		for (int i = 0; i < selectedForCrossover->size(); i++) {
			offsprings->push_back(new Individual(selectedForCrossover->at(i)));
		}
	}

	

	return offsprings;
}
