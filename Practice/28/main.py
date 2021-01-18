multi = []
n = int(input())

div = 2

while n > 1:
    while n % div == 0:
        multi.append(div)
        n = n / div
    div += 1


def printMultipliers(m):
    counter = 1
    i = 0
    prevM = -1
    first = True

    while(i < len(m)):
        if prevM == m[i]:
            counter += 1
        else:
            if counter > 1:
                print("^", counter, end='', sep='')
                counter = 1
            if first:
                first = False
            else:
                print('*', end='', sep='')
            print(m[i], end='', sep='')

        prevM = m[i]
        i += 1

printMultipliers(multi)