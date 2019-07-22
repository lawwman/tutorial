#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// The number of layers within the neural network, inclusive of input and output layers
int num_layers;
list<int> listOfLayers; // A vector containing the number of neurons in each layer.
vector<vector<float>> bias; // A vector containing vectors of biases for each neuron in each layer.

/* ##Note## I used a my own naming convention to explain my vectors for weights.
 * Layer_vector or the outer-most vector is a vector with length = num_layers - 1.
 * Layer_vector's elements are neuron_vectors, each with length = num of neurons.
 * Neuron_vector's elements are weight_vectors, each with length = num of neurons in next layer.
 * Weight_vector's elements are float values, each corresponding to the weight between itself and
 * each neuron in the next layer.
 * weights[0][0] would be the vector of weights between the 1st neuron in 1st layer and all other
 * neurons in the next layer.
 * weights[0][1][2] would be the vector of weights between the 2nd neuron in the 1st layer and the
 * 3rd neuron in the next layer.
 */
vector<vector<vector<float>>> weights;

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
	
	// Since vector size was not declared before, need to resize before giving values.
	bias.resize(num_layers);
	for (int i = 0; i < num_layers; i++) {
		bias[i].resize(*it);
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
	for (int i = 0; i < num_layers - 1; i++) {
		weights[i].resize(*curr); // Resize the neuron_vector
		for (int j = 0; j < *curr; j++) {
			weights[i][j].resize(*next); // Resize the weight vector
			for (int k = 0; k < *next; k++) {
				weights[i][j][k] = rand()%2;
			}
		}
		curr++;
		next++;
	}
	
	
	return 1;
}

int main() {
	
	int check = setup();
	if (check == 0) return 0; // There is an error, end the program.
	
	

	
	return 0;
}