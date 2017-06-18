#include "catch.hpp"
#include "BinaryCrossover.h"
#include "RandomNumberSupplier.h"

class BinaryCrossoverTestRNS : public RandomNumberSupplier {

	bool flag;
public:
	BinaryCrossoverTestRNS() : flag(false) {}

	~BinaryCrossoverTestRNS() {}

	int getRandomNumber() { return 0; }

	double getRandomNumber0to1() { return 0.5; }

	int getRandomNumber(int limit) {
		if (limit == 6) {
			return 3;
		} else {
			flag = !flag;
			return flag ? 4 : 3;
		}
	}
};

TEST_CASE(" Binary crossover basic functionaliy test ") {

	std::vector<Individual*>* population = new std::vector<Individual*>();

	double* values1 = new double[6];
	values1[0] = 0; values1[1] = 1; values1[2] = 2; values1[3] = 3; values1[4] = 4; values1[5] = 5;

	double* values2 = new double[6];
	values2[0] = 10; values2[1] = 9; values2[2] = 8; values2[3] = 7; values2[4] = 6; values2[5] = 5;

	for (int i = 0; i < 4; i++) {
		Individual* newInd = new Individual(values1, 6);
		newInd->setFitness(i);
		population->push_back(newInd);
	}
	Individual* newInd = new Individual(values2, 6);
	newInd->setFitness(4);
	population->push_back(newInd);

	Crossover* cross = new BinaryCrossover(5, 2, 0.6, new BinaryCrossoverTestRNS(), 4);

	std::vector<Individual*>* newGeneration = cross->performCrossover(population);

	SECTION(" test elitsim (save 4) ") {
		for (int i = 0; i < 4; i++) {
			REQUIRE(newGeneration->at(i) == population->at(i));
		}
	}

	SECTION(" test crossover (produces only one because of the population size) ") {
		Individual* offspring = newGeneration->at(4);
		REQUIRE(offspring->getFitness() - DBL_MIN < DBL_EPSILON);

		REQUIRE(offspring->getValues()[0] - 10 < DBL_EPSILON);
		REQUIRE(offspring->getValues()[1] - 9 < DBL_EPSILON);
		REQUIRE(offspring->getValues()[2] - 8 < DBL_EPSILON);
		REQUIRE(offspring->getValues()[3] - 7 < DBL_EPSILON);
		REQUIRE(offspring->getValues()[4] - 4 < DBL_EPSILON);
		REQUIRE(offspring->getValues()[5] - 5 < DBL_EPSILON);
	}
}