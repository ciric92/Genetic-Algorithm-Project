#ifndef __CONTINUOUS_CROSSOVER_H__
#define __CONTINUOUS_CROSSOVER_H__

#include "Crossover.h"
#include "RandomNumberSupplier.h"

class ContinuousCrossover : public Crossover {

	RandomNumberSupplier* rnd;

	/* combination factor */
	double alpha;

public:

	ContinuousCrossover(int n, double crossoverProbability, double combinationFactor, RandomNumberSupplier* rnd, int eliteCount = 0) :
		Crossover(n, 2, crossoverProbability, eliteCount),
		rnd(rnd),
		alpha(combinationFactor) {}

	~ContinuousCrossover() {};

	std::vector<Individual*>* performCrossover(std::vector<Individual*>* population);

};

#endif // !__CONTINUOUS_CROSSOVER_H__
