import math

a = float(input())
b = float(input())
c = float(input())

if (a == 0 and b == 0) or (a == 0 and c == 0) or (b == 0 and c == 0):
    print("Ошибка ввода")
elif a == 0:
    print("x1 = " + str(-c/b))
elif b == 0:
    result = -c/a
    if(result >= 0):
        sqrt = math.sqrt(result)
        print("x1 = " + str(sqrt))
        print("x2 = " + str(-sqrt))
    else:
        print("Уравнение не имеет действительных корней")
elif c == 0:
    print("x1 = 0")
    print("x2 = " + str(-b/a))
else:
    d = b*b - 4*a*c;
    if d > 0:
        result = math.sqrt(d) / 2
        print("x1 = " + str(-b/2 + result))
        print("x2 = " + str(-b/2 - result))
    elif d == 0:
        print("x1 = " + str(-b/2))
    else:
        print("Уравнение не имеет действительных корней")