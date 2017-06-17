#include "catch.hpp"

#include "RouletteSelection.h"
#include <set>

class TestRandomNumberSupplier : public RandomNumberSupplier {

public:

	TestRandomNumberSupplier() {}
	~TestRandomNumberSupplier() {}

	int getRandomNumber() { return 0; }
	int getRandomNumber(int limit) { return 0; }
	double getRandomNumber0to1() {
		return 0.018;
	}
};

TEST_CASE("Roulette selection basic functionality test") {

	RandomNumberSupplier* rnd = new TestRandomNumberSupplier();
	Selection* selection = new RouletteSelection(5, rnd);

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

		for (int i = 1; i <= 5; i++) {
			REQUIRE(fitnessValues->count(i) != 0);
		}

		for (int i = 6; i <= 10; i++) {
			REQUIRE(fitnessValues->count(i) == 0);
		}
	}
}