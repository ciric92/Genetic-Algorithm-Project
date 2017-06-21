#include "catch.hpp"
#include "Mutation.h"
#include "RandomNumberSupplier.h"

class MutationTestRNS : public RandomNumberSupplier {
public:
	int getRandomNumber() { return 0; }

	int getRandomNumber(int limit) { return 0; }

	double getRandomNumber0to1() { return 0.5; }
};

TEST_CASE("Mutation basic functionality test case") {
	Mutation* mutation = new Mutation(0.6, -1, 1, new MutationTestRNS());

	double values[1] = { 2 };
	Individual* ind = new Individual(values, 1);

	SECTION("mutation should happen") {
		mutation->mutate(ind);

		REQUIRE(ind->getValues()[0] < DBL_EPSILON);
	}
}