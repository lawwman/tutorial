#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "Math.hpp"
#include "util.hpp"

using namespace std;

// The number of layers within the neural network, inclusive of input and output layers
int num_layers;
list<int> listOfLayers; // A vector containing the number of neurons in each layer.

/*
 * A vector containing vectors of biases for each neuron in each layer, except first layer.
 */
vector<vector<double>> bias;
vector<vector<double>> delta_bias;

/* ##Note## I used a my own naming convention to explain my vectors for weights.
 * Layer_vector or the outer-most vector is a vector with length = num_layers - 1.
 * Layer_vector's elements are neuron_vectors, each with length = num of neurons.
 * Neuron_vector's elements are weight_vectors, each with length = num of neurons in next layer.
 * Weight_vector's elements are double values, each corresponding to the weight between itself and
 * each neuron in the next layer.
 * weights[0] would be the vector of weights between all the neurons in the first layer and all the
 * other neurons in the next layer.
 * weights[0][0] would be the vector of weights between the 1st neuron in 1st layer and all other
 * neurons in the next layer.
 * weights[0][1][2] would be the vector of weights between the 2nd neuron in the 1st layer and the
 * 3rd neuron in the next layer.
 */
vector<vector<vector<double>>> weights;
vector<vector<vector<double>>> delta_weights;

/* List of activation values for each layer */
vector<vector<double>> activation;

/* List of z values for each layer */
vector<vector<double>> zs;

double learning_rate = 0.1;
int epoch = 50000;
int batch_size = 100;

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
			delta_bias[i][j] = 0;
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
				delta_weights[i][j][k] = 0;
			}
		}
		curr++;
		next++;
	}
	return 1;
}

// Returns the output of the network, given an input
vector<double> feedforward(vector<double> input) {
	
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
		zs[i] = dot_product_for_ff(weights[i - 1], activation[i - 1]);
		zs[i] = matrix_addition(zs[i], bias[i - 1]);
		activation[i] = sigmoid_of_vector(zs[i]);
	}
	
	return activation[num_layers - 1];
}

void update_weights_and_bias() {
	
	list<int>::iterator curr = listOfLayers.begin(); // iterator for current layer.
	list<int>::iterator next = listOfLayers.begin(); // iterator for next layer.
	next++;

	for (int i = 0; i < num_layers - 1; i++) {
		for (int j = 0; j < *curr; j++) {
			for (int k = 0; k < *next; k++) {
				weights[i][j][k] -= learning_rate * delta_weights[i][j][k];
			}
		}
		curr++;
		next++;
	}
	
	list<int>::iterator it = listOfLayers.begin();
	it++;
	
	for (int i = 0; i < num_layers - 1; i++) {
		for (int j = 0; j < *it; j++) {
			bias[i][j] -= learning_rate * delta_bias[i][j];
		}
		it++;
	}
}

// Trains the network to learn the new weights and bias using a vector of input vectors
void backprop(vector<vector<double>> input, vector<vector<double>> expected) {
	
	// Set up list of delta values to be used
	vector<vector<double>> delta_list(num_layers - 1);
	list<int>::iterator it = listOfLayers.begin();
	it++;
	for (int i = 0; i < num_layers - 1; i++) {
		delta_list[i].resize(*it);
		it++;
	}
	
	// Train network for each input value given
	for (int i = 0; i < input.size(); i++) {
		// Get the activation and zs values
		vector<double> outcome = feedforward(input[i]);
		
		vector<double> delta_last_layer = matrix_multiplication(matrix_substitution(activation[num_layers
			- 1], expected[i]), sigmoid_prime_of_vector(zs[num_layers - 1]));
		
		delta_list[num_layers - 2] = delta_last_layer;
		
		// (num_layers - 2) because bias has length of (num_layers - 1)
		delta_bias[num_layers - 2] = delta_list[num_layers - 2];
		
		// (num_layers - 2) because weights has length of (num_layers - 1)
		delta_weights[num_layers - 2] = dot_product_for_delta_w(activation[num_layers - 2],
			delta_list[num_layers - 2]);
		
		
		
		for (int j = 2; j < num_layers; j++) {
			
			vector<double> temp = dot_product_for_bp(weights[num_layers - j],
				delta_list[num_layers - j]);
				
			delta_list[num_layers - j - 1] = matrix_multiplication(temp, sigmoid_prime_of_vector(zs[num_layers - j]));
			
			delta_bias[num_layers - j - 1] = delta_list[num_layers - j - 1];
			
			delta_weights[num_layers - j - 1] = dot_product_for_delta_w(activation[num_layers - j - 1],
				delta_list[num_layers - j - 1]);
		}
		update_weights_and_bias();
	}
}

