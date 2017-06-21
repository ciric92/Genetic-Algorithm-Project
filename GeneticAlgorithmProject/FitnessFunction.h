#ifndef __FITNESS_FUNCTION_H__
#define __FITNESS_FUNCTION_H__

#include <vector>

class FitnessFunction {

public:

	virtual double function(std::vector<double> values) = 0;

};
#endif // !__FITNESS_FUNCTION_H__
