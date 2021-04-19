import math


class Rational:
    @staticmethod
    def gcd(a, b):
        while b != 0:
            a = a % b

            if a == 0:
                a = b
                b = 0

            else:
                b = b % a

        return abs(a)

    @staticmethod
    def gcf(a, b):
        return (a * b) / Rational.gcd(a, b)

    def __init__(self, numerator=None, denominator=None):
        if numerator is not None and denominator is not None:
            self.num = numerator
            self.den = denominator

        elif denominator is None:
            self.num = numerator
            self.den = denominator

        elif numerator is None and denominator is None:
            self.num = 0
            self.den = 0

    def __eq__(self, other):
        if self.isNaN() or other.isNaN():
            return False

        if self.den == 0 and other.den == 0:
            if self.num * other.num < 0:
                return False

            return True

        if self.num == 0 and other.num == 0:
            return True

        if self.den == 0 or other.den == 0 or self.num == 0 or other.num == 0:
            return False

        gcf = Rational.gcf(self.den, other.den)

        if self.num * (gcf / self.den) == other.num * (gcf / other.den):
            return True

        return False

    def __add__(self, other):
        if self.isNaN() or other.isNaN():
            return Rational(0, 0)

        if self.den == other.den:
            return Rational(self.num + other.num, self.den)

        if self.den == 0:
            return Rational(self.num, 0)

        if other.den == 0:
            return Rational(other.num, 0)

        if self.num == 0:
            return Rational(other.num, other.den)

        if other.num == 0:
            return Rational(self.num, self.den)

        gcf = Rational.gcf(self.den, other.den)

        return Rational((gcf / self.den) + (gcf / other.den), gcf)

    def __sub__(self, other):

        if self.isNaN() or other.isNaN():
            return Rational(0, 0)

        if self.den == other.den:
            return Rational(self.num - other.num, self.den)

        if self.den == 0:
            return Rational(self.num, 0)

        if other.den == 0:
            return Rational(-other.num, 0)

        if self.num == 0:
            return Rational(other.num, other.den)

        if other.num == 0:
            return Rational(self.num, self.den)

        gcf = Rational.gcf(self.den, other.den)
        return Rational((gcf / self.den) - (gcf / other.den), gcf)

    def __mul__(self, other):
        return Rational(self.num * other.num, self.den * other.den)

    def __truediv__(self, other):

        if other.den == 0 and self.num < 0:
            return Rational(self.num * other.den, -self.den * other.num)

        if self.den == 0 and other.num < 0:
            return Rational(-self.num * other.den, self.den * other.num)

        return Rational(self.num * other.den, self.den * other.num)

    def __float__(self):

        if self.isNaN():
            return float('nan')

        if self.num == 0:
            return float(0)

        if self.den == 0:
            if self.num >= 0:
                return float('inf')
            else:
                return float('-inf')

        return float(self.num / self.den)

    def __bool__(self):
        if self.isNaN():
            return True

        if self.num == 0:
            return False

        return True

    def isNaN(self):
        if self.num == 0 and self.den == 0:
            return True

        return False

    def numerator(self):
        return self.num

    def denominator(self):
        return self.den


def equal(a, b, e=1E-10):
    if -e < a - b < e:
        return True
    else:
        return False


if (Rational.gcd(91, 65) == 13 and
        Rational.gcd(10, 3) == 1 and
        Rational.gcd(-10, 3) == 1 and
        Rational.gcd(10, -3) == 1 and
        Rational.gcd(-10, -3) == 1 and
        Rational.gcd(30, 10) == 10 and
        Rational.gcd(10, 30) == 10 and
        Rational.gcd(0, 10) == 10 and
        Rational.gcd(10, 0) == 10
):
    print('gcd test passed')
else:
    print('gcd test failed')

if (not Rational(22, 0).isNaN() and
        not Rational(22, 9).isNaN() and
        not Rational(0, 9).isNaN() and
        not Rational(-22, 9).isNaN() and
        not Rational(-22, 0).isNaN() and
        Rational(0, 0).isNaN()
):
    print('isNaN test passed')
else:
    print('isNaN test failed')

