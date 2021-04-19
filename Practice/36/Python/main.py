from enum import Enum
from math import sqrt, atan2, cos, sin, pi
import copy


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


with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]

simulacrum = copy.deepcopy(original)
for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180 * pi / 180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')