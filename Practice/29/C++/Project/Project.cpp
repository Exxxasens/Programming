#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BozoSort(std::vector<Student> arr) {
    int size = arr.size();
    int slot1 = 0;
    int slot2 = 0;


    srand(time(NULL));

    while (!isSorted(arr)) {

        slot1 = rand() % size;
        slot2 = rand() % size;

        std::swap(arr[slot1], arr[slot2]);
    }
}

bool isSorted(std::vector<Student> arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

struct Student {
    std::string name;
    int group;
    std::map <std::string, int> exams;
};

int getMark() {
    return rand() % 4 + 2;
}

std::ostream& operator <<(std::ostream& os, Student& st) {
    int math = st.exams["mathematics"];
    int phys = st.exams["physics"];
    int hist = st.exams["history"];
    int prog = st.exams["programming"];
    os << "+-----------------+-------+------+------+------+------+" << std::endl;
    os << "| Name            | Group | Math | Phys | Hist | Prog |" << std::endl;
    os << "+-----------------+-------+------+------+------+------+" << std::endl;
    os << "| ";
    os.width(15); os << std::left << st.name;
    os << " |  " << st.group << "    | " << math << "    | " << phys << "    | " << hist << "    | " << prog << "    |" << std::endl;
    os << "+-----------------+-------+------+------+------+------+" << std::endl;
    return os;
}

std::ostream& operator <<(std::ostream& os, std::vector<Student>& students) {
    os << "+-----------------+-------+------+------+------+------+" << std::endl;
    os << "| Name            | Group | Math | Phys | Hist | Prog |" << std::endl;
    os << "+-----------------+-------+------+------+------+------+" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        int math = students[i].exams["mathematics"];
        int phys = students[i].exams["physics"];
        int hist = students[i].exams["history"];
        int prog = students[i].exams["programming"];
        int group = students[i].group;
        std::string name = students[i].name;
        os << "| ";
        os.width(15); os << std::left << name;
        os << " |  " << group << "    | " << math << "    | " << phys << "    | " << hist << "    | " << prog << "    |" << std::endl;
        os << "+-----------------+-------+------+------+------+------+" << std::endl;
    }

    return os;
}

bool operator> (Student & s1, const Student& s2) {
    return strcmp(s1.name.c_str(), s2.name.c_str());
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
    std::cout << "Все студенты:" << std::endl;
    std::cout << students;
    std::cout << "Студент №5" << std::endl;
    std::cout << students[4] << std::endl;


    BozoSort(students);
    std::cout << students;

    return 0;
}
