#ifndef __MUTATION_H__
#define __MUTATION_H__

#include "Individual.h"
#include "RandomNumberSupplier.h"

class Mutation {

	/* probability of mutation */
	double mutationProb;

	/* allowed mutation */
	double min;
	double max;

	RandomNumberSupplier* rnd;

public:
	Mutation(double mutationProb, double min, double max, RandomNumberSupplier* rnd) : mutationProb(mutationProb), min(min), max(max), rnd(rnd) {}

	virtual ~Mutation() {};

	virtual void mutate(Individual* ind) {
		std::vector<double> values = ind->getValues();
		for (int i = 0; i < ind->getNumberOfDimensions(); i++) {
			if (shouldMutate()) {
				values[i] = min + rnd->getRandomNumber0to1() * (max - min);
			}
		}
		ind->setValues(values);
	}

protected:

	bool shouldMutate() {
		return rnd->getRandomNumber0to1() < mutationProb;
	}
};

#endif // !__MUTATION_H__

