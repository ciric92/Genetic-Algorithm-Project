#ifndef __RANDOM_NUMBER_SUPPLIER_H__
#define __RANDOM_NUMBER_SUPPLIER_H__

class RandomNumberSupplier {
public:
	virtual int getRandomNumber() = 0;
	virtual double getRandomNumber0to1() = 0;
	virtual int getRandomNumber(int limit) = 0;
};

#endif // !__RANDOM_NUMBER_SUPPLIER_H__
