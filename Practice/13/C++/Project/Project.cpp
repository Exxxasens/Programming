#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    unsigned long int number;
    cin >> number;

    const int number_sqrt = ceil(sqrt(number));

    for (int i = 2; i <= number_sqrt; i++) {
        if (number % i == 0) {
            cout << "Составное" << endl;
            return 0;
        }
    }

    cout << "Простое" << endl;

    return 0;
}
