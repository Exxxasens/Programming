﻿#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	double g = 9.8, x, v, t;

	cout << "Введите значения: x, v, t" << endl;
	cin >> x >> v >> t;

	double xt = x + v * t - g * t * t * 0.5;

	cout << abs(xt - x);

	return 0;
}