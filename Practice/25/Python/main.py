import random

def isSorted(arr, order = True):
    for i in range(0, len(arr)-1):
        if order and (arr[i] > arr[i+1]):
            return False
        elif not order and (arr[i] < arr[i+1]):
            return False
    return True

def BozoSort(arr, order = True):
    size = len(arr)

    while(not isSorted(arr, order)):
        s1 = random.randint(0, size-1)
        s2 = random.randint(0, size-1)
        temp = arr[s1]
        arr[s1] = arr[s2]
        arr[s2] = temp

    return arr

def BozoSortMatrix(arr, order = True):
    size = len(arr)
    transformed = []
    for i in arr:
        for j in i:
            transformed.append(j)

    transformed = BozoSort(transformed, order)
    c = 0
    for i in range(size):
        for j in range(size):
            arr[i][j] = transformed[c]
            c += 1

    return arr



def BozoSortInt(a, b, c, order = True):
    arr = [a, b, c]
    return BozoSort(arr, order)


n = int(input())
arr = map(int, input().split())
arr = list(arr)

a, b, c = arr[0], arr[1], arr[2]

print(BozoSort(arr), sep=' ')
print(BozoSort(arr, False), sep=' ')
print(BozoSortInt(a, b, c), sep=' ')
print(BozoSortInt(a, b, c, False), sep=' ')



