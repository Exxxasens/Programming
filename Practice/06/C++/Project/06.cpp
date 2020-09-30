#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    double a, b, c;

    cin >> a >> b >> c;

    if (a == 0 && b == 0) {
        cout << "Ошибка ввода" << endl;
    } else if (a == 0) { // линейное уравнение
        cout << -(c / b) << endl;
    } else if (c == 0) {
        cout << 0 << endl;
        cout << b / a << endl;
    }
    else {
        double d = b * b - 4 * a * c;

        if (d < 0) {
            cout << "Уравнение не имеет действительных корней" << endl;
        }
        else if (d == 0) {
            cout << -b / 2 / a;
        }
        else {
            double sqrt_d = sqrt(d);
            cout << (-b + sqrt_d) / 2 / a << endl;
            cout << (-b - sqrt_d) / 2 / a << endl;
        }
    }

    return 0;
}
