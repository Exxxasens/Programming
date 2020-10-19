a, operation, b = input().split()
a = int(a)
b = int(b)

if operation == '+':
    print(a+b)
elif operation == '*':
    print(a*b)
elif operation == '-':
    print(a-b)
elif operation == '/':
    if b == 0:
        print("Ошибка: деление на ноль")
    else:
        print(a/b)
else:
    print("Незвестная операция")
