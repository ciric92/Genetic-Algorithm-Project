#include "DecimationSelection.h"
#include <algorithm>

using namespace std;

std::vector<Individual*>* DecimationSelection::select(vector<Individual*>* population) {
	sort(population->begin(), population->end(), [](Individual* lhs, Individual* rhs) {
		return lhs->getFitness() > rhs->getFitness();
	});
	population->resize(n);
	return population;
}