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
    return 0;
}