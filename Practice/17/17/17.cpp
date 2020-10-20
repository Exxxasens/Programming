#include <iostream>
#include <vector>

const int K = 12;
const int S = 37;

bool has(std::vector <int> array, int n) {
    int length = array.size();
    for (int i = 0; i < length; i++) {
        if (array[i] == n) return true;
    }
    return false;
}

int main() {
    
    int numbers[S] = {};
    std::vector <int> lastNums; // last nums for k games;
    int input;

    do {
        std::cin >> input;
        numbers[input]++;
        lastNums.push_back(input);

        int f = 0;

        for (int i = 0; i < S; i++) {
            if (numbers[i] > f) {
                f = numbers[i];
            }
        }

        for (int i = 0; i < S; i++) {
            if (f == numbers[i]) {
                std::cout << i << ' ';
            }
        }

        for (int i = 0; i < S; i++) {
            if (has() {

            }
        }

    } while (input >= 0 && input <= 36);


}
