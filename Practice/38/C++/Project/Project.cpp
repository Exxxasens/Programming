#include <iostream>

class Rational {
public:
    int num, den;
    static int gcd(int a, int b) {
        while (b != 0) {
            a = a % b;

            if (a == 0) {
                a = b;
                b = 0;

            }
            else b = b % a;
        }

        return abs(a);
    }

    static int gcf(int a, int b) {
        return (a * b) / gcd(a, b);
    }

    Rational() {
        num = 0;
        den = 0;
    }

    Rational(int a, int b) {
        num = a;
        den = b;
    }

    bool operator == (Rational other) {
        if (isNaN() || other.isNaN())
            return false;

        if (den == 0 && other.den == 0) {
            if (num * other.num < 0) return false;

            return true;
        }

        if (num == 0 && other.num == 0) {
            return true;
        }

        if (den == 0 || other.den == 0 || num == 0 || other.num == 0)
            return false;

        int g = gcf(den, other.den);

        if (num * (g / den) == other.num * (g / other.den))
            return true;

        return false;
    }

    Rational operator + (Rational other) {
        if (isNaN() || other.isNaN()) return Rational(0, 0);

        if (den == other.den)
            return Rational(num + other.num, den);

        if (den == 0)
            return Rational(num, 0);

        if (other.den == 0)
            return Rational(other.num, 0);

        if (num == 0)
            return Rational(other.num, other.den);

        if (other.num == 0)
            return Rational(num, den);


        int g = gcf(den, other.den);

        return Rational((g / den) + (g / other.den), g);
    }

    Rational operator - (Rational other) {
        if (isNaN() || other.isNaN())
            return Rational(0, 0);

        if (den == other.den)
            return Rational(num - other.num, den);

        if (den == 0)
            return Rational(num, 0);

        if (other.den == 0)
            return Rational(-other.num, 0);

        if (num == 0)
            return Rational(other.num, other.den);

        if (other.num == 0)
            return Rational(num, den);

        int g = gcf(den, other.den);
        return Rational((g / den) - (g / other.den), g);
    }

    Rational operator * (Rational other) {
        return Rational(num * other.num, den * other.den);
    }

    Rational operator / (Rational other) {
        if (other.den == 0 and num < 0)
            return Rational(num * other.den, -den * other.num);

        if (den == 0 and other.num < 0)
            return Rational(-num * other.den, den * other.num);

        return Rational(num * other.den, den * other.num);
    }

    operator double() {
        if (isNaN()) return std::numeric_limits<double>::quiet_NaN();

        if (num == 0) return 0;

        if (den == 0) return std::numeric_limits<double>::infinity();

        return double(num) / double(den);
    }

    operator bool() {
        if (isNaN()) return true;
        if (num == 0) return false;

        return true;
    }

    double numerator() {
        return num;
    }

    double denominator() {
        return den;
    }

    bool isNaN() {
        if (num == 0 && den == 0) return true;
        return false;
    }

};

bool equal(double a, double b, double e = 1e-10) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

