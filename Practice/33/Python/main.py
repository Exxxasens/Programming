def create(length, start, step):
    array = []
    for i in range(length):
        array.append(start + (step * i))

    return array

def sort(array):
    for i in range(1, len(array)):
        key = array[i]
        j = i - 1
        while j >= 0 and array[j] > key:
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = key

def printArray(array):
    length = len(array)
    print("[", end="")
    for i in range(length):
        print(array[i], end="")
        if i < length-1:
            print(", ", end="")
    print("]", end="")


length = int(input("Введите длину массива: "))
start = int(input("Введите начальное значение: "))
step = int(input("Введите шаг: "))

array = create(length, start, step)
sort(array)
printArray(array)