import math

num = int(input())
sqrt = math.ceil(math.sqrt(num))
isSimple = True

for i in range(2, sqrt+1):
    if num % i == 0:
        isSimple = False

if isSimple:
    print("Простое")
else:
    print("Составное")
