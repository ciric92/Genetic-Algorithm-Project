#include "RouletteSelection.h"
#include <algorithm>

/* function prototypes */
double fitnessSum(std::vector<Individual*>* population);
std::vector<double>* assignProbabilities(std::vector<Individual*>* population);
Individual* rouletteSelect(std::vector<Individual*>* population, RandomNumberSupplier* rnd);
void removeSelected(std::vector<Individual*>* population, Individual* selected);


std::vector<Individual*>* RouletteSelection::select(std::vector<Individual*>* population) {
	std::vector<Individual*>* selectedPopulation = new std::vector<Individual*>();

	for (int i = 0; i < this->n; i++) {
		Individual* selected = rouletteSelect(population, this->rnd);
		selectedPopulation->push_back(selected);
		removeSelected(population, selected);
	}
	
	return selectedPopulation;
}

Individual* rouletteSelect(std::vector<Individual*>* population, RandomNumberSupplier* rnd) {
	std::vector<double>* probabilities = assignProbabilities(population);

	double select = rnd->getRandomNumber0to1();

	for (unsigned int i = 0; i < population->size(); i++) {
		if (select < probabilities->at(i)) {
			return population->at(i);
		}		
	}

	return population->at(population->size() - 1);
}

std::vector<double>* assignProbabilities(std::vector<Individual*>* population) {
	std::vector<double>* probabilities = new std::vector<double>();

	double fSum = fitnessSum(population);
	double prevProb = 0; // initial probability

	std::for_each(population->begin(), population->end(), [&](Individual* i) {
		prevProb += i->getFitness() / fSum;
		probabilities->push_back(prevProb);
	});

	

	return probabilities;
}

double fitnessSum(std::vector<Individual*>* population) {
	double sum = 0;

	std::for_each(population->begin(), population->end(), [&](Individual*& i) {
		sum += i->getFitness();
	});

	return sum;
}

void removeSelected(std::vector<Individual*>* population, Individual* winner) {
	for (int i = 0; i < population->size(); i++) {
		if (population->at(i) == winner) {
			population->erase(population->begin() + i);
			return;
		}
	}
}


