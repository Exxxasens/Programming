#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

const auto PI = 3.141592653589793;

enum System {
    Cartesian,
    Polar
};

class Point {
public:
    double x, y, r, phi;
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
        x = calc_x(r, value);
        y = calc_y(r, value);
    }
private:
    double calc_r(double x, double y) {
        return sqrt(x * x + y * y);
    }
    double calc_phi(double x, double y) {
        return atan2(y, x);
    }
    double calc_x(double r, double phi) {
        return r * cos(phi);
    }
    double calc_y(double r, double phi) {
        return r * sin(phi);
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

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180 * PI / 180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
