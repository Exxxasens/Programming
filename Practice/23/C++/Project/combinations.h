#pragma once

#ifndef COMBINATIONS
#define COMBINATIONS

#include "factorial.h"

unsigned long long int combinations(int k, int n) {
	return (factorial(n) / (factorial(k) * factorial(n - k));
}

#endif