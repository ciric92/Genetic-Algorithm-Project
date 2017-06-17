#include "catch.hpp"
#include "TournamentSelection.h"
#include "RandomNumberSupplier.h"

class TournamentTestRandomNumberSupplier : public RandomNumberSupplier {
	bool flag;
public:

	TournamentTestRandomNumberSupplier() { flag = false; }
	int getRandomNumber() { return 0; }
	double getRandomNumber0to1() { return 0; }
	int getRandomNumber(int limit) { flag = !flag;  return flag ? 1 : 0; }
};

TEST_CASE(" Tournament Selection basic functionality test ") {

	RandomNumberSupplier* rnd = new TournamentTestRandomNumberSupplier();
	Selection* selection = new TournamentSelection(5, 2, rnd);

	/* initialize test population */
	std::vector<Individual*>* population = new std::vector<Individual*>();
	double *values = new double[5];
	values[0] = 0; values[1] = 1; values[2] = 2; values[3] = 3; values[4] = 4;

	for (int i = 0; i < 10; i++) {
		Individual* ind = new Individual(values, 5);
		ind->setFitness(i + 1);
		population->push_back(ind);
	}

	population = selection->select(population);

	SECTION("test population size") {
		REQUIRE(population->size() == 5);
	}

	SECTION("test selected fitness values") {
		std::set<double>* fitnessValues = new std::set<double>();

		std::for_each(population->begin(), population->end(), [&](Individual* ind) {
			fitnessValues->insert(ind->getFitness());
		});

		REQUIRE(fitnessValues->count(1) == 0);

		for (int i = 2; i <= 6; i++) {
			REQUIRE(fitnessValues->count(i) != 0);
		}

		for (int i = 7; i <= 10; i++) {
			REQUIRE(fitnessValues->count(i) == 0);
		}
	}
}