#include <iostream>

using namespace std;

int main() {
    int num, pow;
    long long int result = 1;

    cin >> num >> pow;

    for (int i = 0; i < pow; i++) result *= num;

    cout << result << endl;

    return 0;
}
