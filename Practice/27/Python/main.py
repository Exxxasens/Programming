n = int(input())
signals = []
for i in range(n):
    signals.append(int(input()))
    signals.sort()
    signalsSize = len(signals)

    if signalsSize > 5:
        signalsSize = 5

    for k in range(signalsSize):
        print(signals[signalsSize - 1 - k], sep=' ', end=' ')
