#include <string>
#include <iostream>
#include <vector>

int main() {
    int count;
    std::cin >> count;
    std::vector <std::string> tickets;

    for (int i = 0; i < count; i++) {
        std::string ticket;
        std::cin >> ticket;
        if (ticket[0] == 'a' && ticket.substr(4) == "55661") {
            tickets.push_back(ticket);
        }
    }

    int ticketsLength = tickets.size();

    if (ticketsLength == 0) {
        std::cout << -1;
        return 0;
    }

    for (int i = 0; i < ticketsLength; i++) {
        std::cout << tickets[i] << ' ';
    }

}
