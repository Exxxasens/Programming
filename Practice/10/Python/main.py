s, l1, r1, l2, r2 = map(int, input().split(' '))


if l2 <= s - l1 <= r2:
    print(str(l1) + ' ' + str(s-l1))

elif l1 <= l2 - s <= r1:
    print(str(l2-s) + ' ' + str(l2))

elif l1 <= r2 - s <= r1:
    print(str(r2-s) + ' ' + str(r2))

elif l2 <= r1 + s <= r2:
    print(str(r1) + ' ' + str(r1+s))
else:
    print(-1)