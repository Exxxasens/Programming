#include <iostream>
#include <typeinfo>

struct IntArray {
    int * data;
    int size;
};

void create(IntArray* arr, int size);
void create(IntArray& arr, int size);
int get(IntArray* arr, int index);
int get(IntArray& arr, int index);
void set(IntArray* arr, int index, int value);
void set(IntArray& arr, int index, int value);
void print(IntArray* arr);
void print(IntArray& arr);
void resize(IntArray* arr, int newSize);
void resize(IntArray& arr, int newSize);
void destroy(IntArray* arr);
void destroy(IntArray& arr);

void create(IntArray* arr, int size) {
    arr -> data = new int[size];
    arr -> size = size;
}

void create(IntArray& arr, int size) {
    create(&arr, size);
}

void isSafe(IntArray arr, int index) {
    if (index > arr.size) {
        std::cout << "index выходит за пределы массива" << std::endl;
        exit(0);
    }
}

int get(IntArray* arr, int index) {
    isSafe(*arr, index);
    return arr -> data[index];
}

int get(IntArray& arr, int index) {
    return get(&arr, index);
}

void set(IntArray* arr, int index, int value) {
    isSafe(*arr, index);
    arr -> data[index] = value;
}

void set(IntArray& arr, int index, int value) {
    set(&arr, index, value);
}

void print(IntArray* arr) {
    std::cout << "[";
    for (int i = 0; i < arr -> size; i++) {
        std::cout << arr -> data[i];
        if (i < arr -> size-1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void print(IntArray& arr) {
    print(&arr);
}

void resize(IntArray* arr, int newSize) {
    auto newArray = new int[newSize];
    for (int i = 0; i < newSize; i++) {
        if (arr->size > i) {
            newArray[i] = arr -> data[i];
        } else {
            newArray[i] = 0;
        }
    }
    destroy(arr);
    arr -> data = newArray;
    arr -> size = newSize;
}

void resize(IntArray& arr, int newSize) {
    resize(&arr, newSize);
}

void destroy(IntArray* arr) {
    delete[] arr->data;
}

void destroy(IntArray& arr) {
    destroy(&arr);
}


int main() {
    setlocale(LC_ALL, "Rus");
    IntArray array;
    create(array, 30);

    for (int i = 0; i < array.size; i++)
        set(array, i, i+1);
    
    print(array);  // print array with 30 elements
    resize(array, 10000000); // resize array to 50 elements
    print(array); // print array with 50 elements
    resize(array, 10); // resize array to 10 elements
    print(array); // print array with 10 elements
    
    return 0;
}
