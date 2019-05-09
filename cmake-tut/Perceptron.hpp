#pragma once
#include <vector>

class Perceptron
{
	public:
		// Variables
		int input_size;
		std::vector<float> weights;
		std::vector<float>::iterator it;
		
		// Functions
		Perceptron(int size);
		float guess(float inputs[]);
};

