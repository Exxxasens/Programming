import math
from enum import Enum
from math import sqrt, atan2, cos, sin


class CoordSystem(Enum):
    Cartesian = 0
    Polar = 1


class Point:
    @staticmethod
    def calc_r(x, y):
        return sqrt(x * x + y * y)

    @staticmethod
    def calc_phi(x, y):
        return atan2(y, x)

    @staticmethod
    def calc_x(r, phi):
        return r * cos(phi)

    @staticmethod
    def calc_y(r, phi):
        return r * sin(phi)

    def __init__(self, a, b=0, system=CoordSystem.Cartesian):
        if isinstance(a, str):
            slice_obj = slice(1, -1)
            s = a[slice_obj].split(',')
            self.x = float(s[0])
            self.y = float(s[1])

        elif system == CoordSystem.Cartesian:
            self.x = a
            self.y = b
            self.r = Point.calc_r(a, b)
            self.phi = Point.calc_phi(a, b)

        elif system == CoordSystem.Polar:
            self.r = a
            self.phi = b
            self.x = Point.calc_x(a, b)
            self.y = Point.calc_y(a, b)

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_r(self):
        return self.r

    def get_phi(self):
        return self.phi

    def set_x(self, x):
        self.x = x
        self.r = Point.calc_r(x, self.y)
        self.phi = Point.calc_phi(x, self.y)

    def set_y(self, y):
        self.y = y
        self.r = Point.calc_r(self.x, y)
        self.phi = Point.calc_phi(self.x, y)

    def set_r(self, r):
        self.r = r
        self.x = Point.calc_x(r, self.phi)
        self.y = Point.calc_y(r, self.phi)

    def set_phi(self, phi):
        self.phi = phi
        self.x = Point.calc_x(self.r, phi)
        self.y = Point.calc_y(self.r, phi)

    def __str__(self):
        return '({},{})'.format(self.x, self.y)

    def __repr__(self):
        return '({},{})'.format(self.x, self.y)

    def __eq__(self, other):
        if abs(self.x - other.x) > 1e-10:
            return False

        if abs(self.y - other.y) > 1e-10:
            return False

        return True

    def __ne__(self, other):
        return not self.__eq__(other)


class Vector:
    def __init__(self, begin=None, end=None):

        if isinstance(begin, (int, float)) and isinstance(end, (int, float)):
            self.x = begin
            self.y = end

        elif not begin and not end:
            self.x = 1
            self.y = 0

        elif begin and not end:
            self.x = begin.get_x()
            self.y = begin.get_y()

        elif begin and end:
            self.x = end.get_x() - begin.get_x()
            self.y = end.get_y() - begin.get_y()

    def length(self):
        return math.sqrt(pow(self.x, 2) + pow(self.y, 2))

    def __eq__(self, other):
        e = 1e-10
        if self.x - other.x > e:
            return False

        if self.y - other.y > e:
            return False

        return True

    def __mul__(self, other):
        if isinstance(other, (int, float)):
            return Vector(self.x * other, self.y * other)

        return self.x * other.x + self.y * other.y

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __sub__(self, other):
        return Vector(self.x + other.x, self.y + other.y)


def equal(a, b, e=1E-10):
    if -e < a - b < e:
        return True
    else:
        return False


a = Vector(Point(1, 2))
b = Vector(Point(-2, 0), Point(-1, 2))
if a == b and b == a:
    print('Equality test passed')
else:
    print('Equality test failed')

na = Vector(Point(-1, -2))
ox = Vector(Point(1, 0))
nox = Vector(Point(-1, 0))
oy = Vector(Point(0, 1))
noy = Vector(Point(0, -1))
if a == -na and na == -a and -ox == nox and -oy == noy:
    print('Invert test passed')
else:
    print('Invert test failed')

if ox + oy + oy == a and -ox == -a + oy + oy:
    print('Summation test passed')
else:
    print('Summation test failed')

if -ox + oy == oy - ox and -oy + ox == ox - oy:
    print('Subtraction test passed')
else:
    print('Subtraction test failed')

if (ox * 3 == ox + ox + ox and
        oy * 3 == oy + oy + oy and
        ox * (-3) == -ox - ox - ox and
        oy * (-3) == -oy - oy - oy):
    print('Multiplication by number test passed')
else:
    print('Multiplication by number test failed')

if (equal(ox.length(), 1) and
        equal(oy.length(), 1) and
        equal((ox * 3 + oy * 4).length(), 5)):
    print('Length test passed')
else:
    print('Length test failed')

if (equal(ox * ox, ox.length() ** 2) and
        equal(oy * oy, oy.length() ** 2) and
        equal((ox * 3 + oy * 4) * (ox * 3 + oy * 4), (ox * 3 + oy * 4).length() ** 2)):
    print('Multiplication by Vector test passed')
else:
    print('Multiplication by Vector test failed')