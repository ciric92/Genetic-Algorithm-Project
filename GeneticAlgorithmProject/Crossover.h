#ifndef __CROSSOVER_H__
#define __CROSSOVER_H__

#include "Individual.h"
#include <vector>

class Crossover {
	/* number of individuals to generate */
	int n; 

	/* number of inidividuals to cross */
	int m;

	/* number of elites */
	int eliteCount;

public:

	Crossover(int n, int m, int eliteCount = 0) : n(n), m(m), eliteCount(eliteCount) {}

	virtual ~Crossover() {}

	virtual std::vector<Individual*>* performCrossover(std::vector<Individual*>* population) = 0;

	int getNumberOfIndividualsToGenerate() { return n; }

	int getNumberOfIndividualsToCross() { return m; }

	int getNumberOfEliteIndividuals() { return eliteCount; }
};

#endif // !__CROSSOVER_H__

