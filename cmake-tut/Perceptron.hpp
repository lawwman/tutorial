#include <vector>

class Perceptron
{
	public:
		// Variables
		int input_size;
		std::vector<int> weights;
		std::vector<int>::iterator it;
		
		// Functions
		Perceptron(int size);
		int guess();
};