int main()
{
    if (Rational::gcd(91, 65) == 13 &&
        Rational::gcd(10, 3) == 1 &&
        Rational::gcd(-10, 3) == 1 &&
        Rational::gcd(10, -3) == 1 &&
        Rational::gcd(-10, -3) == 1 &&
        Rational::gcd(30, 10) == 10 &&
        Rational::gcd(10, 30) == 10 &&
        Rational::gcd(0, 10) == 10 &&
        Rational::gcd(10, 0) == 10) std::cout << "gcd test passed\n";
    else std::cout << "gcd test failed\n";

    if (!Rational(22, 0).isNaN() &&
        !Rational(22, 9).isNaN() &&
        !Rational(0, 9).isNaN() &&
        !Rational(-22, 9).isNaN() &&
        !Rational(-22, 0).isNaN() &&
        Rational(0, 0).isNaN()
        ) std::cout << "isNaN test passed\n";
    else std::cout << "isNaN test failed\n";

    if (Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 0) == Rational(9, 0) &&
        !(Rational(22, 0) == Rational(22, 9)) &&
        !(Rational(22, 0) == Rational(-22, 9)) &&
        !(Rational(22, 0) == Rational(-22, 0)) &&
        !(Rational(22, 0) == Rational(0, 9)) &&
        !(Rational(22, 0) == Rational(0, 0)) &&

        Rational(22, 9) == Rational(22, 9) &&
        Rational(22, 9) == Rational(-22, -9) &&
        Rational(22, 9) == Rational(110, 45) &&
        Rational(22, 9) == Rational(-110, -45) &&
        !(Rational(22, 9) == Rational(-22, 9)) &&
        !(Rational(22, 9) == Rational(22, -9)) &&
        !(Rational(22, 9) == Rational(9, 22)) &&
        !(Rational(22, 9) == Rational(22, 0)) &&
        !(Rational(22, 9) == Rational(-22, 0)) &&
        !(Rational(22, 9) == Rational(0, 9)) &&
        !(Rational(22, 9) == Rational(0, 0)) &&

        Rational(0, 1) == Rational(0, 1) &&
        Rational(0, 1) == Rational(0, 9) &&
        Rational(0, 1) == Rational(0, -9) &&
        !(Rational(0, 1) == Rational(22, 9)) &&
        !(Rational(0, 1) == Rational(-22, 9)) &&
        !(Rational(0, 1) == Rational(22, 0)) &&
        !(Rational(0, 1) == Rational(-22, 0)) &&
        !(Rational(0, 1) == Rational(0, 0)) &&

        Rational(-22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) == Rational(22, -9) &&
        Rational(-22, 9) == Rational(-110, 45) &&
        Rational(-22, 9) == Rational(110, -45) &&
        !(Rational(-22, 9) == Rational(-22, -9)) &&
        !(Rational(-22, 9) == Rational(22, 9)) &&
        !(Rational(-22, 9) == Rational(9, -22)) &&
        !(Rational(-22, 9) == Rational(22, 0)) &&
        !(Rational(-22, 9) == Rational(-22, 0)) &&
        !(Rational(-22, 9) == Rational(0, 9)) &&
        !(Rational(-22, 9) == Rational(0, 0)) &&

        Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) == Rational(-9, 0) &&
        !(Rational(-22, 0) == Rational(22, 9)) &&
        !(Rational(-22, 0) == Rational(-22, 9)) &&
        !(Rational(-22, 0) == Rational(22, 0)) &&
        !(Rational(-22, 0) == Rational(0, 9)) &&
        !(Rational(-22, 0) == Rational(0, 0)) &&

        !(Rational(0, 0) == Rational(0, 0))
        ) std::cout << "Equality test passed\n";
    else std::cout << "Equality test failed\n";

    if (Rational(22, 0) + Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 9) + Rational(22, 0) == Rational(22, 0) &&
        Rational(0, 9) + Rational(22, 0) == Rational(22, 0) &&
        Rational(-22, 9) + Rational(22, 0) == Rational(22, 0) &&
        (Rational(-22, 0) + Rational(22, 0)).isNaN() &&

        Rational(22, 0) + Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) + Rational(22, 9) == Rational(44, 9) &&
        Rational(0, 9) + Rational(22, 9) == Rational(22, 9) &&
        Rational(-22, 9) + Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 0) + Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) + Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) + Rational(0, 1) == Rational(22, 9) &&
        Rational(0, 9) + Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) + Rational(0, 1) == Rational(-22, 9) &&
        Rational(-22, 0) + Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) + Rational(-22, 9) == Rational(22, 0) &&
        Rational(22, 9) + Rational(-22, 9) == Rational(0, 9) &&
        Rational(0, 9) + Rational(-22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) + Rational(-22, 9) == Rational(-44, 9) &&
        Rational(-22, 0) + Rational(-22, 9) == Rational(-22, 0) &&

        (Rational(22, 0) + Rational(-22, 0)).isNaN() &&
        Rational(22, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(0, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) + Rational(-22, 0) == Rational(-22, 0) &&

        (Rational(22, 0) + Rational(0, 0)).isNaN() &&
        (Rational(22, 9) + Rational(0, 0)).isNaN() &&
        (Rational(0, 9) + Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) + Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) + Rational(0, 0)).isNaN()
        ) std::cout << "Summation test passed\n";
    else std::cout << "Summation test failed\n";

    if ((Rational(22, 0) - Rational(22, 0)).isNaN() &&
        Rational(22, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(0, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) - Rational(22, 0) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) - Rational(22, 9) == Rational(0, 9) &&
        Rational(0, 9) - Rational(22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) - Rational(22, 9) == Rational(-44, 9) &&
        Rational(-22, 0) - Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) - Rational(0, 1) == Rational(22, 9) &&
        Rational(0, 9) - Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) - Rational(0, 1) == Rational(-22, 9) &&
        Rational(-22, 0) - Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(-22, 9) == Rational(22, 0) &&
        Rational(22, 9) - Rational(-22, 9) == Rational(44, 9) &&
        Rational(0, 9) - Rational(-22, 9) == Rational(22, 9) &&
        Rational(-22, 9) - Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 0) - Rational(-22, 9) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(22, 9) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(0, 9) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(-22, 9) - Rational(-22, 0) == Rational(22, 0) &&
        (Rational(-22, 0) - Rational(-22, 0)).isNaN() &&

        (Rational(22, 0) - Rational(0, 0)).isNaN() &&
        (Rational(22, 9) - Rational(0, 0)).isNaN() &&
        (Rational(0, 9) - Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) - Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) - Rational(0, 0)).isNaN()
        ) std::cout << "Subtraction test passed\n";
    else std::cout << "Subtraction test failed\n";

    if (Rational(22, 0) * Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 9) * Rational(22, 0) == Rational(22, 0) &&
        (Rational(0, 9) * Rational(22, 0)).isNaN() &&
        Rational(-22, 9) * Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) * Rational(22, 0) == Rational(-22, 0) &&

        Rational(22, 0) * Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) * Rational(22, 9) == Rational(22 * 22, 9 * 9) &&
        Rational(0, 9) * Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(22, 9) == Rational(-22 * 22, 9 * 9) &&
        Rational(-22, 0) * Rational(22, 9) == Rational(-22, 0) &&

        (Rational(22, 0) * Rational(0, 1)).isNaN() &&
        Rational(22, 9) * Rational(0, 1) == Rational(0, 9) &&
        Rational(0, 9) * Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(0, 1) == Rational(0, 9) &&
        (Rational(-22, 0) * Rational(0, 1)).isNaN() &&

        Rational(22, 0) * Rational(-22, 9) == Rational(-22, 0) &&
        Rational(22, 9) * Rational(-22, 9) == Rational(-22 * 22, 9 * 9) &&
        Rational(0, 9) * Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(-22, 9) == Rational(22 * 22, 9 * 9) &&
        Rational(-22, 0) * Rational(-22, 9) == Rational(22, 0) &&

        Rational(22, 0) * Rational(-22, 0) == Rational(-22, 0) &&
        Rational(22, 9) * Rational(-22, 0) == Rational(-22, 0) &&
        (Rational(0, 9) * Rational(-22, 0)).isNaN() &&
        Rational(-22, 9) * Rational(-22, 0) == Rational(22, 0) &&
        Rational(-22, 0) * Rational(-22, 0) == Rational(22, 0) &&

        (Rational(22, 0) * Rational(0, 0)).isNaN() &&
        (Rational(22, 9) * Rational(0, 0)).isNaN() &&
        (Rational(0, 9) * Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) * Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) * Rational(0, 0)).isNaN()
        ) std::cout << "Multiplication test passed\n";
    else std::cout << "Multiplication test failed\n";

    if ((Rational(22, 0) / Rational(22, 0)).isNaN() &&
        Rational(22, 9) / Rational(22, 0) == Rational(0, 9) &&
        Rational(0, 9) / Rational(22, 0) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(22, 0) == Rational(0, 9) &&
        (Rational(-22, 0) / Rational(22, 0)).isNaN() &&

        Rational(22, 0) / Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) / Rational(22, 9) == Rational(9, 9) &&
        Rational(0, 9) / Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(22, 9) == Rational(-9, 9) &&
        Rational(-22, 0) / Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) / Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) / Rational(0, 1) == Rational(22, 0) &&
        (Rational(0, 9) / Rational(0, 1)).isNaN() &&
        Rational(-22, 9) / Rational(0, 1) == Rational(-22, 0) &&
        Rational(-22, 0) / Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) / Rational(-22, 9) == Rational(-22, 0) &&
        Rational(22, 9) / Rational(-22, 9) == Rational(-9, 9) &&
        Rational(0, 9) / Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(-22, 9) == Rational(9, 9) &&
        Rational(-22, 0) / Rational(-22, 9) == Rational(22, 0) &&

        (Rational(22, 0) / Rational(-22, 0)).isNaN() &&
        Rational(22, 9) / Rational(-22, 0) == Rational(0, 9) &&
        Rational(0, 9) / Rational(-22, 0) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(-22, 0) == Rational(0, 9) &&
        (Rational(-22, 0) / Rational(-22, 0)).isNaN() &&

        (Rational(22, 0) / Rational(0, 0)).isNaN() &&
        (Rational(22, 9) / Rational(0, 0)).isNaN() &&
        (Rational(0, 9) / Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) / Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) / Rational(0, 0)).isNaN()
        ) std::cout << "Division test passed\n";
    else std::cout << "Division test failed\n";

    if (equal(Rational(-22, -9), 22 / 9.0) &&
        equal(Rational(-9, -9), 1) &&
        equal(Rational(-6, -9), 6 / 9.0) &&
        equal(Rational(0, -9), 0) &&
        equal(Rational(6, -9), -6 / 9.0) &&
        equal(Rational(9, -9), -1) &&
        equal(Rational(22, -9), -22 / 9.0) &&
        std::isinf((double)Rational(-9, 0)) &&
        std::isnan((double)Rational(0, 0)) &&
        std::isinf((double)Rational(9, 0)) &&
        equal(Rational(-22, 9), -22 / 9.0) &&
        equal(Rational(-9, 9), -1) &&
        equal(Rational(-6, 9), -6 / 9.0) &&
        equal(Rational(0, 9), 0) &&
        equal(Rational(6, 9), 6 / 9.0) &&
        equal(Rational(9, 9), 1) &&
        equal(Rational(22, 9), 22 / 9.0)) std::cout << "Conversion to double test passed\n";
    else std::cout << "Conversion to double test failed\n";

    if (Rational(-22, -9) &&
        Rational(-9, -9) &&
        Rational(-6, -9) &&
        !Rational(0, -9) &&
        Rational(6, -9) &&
        Rational(9, -9) &&
        Rational(22, -9) &&
        Rational(-9, 0) &&
        Rational(0, 0) &&
        Rational(9, 0) &&
        Rational(-22, 9) &&
        Rational(-9, 9) &&
        Rational(-6, 9) &&
        !Rational(0, 9) &&
        Rational(6, 9) &&
        Rational(9, 9) &&
        Rational(22, 9)) std::cout << "Conversion to bool test passed\n";
    else std::cout << "Conversion to bool test failed\n";

}