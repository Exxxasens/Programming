#ifndef TAYLOR_SERIES
#define TAYLOR_SERIES

#include "factorial.h"
#include <cmath>

double taylorSeries(double x, int k) {
	double result = 0;

	for (int i = 0; i < k; i += 1) {
		int q = 1;
		if (i % 2 != 0) {
			q = -1;
		}

		result += q * (pow(x, 2 * k + 1) / factorial(2 * k + 1));
	}

	return result;

}

#endif