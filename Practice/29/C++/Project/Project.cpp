#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Student {
    std::string name;
    int group;
    std::map <std::string, int> exams;
};

int getMark() {
    return rand() % 4 + 2;
}

void fillData(std::vector<Student>& list) {

    std::vector<std::string> people = {
        "Федорова В",
        "Вавилова М",
        "Прокофьев Г",
        "Костин Э",
        "Сахарова В",
        "Бирюкова А",
        "Касаткина А",
        "Исакова Т",
        "Гусев М",
        "Маслов П"
    };

    for (int i = 0; i < people.size(); i++) {
        Student person = {
            people[i], 3, {
                { "mathematics", getMark() },
                { "physics", getMark() },
                { "history", getMark() },
                { "programming", getMark() }
            }
        };
        list.push_back(person);
    }

}

int main() {

    setlocale(LC_ALL, "Russian");

    srand(time(NULL));
    std::vector<Student> students;

    fillData(students);

    std::cout << "struct size: " << students.size() << std::endl;

    for (int i = 0; i < students.size(); i++) {
        std::cout << "name: " << students[i].name << std::endl;
        std::cout << students[i].exams["mathematics"] << std::endl;
    }

    int m;

    std::cin >> m;

    return 0;
}
