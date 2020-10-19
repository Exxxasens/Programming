number = int(input())
result = 1
count = 0

if number == 0:
    print(1)
    exit(0)

while number >= result:
    result *= 2
    count += 1

print(count)
