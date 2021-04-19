#include <iostream>

const auto PI = 3.141592653589793;
double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

enum System {
    Cartesian,
    Polar
};

class Point {
private:
    double x, y, r, phi;

    double calc_r(double _x, double _y) {
        return sqrt(_x * _x + _y * _y);
    }

    double calc_phi(double _x, double _y) {
        double _phi = atan2(_y, _x);
        return _phi;
    }

    double calc_x(double _r, double _phi) {
        return _r * cos(_phi);
    }

    double calc_y(double _r, double _phi) {
        return _r * sin(_phi);
    }
public:
    Point(double a1 = 0, double a2 = 0, System coord_system = System::Cartesian) {
        if (coord_system == System::Cartesian) {
            x = a1;
            y = a2;
            r = calc_r(a1, a2);
            phi = calc_phi(a1, a2);
        }
        else {
            r = a1;
            phi = a2;
            x = calc_x(a1, a2);
            y = calc_y(a1, a2);
        }
    }

    double get_x() const {
        return x;
    }

    double get_y() const {
        return y;
    }

    double get_r() const {
        return r;
    }

    double get_phi() const {
        return phi;
    }

    void set_x(double value) {
        x = value;
        r = calc_r(value, y);
        phi = calc_phi(value, y);
    }

    void set_y(double value) {
        y = value;
        r = calc_r(x, value);
        phi = calc_phi(x, value);
    }

    void set_r(double value) {
        r = value;
        x = calc_x(value, phi);
        y = calc_y(value, phi);
    }

    void set_phi(double value) {
        phi = value;
        x = calc_x(r, phi);
        y = calc_y(r, phi);
    }
};


bool operator == (const Point& p1, const Point& p2) {
    if (abs(p1.get_x() - p2.get_x()) > 1e-5) {
        return false;
    }

    if (abs(p1.get_y() - p2.get_y()) > 1e-5) {
        return false;
    }

    if (abs(p1.get_r() - p2.get_r()) > 1e-5) {
        return false;
    }

    if (abs(p1.get_phi() - p2.get_phi()) > 1e-5) {
        return false;
    }

    return true;
}

bool operator != (const Point& p1, const Point& p2) {
    return !(p1 == p2);
}

std::ostream& operator << (std::ostream& out, Point& point) {
    out << "(" << point.get_x() << "," << point.get_y() << ")";
    return out;
}

std::istream& operator >> (std::istream& in, Point& point) {
    double x, y;
    char d1, d2, d3;
    in >> d1 >> x >> d2 >> y >> d3;
    point.set_x(x);
    point.set_y(y);
    return in;
}

class Vector {
public:
    double x, y;

    Vector(double _x, double _y) {
        x = _x;
        y = _y;
    }

    Vector() {
        x = 1;
        y = 0;
    }

    Vector(Point p) {
        x = p.get_x();
        y = p.get_y();
    }

    Vector(Point b, Point e) {
        x = e.get_x() - b.get_x();
        y = e.get_y() - b.get_y();
    }

    double length() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    Vector operator * (double mul) {
        return Vector(x * mul, y * mul);
    }

    Vector operator - () {
        return (*this * -1);
    }

    Vector operator + (Vector a) {
        return Vector(x + a.x, y + a.y);
    }

    Vector operator - (Vector a) {
        return Vector(x - a.x, y - a.y);
    }

    bool operator == (Vector a) {
        const double e = 1e-10;

        if (a.x - x > e) {
            return false;
        }

        if (a.y - y > e) {
            return false;
        }

        return true;
    }

    double operator * (Vector a) {
        return x * a.x + y * a.y;
    }

};


using namespace std;

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox * ox, sqr(ox.length())) &&
        equal(oy * oy, sqr(oy.length())) &&
        equal((ox * 3 + oy * 4) * (ox * 3 + oy * 4), sqr((ox * 3 + oy * 4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}
