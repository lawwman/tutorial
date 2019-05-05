#pragma once
#include <vector>

class Perceptron
{
	public:
		// Variables
		int input_size;
		std::vector<int> weights;
		
		// Functions
		Perceptron(int size);
		int guess();
};

