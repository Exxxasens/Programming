#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    double a, b;
    char operation;
    cin >> a >> operation >> b;

    switch (operation) {
    case '+':
        cout << a + b << endl;
        break;
    case '-':
        cout << a - b << endl;
        break;
    case '*':
        cout << a * b << endl;
        break;
    case '/':
        if (b == 0) {
            cout << "Ошибка: деление на ноль" << endl;
            return 0;
        }
        cout << a / b << endl;
        break;
    default:
        cout << "Неизвестная операция: " << operation << endl;
        break;
    }

    return 0;
}

