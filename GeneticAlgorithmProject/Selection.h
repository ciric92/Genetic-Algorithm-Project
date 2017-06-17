#ifndef __SELECTION_H__
#define __SELECTION_H__

#include "Individual.h"

class Selection {
 
protected:

	int n;

public:

	Selection(int n) : n(n) {};

	~Selection() {};

	virtual std::vector<Individual*>* select(std::vector<Individual*>* population) = 0;
};

#endif // !__SELECTION_H__


