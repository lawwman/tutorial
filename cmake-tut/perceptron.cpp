#include "Perceptron.hpp"
#include <cstdlib>
#include <ctime>

Perceptron::Perceptron(int size) {
	// To set random numbers
	srand(time(NULL));
	int max = 2, min = 0;
	int randNum = 0;
	
	input_size = size;
	for(int i = 0; i < size; i++){
		// Iterators get invalidated after insert(). Need to get iterator again at beginning of loop
		it = weights.begin(); 
		
		randNum = rand()%(max-min + 1) + - 1; // Generate number from -1 to 1
		weights.insert(it + i, randNum);
	}
}

int Perceptron::guess() {
	int sum = 0;
	
	return sum;
}
