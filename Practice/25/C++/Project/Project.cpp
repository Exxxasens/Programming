#include <iostream>
#include <ctime>
using namespace std;

void BozoSort(int[], int);
bool isSorted(int[], int);

int main()
{
	int arMyValues[5] = { 3, 2, 1, 5, 4 };
	BozoSort(arMyValues, 5);


	for (int i = 0; i < 5; i++) {
		cout << "Element: " << i << " - " << arMyValues[i] << endl;
	}

	return 0;
}
void BozoSort(int arValues[], int size) {
	int slot1 = 0;
	int slot2 = 0;
	int temp;


	srand(time(NULL));

	while (!isSorted(arValues, size)) {

		slot1 = rand() % size;
		slot2 = rand() % size;

		temp = arValues[slot1];
		arValues[slot1] = arValues[slot2];
		arValues[slot2] = temp;
	}
}


bool isSorted(int arValues[], int size) {
	for (int i = 0; i < size - 1; i++) {
		if (arValues[i] > arValues[i + 1]) {
			return false;
		}
	}
	return true;
}