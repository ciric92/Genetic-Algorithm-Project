#include "Individual.h"

using namespace std;

Individual::Individual(double* values, int d) {
	this->values.resize(d);
	for (int i = 0; i < d; i++) {
		this->values.at(i) = values[i];
	}
	this->setFitness(DBL_MIN);
}
