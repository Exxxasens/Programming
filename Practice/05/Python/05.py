x, v, t = input("Введите x, v, t: ").split()
x = float(x)
v = float(v)
t = float(t)

xt = x + v*t - 9.8*t*t*0.5;

print(abs(xt- x))