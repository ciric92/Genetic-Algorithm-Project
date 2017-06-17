#ifndef __ROULETTE_SELECTION_H__
#define __ROULETTE_SELECTION_H__

#include "Selection.h"
#include "RandomNumberSupplier.h"

class RouletteSelection : public Selection {

	RandomNumberSupplier* rnd;

public:
	
	RouletteSelection(int n, RandomNumberSupplier* rnd) : Selection(n), rnd(rnd) {};

	~RouletteSelection() {};

	std::vector<Individual*>* select(std::vector<Individual*>* population);
};

#endif // !__ROULETTE_SELECTION_H__
