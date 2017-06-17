#ifndef __DECIMATION_SELECTION_H__
#define __DECIMATION_SELECTION_H__

#include "Selection.h"

class DecimationSelection : public Selection {

public:

	DecimationSelection(int n) : Selection(n) {}

	~DecimationSelection() {}

	std::vector<Individual*>* select(std::vector<Individual*>* population);

	int getBestSubsetLength() { return n; }

	void setSubsetLength(int n) { this->n = n; }
};
#endif // !__DECIMATION_SELECTION_H__