if (Rational(22, 0) == Rational(22, 0) and
        Rational(22, 0) == Rational(9, 0) and
        not (Rational(22, 0) == Rational(22, 9)) and
        not (Rational(22, 0) == Rational(-22, 9)) and
        not (Rational(22, 0) == Rational(-22, 0)) and
        not (Rational(22, 0) == Rational(0, 9)) and
        not (Rational(22, 0) == Rational(0, 0)) and

        Rational(22, 9) == Rational(22, 9) and
        Rational(22, 9) == Rational(-22, -9) and
        Rational(22, 9) == Rational(110, 45) and
        Rational(22, 9) == Rational(-110, -45) and
        not (Rational(22, 9) == Rational(-22, 9)) and
        not (Rational(22, 9) == Rational(22, -9)) and
        not (Rational(22, 9) == Rational(9, 22)) and
        not (Rational(22, 9) == Rational(22, 0)) and
        not (Rational(22, 9) == Rational(-22, 0)) and
        not (Rational(22, 9) == Rational(0, 9)) and
        not (Rational(22, 9) == Rational(0, 0)) and

        Rational(0, 1) == Rational(0, 1) and
        Rational(0, 1) == Rational(0, 9) and
        Rational(0, 1) == Rational(0, -9) and
        not (Rational(0, 1) == Rational(22, 9)) and
        not (Rational(0, 1) == Rational(-22, 9)) and
        not (Rational(0, 1) == Rational(22, 0)) and
        not (Rational(0, 1) == Rational(-22, 0)) and
        not (Rational(0, 1) == Rational(0, 0)) and

        Rational(-22, 9) == Rational(-22, 9) and
        Rational(-22, 9) == Rational(22, -9) and
        Rational(-22, 9) == Rational(-110, 45) and
        Rational(-22, 9) == Rational(110, -45) and
        not (Rational(-22, 9) == Rational(-22, -9)) and
        not (Rational(-22, 9) == Rational(22, 9)) and
        not (Rational(-22, 9) == Rational(9, -22)) and
        not (Rational(-22, 9) == Rational(22, 0)) and
        not (Rational(-22, 9) == Rational(-22, 0)) and
        not (Rational(-22, 9) == Rational(0, 9)) and
        not (Rational(-22, 9) == Rational(0, 0)) and

        Rational(-22, 0) == Rational(-22, 0) and
        Rational(-22, 0) == Rational(-9, 0) and
        not (Rational(-22, 0) == Rational(22, 9)) and
        not (Rational(-22, 0) == Rational(-22, 9)) and
        not (Rational(-22, 0) == Rational(22, 0)) and
        not (Rational(-22, 0) == Rational(0, 9)) and
        not (Rational(-22, 0) == Rational(0, 0)) and

        not (Rational(0, 0) == Rational(0, 0))
):
    print('Equality test passed')
else:
    print('Equality test failed')

if (Rational(22, 0) + Rational(22, 0) == Rational(22, 0) and
        Rational(22, 9) + Rational(22, 0) == Rational(22, 0) and
        Rational(0, 9) + Rational(22, 0) == Rational(22, 0) and
        Rational(-22, 9) + Rational(22, 0) == Rational(22, 0) and
        (Rational(-22, 0) + Rational(22, 0)).isNaN() and

        Rational(22, 0) + Rational(22, 9) == Rational(22, 0) and
        Rational(22, 9) + Rational(22, 9) == Rational(44, 9) and
        Rational(0, 9) + Rational(22, 9) == Rational(22, 9) and
        Rational(-22, 9) + Rational(22, 9) == Rational(0, 9) and
        Rational(-22, 0) + Rational(22, 9) == Rational(-22, 0) and

        Rational(22, 0) + Rational(0, 1) == Rational(22, 0) and
        Rational(22, 9) + Rational(0, 1) == Rational(22, 9) and
        Rational(0, 9) + Rational(0, 1) == Rational(0, 9) and
        Rational(-22, 9) + Rational(0, 1) == Rational(-22, 9) and
        Rational(-22, 0) + Rational(0, 1) == Rational(-22, 0) and

        Rational(22, 0) + Rational(-22, 9) == Rational(22, 0) and
        Rational(22, 9) + Rational(-22, 9) == Rational(0, 9) and
        Rational(0, 9) + Rational(-22, 9) == Rational(-22, 9) and
        Rational(-22, 9) + Rational(-22, 9) == Rational(-44, 9) and
        Rational(-22, 0) + Rational(-22, 9) == Rational(-22, 0) and

        (Rational(22, 0) + Rational(-22, 0)).isNaN() and
        Rational(22, 9) + Rational(-22, 0) == Rational(-22, 0) and
        Rational(0, 9) + Rational(-22, 0) == Rational(-22, 0) and
        Rational(-22, 9) + Rational(-22, 0) == Rational(-22, 0) and
        Rational(-22, 0) + Rational(-22, 0) == Rational(-22, 0) and

        (Rational(22, 0) + Rational(0, 0)).isNaN() and
        (Rational(22, 9) + Rational(0, 0)).isNaN() and
        (Rational(0, 9) + Rational(0, 0)).isNaN() and
        (Rational(-22, 9) + Rational(0, 0)).isNaN() and
        (Rational(-22, 0) + Rational(0, 0)).isNaN()
):
    print('Summation test passed')
else:
    print('Summation test failed')

