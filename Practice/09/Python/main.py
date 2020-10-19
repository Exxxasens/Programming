import math

h1, m1 = map(int, input().split(":"))
h2, m2 = map(int, input().split(":"))

if h1 > 23 or h2 > 23 or m1 > 59 or m2 > 59:
    print("Ошибка ввода")
elif (h1 == 0 and h2 == 23 and m2 - 45 + m1 <= 15) or (h1 == 23 and h2 == 0 and m1 - 45 + m2 <= 15):
    print("Встреча состоится")
else:
    h1 = h1 * 60 + m1
    h2 = h2 * 60 + m2
    if math.fabs(h1 - h2) > 15:
        print("Встреча не состоится")
    else:
        print("Встреча состоится")
