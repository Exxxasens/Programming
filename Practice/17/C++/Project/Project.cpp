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
    int gameCounter = 0, black = 0, red = 0;;

    do {
        std::cin >> input;

        if (!(input >= 0 && input <= 36)) {
            return 0;
        }

        numbers[input]++;
        gameCounter++;
        lastNums.push_back(input);



        if (gameCounter > 12) {
            gameCounter = 0;
            lastNums.clear();
            black = 0;
            red = 0;
        }

        if (input % 2 == 0) {
            black++;
        }
        else red++;

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

        std::cout << std::endl;

        for (int i = 0; i < S; i++) {
            if (!has(lastNums, numbers[i])) {
                std::cout << i << ' ';
            }
        }

        std::cout << std::endl;
        std::cout << red << ' ' << black << std::endl;



    } while (true);


}
