factorial = int(input())

if factorial == 0:
    print(1)
else:
    result = 1
    for i in range(1, factorial+1):
        result *= i
    print(result)