if ((Rational(22, 0) - Rational(22, 0)).isNaN() and
        Rational(22, 9) - Rational(22, 0) == Rational(-22, 0) and
        Rational(0, 9) - Rational(22, 0) == Rational(-22, 0) and
        Rational(-22, 9) - Rational(22, 0) == Rational(-22, 0) and
        Rational(-22, 0) - Rational(22, 0) == Rational(-22, 0) and

        Rational(22, 0) - Rational(22, 9) == Rational(22, 0) and
        Rational(22, 9) - Rational(22, 9) == Rational(0, 9) and
        Rational(0, 9) - Rational(22, 9) == Rational(-22, 9) and
        Rational(-22, 9) - Rational(22, 9) == Rational(-44, 9) and
        Rational(-22, 0) - Rational(22, 9) == Rational(-22, 0) and

        Rational(22, 0) - Rational(0, 1) == Rational(22, 0) and
        Rational(22, 9) - Rational(0, 1) == Rational(22, 9) and
        Rational(0, 9) - Rational(0, 1) == Rational(0, 9) and
        Rational(-22, 9) - Rational(0, 1) == Rational(-22, 9) and
        Rational(-22, 0) - Rational(0, 1) == Rational(-22, 0) and

        Rational(22, 0) - Rational(-22, 9) == Rational(22, 0) and
        Rational(22, 9) - Rational(-22, 9) == Rational(44, 9) and
        Rational(0, 9) - Rational(-22, 9) == Rational(22, 9) and
        Rational(-22, 9) - Rational(-22, 9) == Rational(0, 9) and
        Rational(-22, 0) - Rational(-22, 9) == Rational(-22, 0) and

        Rational(22, 0) - Rational(-22, 0) == Rational(22, 0) and
        Rational(22, 9) - Rational(-22, 0) == Rational(22, 0) and
        Rational(0, 9) - Rational(-22, 0) == Rational(22, 0) and
        Rational(-22, 9) - Rational(-22, 0) == Rational(22, 0) and
        (Rational(-22, 0) - Rational(-22, 0)).isNaN() and

        (Rational(22, 0) - Rational(0, 0)).isNaN() and
        (Rational(22, 9) - Rational(0, 0)).isNaN() and
        (Rational(0, 9) - Rational(0, 0)).isNaN() and
        (Rational(-22, 9) - Rational(0, 0)).isNaN() and
        (Rational(-22, 0) - Rational(0, 0)).isNaN()
):
    print('Subtraction test passed')
else:
    print('Subtraction test failed')

if (Rational(22, 0) * Rational(22, 0) == Rational(22, 0) and
        Rational(22, 9) * Rational(22, 0) == Rational(22, 0) and
        (Rational(0, 9) * Rational(22, 0)).isNaN() and
        Rational(-22, 9) * Rational(22, 0) == Rational(-22, 0) and
        Rational(-22, 0) * Rational(22, 0) == Rational(-22, 0) and

        Rational(22, 0) * Rational(22, 9) == Rational(22, 0) and
        Rational(22, 9) * Rational(22, 9) == Rational(22 * 22, 9 * 9) and
        Rational(0, 9) * Rational(22, 9) == Rational(0, 9) and
        Rational(-22, 9) * Rational(22, 9) == Rational(-22 * 22, 9 * 9) and
        Rational(-22, 0) * Rational(22, 9) == Rational(-22, 0) and

        (Rational(22, 0) * Rational(0, 1)).isNaN() and
        Rational(22, 9) * Rational(0, 1) == Rational(0, 9) and
        Rational(0, 9) * Rational(0, 1) == Rational(0, 9) and
        Rational(-22, 9) * Rational(0, 1) == Rational(0, 9) and
        (Rational(-22, 0) * Rational(0, 1)).isNaN() and

        Rational(22, 0) * Rational(-22, 9) == Rational(-22, 0) and
        Rational(22, 9) * Rational(-22, 9) == Rational(-22 * 22, 9 * 9) and
        Rational(0, 9) * Rational(-22, 9) == Rational(0, 9) and
        Rational(-22, 9) * Rational(-22, 9) == Rational(22 * 22, 9 * 9) and
        Rational(-22, 0) * Rational(-22, 9) == Rational(22, 0) and

        Rational(22, 0) * Rational(-22, 0) == Rational(-22, 0) and
        Rational(22, 9) * Rational(-22, 0) == Rational(-22, 0) and
        (Rational(0, 9) * Rational(-22, 0)).isNaN() and
        Rational(-22, 9) * Rational(-22, 0) == Rational(22, 0) and
        Rational(-22, 0) * Rational(-22, 0) == Rational(22, 0) and

        (Rational(22, 0) * Rational(0, 0)).isNaN() and
        (Rational(22, 9) * Rational(0, 0)).isNaN() and
        (Rational(0, 9) * Rational(0, 0)).isNaN() and
        (Rational(-22, 9) * Rational(0, 0)).isNaN() and
        (Rational(-22, 0) * Rational(0, 0)).isNaN()
):
    print('Multiplication test passed')
