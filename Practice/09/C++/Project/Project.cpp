#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    char a;
    int h1, h2, m1, m2;
    cin >> h1 >> a >> m1;
    cin >> h2 >> a >> m2;

    if ((h1 == 0 && h2 == 23 && m2 - 45 + m1 <= 15) || (h1 == 23 && h2 == 0 && m1 - 45 + m2 <= 15)) {
        cout << "Встреча состоится" << endl;
        return 0;
    }

    h1 = h1 * 60 + m1;
    h2 = h2 * 60 + m2;

    if (abs(h1 - h2) > 15) {
        cout << "Встреча не состоится" << endl;
    }
    else {
        cout << "Встреча состоится" << endl;
    }

    return 0;
}
