#include "TournamentSelection.h"
#include <set>

/* function prototypes */
std::vector<Individual*>* selectParticipants(std::vector<Individual*>* population, int tournamentSize, RandomNumberSupplier* rnd);
Individual* selectWinner(std::vector<Individual*>* participants);
void removeWinner(std::vector<Individual*>* population, Individual* winner);

std::vector<Individual*>* TournamentSelection::select(std::vector<Individual*>* population) {
	std::vector<Individual*>* selected = new std::vector<Individual*>();

	for (int i = 0; i < this->n; i++) {
		
		std::vector<Individual*>* participants = selectParticipants(population, this->tournamentSize, this->rnd);

		Individual* winner = selectWinner(participants);

		selected->push_back(winner);
		removeWinner(population, winner);
	}

	return selected;
}

std::vector<Individual*>* selectParticipants(std::vector<Individual*>* population, int tournamentSize, RandomNumberSupplier* rnd) {
	std::vector<Individual*>* participants = new std::vector<Individual*>();
	std::set<int>* selected = new std::set<int>();

	while (selected->size() < tournamentSize) {
		int index = rnd->getRandomNumber(population->size());
		if (selected->count(index) == 0) {
			selected->insert(index);
			participants->push_back(population->at(index));
		}
	}

	return participants;
}

Individual* selectWinner(std::vector<Individual*>* participants) {
	double maxFitness = -DBL_MAX;
	Individual* winner = nullptr;
	for (int i = 0; i < participants->size(); i++) {
		Individual* current = participants->at(i);
		if (current->getFitness() > maxFitness) {
			maxFitness = current->getFitness();
			winner = current;
		}
	}
	return winner;
}

void removeWinner(std::vector<Individual*>* population, Individual * winner) {
	for (int i = 0; i < population->size(); i++) {
		if (population->at(i) == winner) {
			population->erase(population->begin() + i);
			return;
		}
	}
}
