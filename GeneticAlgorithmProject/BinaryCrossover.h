#ifndef __BINARY_CROSSOVER_H__
#define __BINARY_CROSSOVER_H__

#include "Crossover.h"
#include "RandomNumberSupplier.h"

class BinaryCrossover : public Crossover {

	RandomNumberSupplier* rnd;

public:

	BinaryCrossover(int n, int m, double crossProbability, RandomNumberSupplier* rnd, int eliteCount = 0) : Crossover(n, m, crossProbability, eliteCount), rnd(rnd) {}

	~BinaryCrossover() {}

	std::vector<Individual*>* performCrossover(std::vector<Individual*>* population);
};
#endif // !__BINARY_CROSSOVER_H__
