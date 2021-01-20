#include <iostream>
#include <vector>

void printMultipliers(std::vector<int> m) {
    int prevM;
    int counter = 1;
    int i = 0;

    std::cout << " = 1";


    while (i < m.size()) {
        if (prevM == m[i]) {
            counter++;
        }
        else {

            if (counter != 1) {
                std::cout << "^" << counter;
                counter = 1;
            }

            std::cout << "*" << m[i];

        }
        prevM = m[i];
        i++;
    }

    std::cout << std::endl;
}

int main() {
    int n, div = 2;
    std::vector <int> multi;

    std::cout << "N = ";
    std::cin >> n;

    while (n > 1) {
        while (n % div == 0) {
            multi.push_back(div);
            n = n / div;
        }

        div++;
    }

    printMultipliers(multi);

    return 0;
}
