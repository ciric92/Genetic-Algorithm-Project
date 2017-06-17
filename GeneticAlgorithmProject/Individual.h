#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <vector>

class Individual {

	std::vector<double> values;
	double fitness;

public:

	Individual(double* values, int d);

	Individual() { };

	Individual(const std::vector<double> values) : values(values) { };

	unsigned int getNumberOfDimensions() { return values.size(); }

	std::vector<double> getValues() { return values; }

	double getFitness() { return fitness; }

	void setFitness(double fitness) { this->fitness = fitness; }

	~Individual() { }
};


#endif // !__INDIVIDUAL_H__

