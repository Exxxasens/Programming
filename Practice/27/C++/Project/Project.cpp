#include <iostream>
#include <vector>
#include <algorithm>

bool cmp_fn(int a, int b) {
    return a < b;
}


int main(int argc, const char* argv[]) {
    int n;

    std::cin >> n;

    std::vector<int> signals;

    for (int i = 0; i < n; i++) {
        int s;
        std::cin >> s;
        signals.push_back(s);
        sort(signals.begin(), signals.end(), cmp_fn);
        int signalsSize = signals.size();
        if (signalsSize > 5) signalsSize = 5;

        for (int j = 0; j < signalsSize; j++) {
            std::cout << signals[signalsSize - 1 - j];
        }

    }


    return 0;
}
