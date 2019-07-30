#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "Math.hpp"

using namespace std;

// The number of layers within the neural network, inclusive of input and output layers
int num_layers;
list<int> listOfLayers; // A vector containing the number of neurons in each layer.

/*
 * A vector containing vectors of biases for each neuron in each layer, except first layer.
 */
vector<vector<float>> bias;
vector<vector<float>> delta_bias;

/* ##Note## I used a my own naming convention to explain my vectors for weights.
 * Layer_vector or the outer-most vector is a vector with length = num_layers - 1.
 * Layer_vector's elements are neuron_vectors, each with length = num of neurons.
 * Neuron_vector's elements are weight_vectors, each with length = num of neurons in next layer.
 * Weight_vector's elements are float values, each corresponding to the weight between itself and
 * each neuron in the next layer.
 * weights[0] would be the vector of weights between all the neurons in the first layer and all the
 * other neurons in the next layer.
 * weights[0][0] would be the vector of weights between the 1st neuron in 1st layer and all other
 * neurons in the next layer.
 * weights[0][1][2] would be the vector of weights between the 2nd neuron in the 1st layer and the
 * 3rd neuron in the next layer.
 */
vector<vector<vector<float>>> weights;
vector<vector<vector<float>>> delta_weights;

/* List of activation values for each layer */
vector<vector<float>> activation;

/* List of z values for each layer */
vector<vector<float>> zs;

vector<float> input;

void test(int i) {
	cout << "test " << i << endl;
}

/* Setup the neural network by defining num_layers and listOfLayers, taking values from the user.
 * Initialise the weights and biases
 * return 0 if there is an error, else return 1.
 */
int setup() {
	cout << "define network parameters:" << endl;
	cout << "Input number of layers:" << endl;
	cin >> num_layers;
	try {
		// num_layers cannot be less than 2 since it includes input and output layers
		if (num_layers < 2) {
			throw "Number of layers have to be 2 or more.";
		}
	} catch(const char* msg) {
		cout << msg << endl;
		return 0;
	}
	list<int>::iterator it = listOfLayers.begin();

	for (int i = 0; i < num_layers; i++) {
		
		try {
			int numNeuronInLayer;
			cout << "Input number of neuron in layer " << i + 1 << endl;
			cin >> numNeuronInLayer;
			if (numNeuronInLayer == 0) {
				throw "Number of neurons cannot be zero!";
			}
			listOfLayers.insert(it, numNeuronInLayer);
			
		} catch (const char* msg) {
				cout << msg << endl;
				return 0;
		}
	}
	
	it = listOfLayers.begin();
	for (int i = 0; i < num_layers; i++) {
		cout << (*it) << endl;
		it++;
	}
	
	// Define the random initial biases.
	cout << "initialising bias values..." << endl;
	
	// To set random numbers
	srand(time(NULL));
	it = listOfLayers.begin();
	it++;
	
	// Since vector size was not declared before, need to resize before giving values.
	bias.resize(num_layers - 1);
	delta_bias.resize(num_layers - 1);
	for (int i = 0; i < num_layers - 1; i++) {
		bias[i].resize(*it);
		delta_bias[i].resize(*it);
		for (int j = 0; j < *it; j++) {
			bias[i][j] = rand()%2;
		}
		it++;
	}
	
	
	// Define the random initial weights.
	cout << "initialising weights values..." << endl;
	
	list<int>::iterator curr = listOfLayers.begin(); // iterator for current layer.
	list<int>::iterator next = listOfLayers.begin(); // iterator for next layer.
	next++;
	
	// Since vector size was not declared before, need to resize before giving values.
	weights.resize(num_layers - 1); // Resize the Layer_vector
	delta_weights.resize(num_layers - 1);
	for (int i = 0; i < num_layers - 1; i++) {
		weights[i].resize(*curr); // Resize the neuron_vector
		delta_weights[i].resize(*curr);
		for (int j = 0; j < *curr; j++) {
			weights[i][j].resize(*next); // Resize the weight vector
			delta_weights[i][j].resize(*next);
			for (int k = 0; k < *next; k++) {
				weights[i][j][k] = rand()%2;
			}
		}
		curr++;
		next++;
	}
	return 1;
}

// Returns the output of the network, given an input
vector<float> feedforward(vector<float> input) {
	
	list<int>::iterator it = listOfLayers.begin();
	
	// Define size of activation vector and zs vector
	activation.resize(num_layers);
	zs.resize(num_layers);
	
	/* Set activation of first layer to be input */
	activation[0].resize(*it);
	activation[0] = input;
	
	zs[0].resize(*it);
	zs[0] = input;
	
	it++;
	
	for (int i = 1; i < num_layers; i++) {
		
		// Define size of vector
		activation[i].resize(*it);
		zs[i].resize(*it);
		it++;
		
		// Feed forward from layer (i-1) to layer i.
		zs[i] = dot_product_for_ff(weights[i-1], activation[i-1]);
		zs[i] = matrix_addition(zs[i], bias[i-1]);
		activation[i] = sigmoid_of_vector(zs[i]);
	}
	
	return activation[num_layers - 1];
}

// Trains the network to learn the new weights and bias using a vector of input vectors
void backprop(vector<vector<float>> input, vector<vector<float>> expected) {
	
	for (int i = 0; i < input.size(); i++) {
		// Get the activation and zs values
		vector<float> outcome = feedforward(input[i]);
		
		vector<float> delta_last_layer = matrix_multiplication(matrix_substitution(activation[num_layers
			- 1], expected[i]), sigmoid_prime_of_vector(zs[num_layers - 1]));
		
		// (num_layers - 2) because bias has length of (num_layers - 1)
		delta_bias[num_layers - 2] = delta_last_layer;
		
		// (num_layers - 2) because weights has length of (num_layers - 1)
		delta_weights[num_layers - 2] = dot_product_for_delta_w(activation[num_layers - 2],
			delta_last_layer);
		
		for (int j = 2; j < num_layers; j++) {
			// vector<float> delta = hmmmm...
			
			delta_bias[num_layers - j - 1] = delta;
			
			delta_weights[num_layers - j - 1] = dot_product_for_delta_w(activation[num_layers - j - 1],
				delta);
		}
	}
}

int main() {
	
	int check = setup();
	if (check == 0) return 0; // There is an error, end the program.
	
	show_weights(weights);
	show_bias(bias);
	
	input = {3, 2, 3};
	
	vector<float> outcome = feedforward(input);
	show_activation(activation);

	
	return 0;
}