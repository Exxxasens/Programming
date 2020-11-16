#include <iostream>
#include "taylor.h"

int main()
{
    double x;
    int k;

    std::cin >> x;
    std::cin >> k;

    std::cout << taylorSeries(x, k);


}