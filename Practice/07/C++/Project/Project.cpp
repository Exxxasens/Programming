#include <iostream>
#include <cmath>

using namespace std;

bool isExist(double, double, double);
double calcLength(double, double, double, double);
double calcSquare(double, double, double);
void inputParams(int);

int main() {
    setlocale(LC_ALL, "Russian");
    short inputType;

    cin >> inputType;
    inputParams(inputType);

    return 0;
}

bool isExist(double length_1, double length_2, double length_3) {
    if (length_1 + length_2 <= length_3) return false;
    if (length_2 + length_3 <= length_1) return false;
    if (length_1 + length_3 <= length_2) return false;

    return true;
}

double calcLength(double x_1, double y_1, double x_2, double y_2) {
    return sqrt(pow((y_2 - y_1), 2) + pow((x_2 - x_1), 2));
}

void inputParams(int type) {
    double l_1, l_2, l_3;

    if (type == 1) {
        cin >> l_1 >> l_2 >> l_3;
    }
    else if (type == 2) {
        double x_1, y_1, x_2, y_2, x_3, y_3;
        cin >> x_1 >> y_1 >> x_2 >> y_2 >> x_3 >> y_3;

        l_1 = calcLength(x_1, y_1, x_2, y_2);
        l_2 = calcLength(x_1, y_1, x_3, y_3);
        l_3 = calcLength(x_2, y_2, x_3, y_3);

    }
    else {
        cout << "Неверное значение: 1 - ввод параметров треугольника через длины сторон. 2 - ввод параметров через координаты вершин" << endl;
        main();
        return;
    }

    bool exist = isExist(l_1, l_2, l_3);

    if (!exist) {
        cout << "Неверно заданы параметры треугольника: такого треугольника не существует, введите данные заново" << endl;
        return inputParams(type);
    }

    cout << "S = " << calcSquare(l_1, l_2, l_3) << endl;
}

double calcSquare(double l_1, double l_2, double l_3) {
    double p = (l_1 + l_2 + l_3) / 2;
    return sqrt(p * (p - l_1) * (p - l_2) * (p - l_3));
}
