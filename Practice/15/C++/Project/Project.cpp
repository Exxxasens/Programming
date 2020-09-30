#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int NUM_OF_TRIES = 5; // количество попыток
void startGame(short);

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    do {
        cout << "Задано число 0..100, у вас есть " << NUM_OF_TRIES << " попыток, чтобы угадать число" << endl;
        startGame(NUM_OF_TRIES);
        cout << "Хотите начать сначала? (1 - ДА )" << endl;
        int choose;
        cin >> choose;
        if (choose != 1) return 0;
    } while (true);
}

void startGame(short numOfTries) {
    short int random = rand() % 101;
    int counter = 0;

    while (counter < numOfTries) {
        int num;
        cin >> num;
        counter++;
        if (num > random && counter < numOfTries)
            cout << "Загаданное число меньше" << endl;
        if (num < random && counter < numOfTries)
            cout << "Загаданное число больше" << endl;
        if (num == random) {
            cout << "Поздравляю! Вы угадали" << endl;
            return;
        }
    }

    cout << "Вы проиграли. Было загадано: " << random << endl;
}
