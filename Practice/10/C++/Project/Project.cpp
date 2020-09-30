#include <iostream>

using namespace std;

int main() {
    int s, l_1, r_1, l_2, r_2;
    cin >> s >> l_1 >> r_1 >> l_2 >> r_2;

    int max = r_1 + r_2;
    int min = l_1 + l_2;

    if (min > s || s > max) {
        cout << -1 << endl;
        return 0;
    }


    if (s - l_1 >= l_2 && s - l_1 <= r_2) {
        cout << l_1 << ' ' << s - l_1 << endl;
        return 0;
    }
    if (l_2 - s >= l_1 && l_2 - s <= r_1) {
        cout << l_2 - s << ' ' << l_2 << endl;
        return 0;
    }
    if (r_2 - s >= l_1 && r_2 - s <= r_1) {
        cout << r_2 - s << ' ' << r_2 << endl;
        return 0;
    }
    if (r_1 + s >= l_2 && r_1 + s <= r_2) {
        cout << r_1 << ' ' << r_1 + s << endl;
        return 0;
    }

}