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

    std::cout << students[3];

    int m;

    std::cin >> m;

    return 0;
}
