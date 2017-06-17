#include "catch.hpp"

#include "DecimationSelection.h"
#include <set>


TEST_CASE("Decimation selection basic functionality test") {

	Selection* selection = new DecimationSelection(5);

	/* initialize test population */
	std::vector<Individual*>* population = new std::vector<Individual*>();
	double *values = new double[5];
	values[0] = 0; values[1] = 1; values[2] = 2; values[3] = 3; values[4] = 4;

	for (int i = 0; i < 10; i++) {
		Individual* ind = new Individual(values, 5);
		ind->setFitness(i);
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

		for (int i = 0; i < 5; i++) {
			REQUIRE(fitnessValues->count(i) == 0);
		}
		for (int i = 5; i < 10; i++) {
			REQUIRE(fitnessValues->count(i) != 0);
		}
	}
}
