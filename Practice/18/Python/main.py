def count_symbol(arr, symbol):
    w_length = len(arr)
    counter = 0
    for j in range(0, w_length):
        counter += arr[j].count(symbol)
    return counter


words = [
    "hallo",
    "klempner",
    "das",
    "ist",
    "fantastisch",
    "fluggegecheimen"
]

all_symbols = 0
probability = 1.0
word = input()

for i in range(0, len(words)):
    all_symbols += len(words[i])

for k in range(0, len(word)):
    probability *= count_symbol(words, word[k]) / all_symbols

print(probability)
