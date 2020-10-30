#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct drink {
	std::string name;
	unsigned int price = 0;
	unsigned int V = 0;
	unsigned int bought = 0;
};

bool compare_fn(const drink& a, const drink& b) {
	return (double(a.price) / a.V) < (double(b.price) / b.V);
}

int main() {
	unsigned int money;
	unsigned int c;

	std::cin >> money;
	std::cin >> c;

	std::vector <drink> options;

	for (int i = 0; i < c; i++) {
		options.push_back(drink());
		std::cin >> options[i].name >> options[i].price >> options[i].V;
	}

	std::sort(options.begin(), options.end(), compare_fn);

	while (true) {

		bool wasBought = false;

		for (int i = 0; i < c; i++) {

			if (money >= options[i].price) {
				wasBought = true;
				options[i].bought++;
				money -= options[i].price;
				break;
			}

		}

		if (!wasBought) break;

	}

	unsigned int totalVolume = 0;

	for (int i = 0; i < c; i++) {

		if (options[i].bought > 0) {
			totalVolume += options[i].V * options[i].bought;
			std::cout << options[i].name << " " << options[i].bought << std::endl;
		}

	}

	if (totalVolume == 0) {
		std::cout << -1 << std::endl;
		return 0;
	}

	std::cout << totalVolume << std::endl << money << std::endl;

}