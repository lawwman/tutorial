#include <iostream>
#include "util.hpp"
#include "Perceptron.hpp"

using namespace std;

int main() 
{
    cout << "Hello, World!" << endl;
	Perceptron perceptron(2);
	cout << "Hello, World!" << endl;
	for (int j = 0; j < 2; j++) {
		cout << "test" << endl;
		//cout << perceptron.weights[i] << endl;
	}
    return 0;
}