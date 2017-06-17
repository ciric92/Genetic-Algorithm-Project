#ifndef __DEFAULT_RANDOM_NUMBER_SUPPLIER_H__
#define __DEFAULT_RANDOM_NUMBER_SUPPLIER_H__

#include "RandomNumberSupplier.h"
#include <random>

class DefaultRandomNumberSupplier : public RandomNumberSupplier {

public:

	DefaultRandomNumberSupplier() {}

	~DefaultRandomNumberSupplier() {}
	
	int getRandomNumber() { return rand(); }
	
	double getRandomNumber0to1() { return ((double)rand() / (RAND_MAX)) + 1; }

	int getRandomNumber(int limit) { return rand() % limit; }
};
#endif // !__DEFAULT_RANDOM_NUMBER_SUPPLIER_H__

