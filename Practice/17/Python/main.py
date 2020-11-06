def findInList(list, item):
    l = len(list)
    for i in range(l):
        if item == list[i]:
            return True
    return False


numbers = []
numCounter = [0] * 37
gameCounter = 0

red = 0
black = 0

while True:
    inValue = int(input())

    if inValue > 36 or inValue < 0:
        break

    gameCounter += 1
    numbers.append(inValue)
    numCounter[inValue] += 1

    f = 0

    if gameCounter > 12:
        gameCounter = 0
        numbers.clear()

    if inValue % 2 == 0:
        black += 1
    else:
        red += 1

    for i in range(37):
        if numCounter[i] > f:
            f = numCounter[i]

    for i in range(37):
        if numCounter[i] == f:
            print(i, end=' ')

    print()

    for i in range(37):
        if not findInList(numbers, numCounter[i]):
            print(i, end=' ')

    print()
    print(red, black, sep=' ')
