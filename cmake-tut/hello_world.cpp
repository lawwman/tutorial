#include <iostream>
#include "Perceptron.hpp"

using namespace std;

int main() 
{
    cout << "Hello, World!" << endl;
	Perceptron perceptron(2);
	for (int j = 0; j < 2; j++) {
		cout << perceptron.weights[j] << endl;
	}
	
	float input[] = {1, 2};
	
	int guess = perceptron.guess(input);
	
	cout << "Guess: " << guess << endl;
    return 0;
}