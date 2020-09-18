#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	int a, b;

	cout << "Введите пару int int" << endl;
	cin >> a >> b;
	cout << "Сложение: " << a + b << endl;
	cout << "Вычитание: " << a - b << endl;
	cout << "Умножение: " << a * b << endl;
	cout << "Деление: " << a / b << endl;

	int c;
	double d;
	cout << "Введите пару int double" << endl;
	cin >> c >> d;
	cout << "Сложение: " << c + d << endl;
	cout << "Вычитание: " << c - d << endl;
	cout << "Умножение: " << c * d << endl;
	cout << "Деление: " << c / d << endl;

	double e, f;
	cout << "Введите пару double double" << endl;
	cin >> e >> f;
	cout << "Сложение: " << e + f << endl;
	cout << "Вычитание: " << e - f << endl;
	cout << "Умножение: " << e * f << endl;
	cout << "Деление: " << e / f << endl;

	double g;
	int h;
	cout << "Введите пару double int" << endl;
	cin >> g >> h;
	cout << "Сложение: " << g + h << endl;
	cout << "Вычитание: " << g - h << endl;
	cout << "Умножение: " << g * h << endl;
	cout << "Деление: " << g / h;

	return 0;
}