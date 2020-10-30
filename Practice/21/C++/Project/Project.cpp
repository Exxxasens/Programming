#include <iostream>

double BMI(double weight, double height) {
	return weight / (height * height);
}

void printBMI(double BMI) {
	if (BMI < 18.5) {
		std::cout << "Underweight" << std::endl;
	}
	else if (BMI >= 18.5 && BMI < 25) {
		std::cout << "Normal" << std::endl;
	}
	else if (BMI >= 25 && BMI < 30) {
		std::cout << "Overweight" << std::endl;
	}
	else {
		std::cout << "Obesity" << std::endl;
	}
}

int main() {
	double w, h;

	std::cin >> w >> h;

	h = h / 100;

	printBMI(BMI(w, h));

}