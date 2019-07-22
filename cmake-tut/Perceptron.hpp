#pragma once
#include <vector>

class Perceptron
{
	public:
		// Variables
		int input_size;
		float learning_rate;
		std::vector<float> weights;
		std::vector<float>::iterator it;
		
		// Functions
		Perceptron(int size, float lr);
		float guess(float inputs[]);
		void train(float inputs[], int target);
};

