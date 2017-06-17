#ifndef __TOURNAMENT_SELECTION_H__
#define __TOURNAMENT_SELECTION_H__

#include "Selection.h"
#include "RandomNumberSupplier.h"

class TournamentSelection : public Selection {

	int tournamentSize;

	RandomNumberSupplier* rnd;

public:

	TournamentSelection(int n, int tournamentSize, RandomNumberSupplier* rnd) : Selection(n), tournamentSize(tournamentSize), rnd(rnd) {};

	~TournamentSelection() {};

	std::vector<Individual*>* select(std::vector<Individual*>* population);
};

#endif // !__TOURNAMENT_SELECTION_H__
