#include <iostream>

int * create(int length, int first, int step) {
    int * array = new int[length];
    
    for (int i = 0; i < length; i++) {
        array[i] = first + i * step;
    }
    return array;
}

int * printArray(int * array, int length) {
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

int main(int argc, const char * argv[]) {
    int l, f, s;
    std::cout << "Введите длину массива: ";
    std::cin >> l;
    std::cout << "Введите начальное значение: ";
    std::cin >> f;
    std::cout << "Введите шаг: ";
    std::cin >> s;
    
    auto array = create(l, f, s);
    sort(array, l);
    printArray(array, l);
    
    delete[] array;
    
    return 0;
}
