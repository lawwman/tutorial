#include "Perceptron.hpp"

Perceptron::Perceptron(int size) {
	input_size = size;
	for(int i = 0; i < size; i++){
		// Iterators get invalidated after insert(). Need to get iterator again at beginning of loop
		it = weights.begin(); 
		weights.insert(it + i, i);
	}
}

int Perceptron::guess() {
	int sum = 0;
	
	return sum;
}
