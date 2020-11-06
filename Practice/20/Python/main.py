from operator import attrgetter

class Drink:
    def __init__(self, name, price, volume):
        self.name = name
        self.price = price
        self.volume = volume
        self.bought = 0
        self.index = price / volume


money = int(input())
count = int(input())

drinks = []

for i in range(count):
    name, price, volume = input().split()
    price = int(price)
    volume = int(volume)
    drinks.append(Drink(name, price, volume))

drinks.sort(key=attrgetter('index'), reverse=False)

totalVolume = 0

while True:
    wasBought = False

    for i in range(count):
        if money > drinks[i].price:
            wasBought = True
            drinks[i].bought += 1
            money -= drinks[i].price
            break

    if not wasBought:
        break

for i in range(count):
    if drinks[i].bought > 0:
        totalVolume += drinks[i].volume * drinks[i].bought
        print(drinks[i].name, drinks[i].bought, sep=' ')

if totalVolume == 0:
    print(-1)
else:
    print(totalVolume)
    print(money)
