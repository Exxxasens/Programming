count = int(input())
tickets = []

for i in range(count):
    ticket = input()
    print(ticket[:5])
    if ticket[0] == 'a' and ticket[:-5] == "55661":
        tickets.append(ticket)

for i in range(len(tickets)):
    print(tickets[i])

