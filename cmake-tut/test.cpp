#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));
	int max = 100, min = 0;
	int randNum = rand()%(max-min + 1) + min;
	cout << randNum << endl;
	randNum = rand()%(max-min + 1) + min;
	cout << randNum << endl;
	randNum = rand()%(max-min + 1) + min;
	cout << randNum << endl;
	randNum = rand()%(max-min + 1) + min;
	cout << randNum << endl;
	randNum = rand()%(max-min + 1) + min;
	cout << randNum << endl;
	randNum = rand()%(max-min + 1) + min;
	cout << randNum << endl;
	return 0;
}