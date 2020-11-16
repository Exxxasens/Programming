#pragma once
#ifndef FACTORIAL
#define FACTORIAL

unsigned int factorial(int n) {

	if (n > 0) return n * factorial(n - 1);

	return 1;

}

#endif