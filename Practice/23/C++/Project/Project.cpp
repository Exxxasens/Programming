#include <iostream>

# define M_PI 3.14159265358979323846
#include "taylor.h"
#include "factorial.h"
#include "combinations.h"

void printFactorialTable() {
	for (int i = 0; i < 10; i++) {
		std::cout << factorial(i);
	}
}

void printSin() {
	for (int i = 0; i < (M_PI / 4); i += (M_PI / 180)) {
		std::cout << taylorSeries(i, 5);
	}
}

void printCombinations() {
	for (int i = 0; i < 10; i++) {
		std::cout << combinations(i, 10);
	}
}

int main()
{
	
	printFactorialTable();
	printSin();
	printCombinations();

}