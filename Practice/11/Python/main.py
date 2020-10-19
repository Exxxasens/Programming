a = int(input())
b = int(input())
result = 1



if a == 0:
    print(1)
elif b == 0:
    print(1)
elif a == 1:
    print(1)
else:
    for x in range(0, b):
        result *= a
    print(result)