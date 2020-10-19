import math

select = int(input())


def calc_square(a, b, c):
    p = (a + b + c) / 2
    return math.sqrt(p * (p - a) * (p - b) * (p - c))


def get_length(x1, y1, x2, y2):
    return math.sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2))


if select == 1:
    a = float(input())
    b = float(input())
    c = float(input())
elif select == 2:
    x1, y1 = map(float, input().split())
    x2, y2 = map(float, input().split())
    x3, y3 = map(float, input().split())

    a = get_length(x1, y1, x2, y2)
    b = get_length(x2, y2, x3, y3)
    c = get_length(x1, y1, x3, y3)
else:
    print("Ошибка ввода")
    exit(0)

print("S = " + str(calc_square(a, b, c)))


