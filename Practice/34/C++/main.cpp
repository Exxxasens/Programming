#include <iostream>

void create(int * pointer, int length, int start, int step) {
    for (int i = 0; i < length; i++) {
         pointer[i] = start + (step * i);
    }
}

int * destroy(int * pointer) {
    delete[] pointer;
    pointer = nullptr;
    return pointer;
}

int * print(int * array, int length) {
    std::cout << "[";
    for (int i = 0; i < length; i++) {
        std::cout << array[i];
        if (i < length-1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    return array;
}

int * sort(int * array, int length) {
    int key, j, i;
    for (i = 1; i < length; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
    return array;
}

int main() {
    
    int length, start, step;

    std::cout << "Введите длину массива: ";
    std::cin >> length;
    std::cout << "Введите начальное значение: ";
    std::cin >> start;
    std::cout << "Введите шаг: ";
    std::cin >> step;
    
    int * array = new int[length];
    
    create(array, length, start, step);
    sort(array, length);
    destroy(array);
    
    return 0;
}
