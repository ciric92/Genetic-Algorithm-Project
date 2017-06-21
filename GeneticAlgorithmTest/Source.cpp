#include "catch.hpp"
#include "GeneticAlgorithm.h"
#include "TournamentSelection.h"
#include "ContinuousCrossover.h"
#include "Mutation.h"
#include "FitnessFunction.h"
#include "DefaultRandomNumberSupplier.h"
#include "InitialPopulationGenerator.h"
#include <cmath>
#include <iostream>

class DropWaveFunctionFitness : public FitnessFunction {

public:

	double function(std::vector<double> values) {
		double x1 = values[0];
		double x2 = values[1];

		return (1 + std::cos(12 * std::sqrt(x1 * x1 + x2 * x2))) / (0.5 * (x1 * x1 + x2 * x2) + 2);
	}
};

class GriewankFunction : public FitnessFunction {

public:
	double function(std::vector<double> values) {
		double squareSum = 0;
		double cosProd = 1;
		for (int i = 0; i < values.size(); i++) {
			squareSum += values[i] * values[i] / 4000;
			cosProd *= std::cos(values[i] / std::sqrt(i + 1));
		}

		return -squareSum + cosProd - 1;
	}
};

TEST_CASE("Testing gentic algorithm with Drop Wave function") {
	RandomNumberSupplier* rnd = new DefaultRandomNumberSupplier();
	InitialPopulationGenerator* initGen = new InitialPopulationGenerator(rnd);
	GeneticAlgorithm* alg = new GeneticAlgorithm(
		new TournamentSelection(25, 2, rnd),
		new ContinuousCrossover(50, 0.9, 0.5, rnd, 10),
		new Mutation(0.015, -5.12, 5.12, rnd),
		new DropWaveFunctionFitness()
	);

	Individual* winner = alg->run(200, initGen->generate(50, 2, -5.12, 5.12));

	//std::cout << winner->getValues[0] << " " << winner->getValues[1] << " " << -winner->getFitness;

	SECTION("Testing with expecteds") {
		REQUIRE(winner->getFitness() - 1 < DBL_EPSILON);
		REQUIRE(std::abs(winner->getValues()[0]) < 0.001);
		REQUIRE(std::abs(winner->getValues()[1]) < 0.001);
	}
}

TEST_CASE("Griewank function") {
	RandomNumberSupplier* rnd = new DefaultRandomNumberSupplier();
	InitialPopulationGenerator* initGen = new InitialPopulationGenerator(rnd);
	GeneticAlgorithm* alg = new GeneticAlgorithm(
		new TournamentSelection(150, 2, rnd),
		new ContinuousCrossover(500, 0.9, 0.5, rnd, 10),
		new Mutation(0.015, -600, 600, rnd),
		new GriewankFunction()
	);

	Individual* winner = alg->run(1000, initGen->generate(500, 10, -600, 600));

	//std::cout << winner->getValues[0] << " " << winner->getValues[1] << " " << -winner->getFitness;

	SECTION("Testing with expecteds") {
		REQUIRE(winner->getFitness() < 0.001);
		REQUIRE(std::abs(winner->getValues()[0]) < 1);
		REQUIRE(std::abs(winner->getValues()[1]) < 1);
		REQUIRE(std::abs(winner->getValues()[2]) < 1);
		REQUIRE(std::abs(winner->getValues()[3]) < 1);
		REQUIRE(std::abs(winner->getValues()[4]) < 1);
		REQUIRE(std::abs(winner->getValues()[5]) < 1);
		REQUIRE(std::abs(winner->getValues()[6]) < 1);
		REQUIRE(std::abs(winner->getValues()[7]) < 1);
		REQUIRE(std::abs(winner->getValues()[8]) < 1);
		REQUIRE(std::abs(winner->getValues()[9]) < 1);

	}
}