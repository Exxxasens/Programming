#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    double a, b, c;

    cin >> a >> b >> c;

    if ((a == 0 && b == 0) || (a == 0 && c == 0) || (b == 0 && c == 0)) {
        cout << "Ошибка ввода" << endl;
    } else if (a == 0) { // линейное уравнение
        cout << -(c / b) << endl;
    } else if (c == 0) {
        cout << 0 << endl;
        cout << b / a << endl;
    }
    else if (b == 0) {
        double result = -c / a;
        if (result >= 0) {
            result = sqrt(result);
            cout << "x1 = " << result << endl;
            cout << "x2 = " << -result << endl;
        }
        else {
            cout << "Уравнение не имеет действительных корней" << endl;
        }
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