/* Returns the set of coordinates for the display_data function. */
vector<vector<double>> evaluate(vector<vector<vector<double>>> dataset) {
	
	/* Store information about whether the test data had correct or wrong results */
	vector<vector<double>> data(dataset[2].size());
	
	for (int i = 0; i < data.size(); i++) {
		data[i].resize(dataset[2][0].size() + dataset[3][0].size());
	}
	
	cout << "testing...size of display data: " << dataset[2][0].size() + 1 << endl;
	
	int correct = 0;

	for (int i = 0; i < dataset[2].size(); i++) {
		vector<double> output = feedforward(dataset[2][i]);
		cout << "/////////////////////////" << endl;
		
		/* Print out the Neural network's actual output */
		cout << output[0] << " " << output[1] << endl;
		
		/* Print out the Neural network's expected output */
		cout << dataset[3][i][0] << " " << dataset[3][i][1] << endl;
		
		/* Print out the Neural network's input */
		cout << dataset[2][i][0] << " " << dataset[2][i][1] << endl;
		
		if (dataset[3][i][0] == 1) {
			if (output[0] > 0.9 && output[1] < 0.1) {
				correct += 1;
				data[i] = {dataset[2][i][0], dataset[2][i][1], 1};
			}
			else {
				data[i] = {dataset[2][i][0], dataset[2][i][1], 0};
			}
		}
		else {
			if (output[1] > 0.9 && output[0] < 0.1) {
				correct += 1;
				data[i] = {dataset[2][i][0], dataset[2][i][1], 1};
			}
			else {
				data[i] = {dataset[2][i][0], dataset[2][i][1], 0};
			}
		}
	}
	
	cout << "Number of correct predictions: " << correct << endl;
	return data;
}

void evaluate_easy(vector<vector<vector<double>>> dataset) {

	for (int i = 0; i < dataset[2].size(); i++) {
		vector<double> test = feedforward(dataset[2][i]);
		cout << "/////////////////////////" << endl;
		cout << test[0] << endl;
		cout << dataset[3][i][0] << endl;
		cout << dataset[2][i][0] << " " << dataset[2][i][1] << endl;
	}
}

int main() {
	
	vector<vector<vector<double>>> dataset = generate_train_test_data();
	
	int check = setup();
	if (check == 0) return 0; // There is an error in the setup, end the program.
	
	for (int i = 0; i < epoch; i++) {
		randomize_train_data(dataset);
		
		// Get input and expected output for the batch.
		vector<vector<double>> batch_input(batch_size);
		vector<vector<double>> batch_output(batch_size);
		
		for (int j = 0; j < batch_size; j++) {
			batch_input[j] = dataset[0][j];
			batch_output[j] = dataset[1][j];
		}
		
		// Feed the batch into the neural network.
		backprop(batch_input, batch_output);
		
		// Display the output from the neural network after every 20 iterations.
		if (i%20 == 0) {
			vector<vector<double>> data = evaluate(dataset);
			display_data(data);
			cout << i << "th iteration. Continue?" << endl;
			char yes;
			cin >> yes;
			system("cls");
		}
	}
	return 0;
}