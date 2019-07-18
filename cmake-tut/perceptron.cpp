#include "Perceptron.hpp"
#include <cstdlib>
#include <ctime>

int activation(float sum);

// Constructor
Perceptron::Perceptron(int size, float lr) {
	// To set random numbers
	srand(time(NULL));
	int max = 2, min = 0;
	int randNum = 0;
	
	input_size = size;
	learning_rate = lr;
	
	for(int i = 0; i < size; i++) { 
		// Iterators get invalidated after insert(). Need to get iterator again at beginning of loop
		it = weights.begin(); 
		
		randNum = rand()%(max-min + 1) + - 1; // Generate number from -1 to 1
		weights.insert(it + i, randNum);
	}
}

float Perceptron::guess(float inputs[]) {
	float sum = 0;
	
	for (int i = 0; i < input_size; i++) {
		
		sum += weights[i] * inputs[i];
	}
	
	return activation(sum);
}

void Perceptron::train(float inputs[], int target) {
	int guess_ = guess(inputs);
	int error = target - guess;
	
	for (int i = 0; i < input_size; i++) {
		
		it = weights.begin(); 
		
		float new_weight = error * inputs[i] * learning_rate;
		
		weights.insert(it + i, new_weight);
	}
}

int activation(float sum) {
	if (sum >= 0) return 1; 
	else return -1;
	
}

