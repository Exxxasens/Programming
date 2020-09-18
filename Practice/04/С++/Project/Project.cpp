#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	double a, b, c;

	cout << "Введите значение a = ";
	cin >> a;
	cout << "Введите значение b = ";
	cin >> b;

	c = b;
	b = a;
	a = c;

	cout << "Обмен с дополнительной переменной" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	cout << "Введите значение a = ";
	cin >> a;
	cout << "Введите значение b = ";
	cin >> b;

	a = a + b;
	b = a - b;
	a = a - b;

	cout << "Обмен без дополнительной переменной" << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b;

	return 0;
}