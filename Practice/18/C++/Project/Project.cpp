#include <iostream>
#include <string>
#include <vector>

int countSymbol(std::vector<std::string>, char);
int countAllSymbols(std::vector<std::string>);

int main() {

	std::vector<std::string> words {
		"hallo",
		"klempner",
		"das",
		"ist",
		"fantastisch",
		"fluggegecheimen"
	};
	
	std::string in;
	std::cin >> in;
	
	int inSize = in.size();
	double probability = 1;
	int wordsSize = countAllSymbols(words);


	for (int i = 0; i < inSize; i++) {
		probability *= double(countSymbol(words, in[i])) / wordsSize;
	}

	std::cout << probability << std::endl;


}

int countSymbol(std::vector<std::string> arr, char symbol) {
	int counter = 0;
	int len = arr.size();
	for (int i = 0; i < len; i++) {
		int strLen = arr[i].size();
		for (int j = 0; j < strLen; j++) {
			if (arr[i][j] == symbol) counter++;
		}

	}
	return counter;

}

int countAllSymbols(std::vector<std::string> arr) {
	int counter = 0;
	int len = arr.size();

	for (int i = 0; i < len; i++) {
		int strLen = arr[i].size();
		counter += strLen;
	}

	return counter;
}