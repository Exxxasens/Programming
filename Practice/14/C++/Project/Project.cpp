#include <iostream>
#include "cmath"

using namespace std;

int main() {
    unsigned long long int n;
    unsigned short count = 1;
    cin >> n;

    while (true) {
        if (n / 2.0 >= 1) {
            count++;
            n = n / 2;
        }
        else {
            cout << count << endl;
            return 0;
        }
    }

    return 0;
}