else:
    print('Multiplication test failed')

if ((Rational(22, 0) / Rational(22, 0)).isNaN() and
        Rational(22, 9) / Rational(22, 0) == Rational(0, 9) and
        Rational(0, 9) / Rational(22, 0) == Rational(0, 9) and
        Rational(-22, 9) / Rational(22, 0) == Rational(0, 9) and
        (Rational(-22, 0) / Rational(22, 0)).isNaN() and

        Rational(22, 0) / Rational(22, 9) == Rational(22, 0) and
        Rational(22, 9) / Rational(22, 9) == Rational(9, 9) and
        Rational(0, 9) / Rational(22, 9) == Rational(0, 9) and
        Rational(-22, 9) / Rational(22, 9) == Rational(-9, 9) and
        Rational(-22, 0) / Rational(22, 9) == Rational(-22, 0) and

        Rational(22, 0) / Rational(0, 1) == Rational(22, 0) and
        Rational(22, 9) / Rational(0, 1) == Rational(22, 0) and
        (Rational(0, 9) / Rational(0, 1)).isNaN() and
        Rational(-22, 9) / Rational(0, 1) == Rational(-22, 0) and
        Rational(-22, 0) / Rational(0, 1) == Rational(-22, 0) and

        Rational(22, 0) / Rational(-22, 9) == Rational(-22, 0) and
        Rational(22, 9) / Rational(-22, 9) == Rational(-9, 9) and
        Rational(0, 9) / Rational(-22, 9) == Rational(0, 9) and
        Rational(-22, 9) / Rational(-22, 9) == Rational(9, 9) and
        Rational(-22, 0) / Rational(-22, 9) == Rational(22, 0) and

        (Rational(22, 0) / Rational(-22, 0)).isNaN() and
        Rational(22, 9) / Rational(-22, 0) == Rational(0, 9) and
        Rational(0, 9) / Rational(-22, 0) == Rational(0, 9) and
        Rational(-22, 9) / Rational(-22, 0) == Rational(0, 9) and
        (Rational(-22, 0) / Rational(-22, 0)).isNaN() and

        (Rational(22, 0) / Rational(0, 0)).isNaN() and
        (Rational(22, 9) / Rational(0, 0)).isNaN() and
        (Rational(0, 9) / Rational(0, 0)).isNaN() and
        (Rational(-22, 9) / Rational(0, 0)).isNaN() and
        (Rational(-22, 0) / Rational(0, 0)).isNaN()
):
    print('Division test passed')
else:
    print('Division test failed')

if (equal(float(Rational(-22, -9)), 22 / 9.0) and
        equal(float(Rational(-9, -9)), 1) and
        equal(float(Rational(-6, -9)), 6 / 9.0) and
        equal(float(Rational(0, -9)), 0) and
        equal(float(Rational(6, -9)), -6 / 9.0) and
        equal(float(Rational(9, -9)), -1) and
        equal(float(Rational(22, -9)), -22 / 9.0) and
        math.isinf(float(Rational(-9, 0))) and
        math.isnan(float(Rational(0, 0))) and
        math.isinf(float(Rational(9, 0))) and
        equal(float(Rational(-22, 9)), -22 / 9.0) and
        equal(float(Rational(-9, 9)), -1) and
        equal(float(Rational(-6, 9)), -6 / 9.0) and
        equal(float(Rational(0, 9)), 0) and
        equal(float(Rational(6, 9)), 6 / 9.0) and
        equal(float(Rational(9, 9)), 1) and
        equal(float(Rational(22, 9)), 22 / 9.0)
):
    print('Conversion to double test passed')
else:
    print('Conversion to double test failed')

if (bool(Rational(-22, -9)) and
        bool(Rational(-9, -9)) and
        bool(Rational(-6, -9)) and
        not bool(Rational(0, -9)) and
        bool(Rational(6, -9)) and
        bool(Rational(9, -9)) and
        bool(Rational(22, -9)) and
        bool(Rational(-9, 0)) and
        bool(Rational(0, 0)) and
        bool(Rational(9, 0)) and
        bool(Rational(-22, 9)) and
        bool(Rational(-9, 9)) and
        bool(Rational(-6, 9)) and
        not bool(Rational(0, 9)) and
        bool(Rational(6, 9)) and
        bool(Rational(9, 9)) and
        bool(Rational(22, 9))
):
    print('Conversion to bool test passed')
else:
    print('Conversion to bool test failed')
