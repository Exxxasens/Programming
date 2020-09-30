#include <iostream>

using namespace std;

int main() {
    int factorial;
    unsigned long long int result = 1;

    cin >> factorial;

    for (int i = 2; i <= factorial; i++) result *= i;

    cout << result << endl;

    return 0;
}
