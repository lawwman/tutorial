#include "Math.hpp"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

float sigmoid(float x) {
	return 1 / (1 + exp(-x));
}

vector<float> sigmoid_of_vector(vector<float> x) {
	vector<float> sigmoid_vector(x.size());
 
	cout << "//////////SHOWING SIGMOID VALUES//////////" << endl;
	
	for (int i = 0; i < x.size(); i++) {
		sigmoid_vector[i] = sigmoid(x[i]);
		cout << sigmoid_vector[i] << endl;
	}
 
	return sigmoid_vector;
}

vector<float> dot_product(vector<vector<float>> weights, vector<float> input) {
	
	// Create vector of same length as number of neurons in NEXT layer.
	vector<float> dp_value(weights[0].size());
	
	// Getting weighted sum for each dp_value element
	for (int i = 0; i < dp_value.size(); i++) {
		float sum = 0;
		for (int j = 0; j < input.size(); j++) {
			sum += weights[j][i] * input[j];
		}
		dp_value[i] = sum;
	}
	
	cout << "//////////SHOWING NEW DP VALUE//////////" << endl;
	for (int i = 0; i < dp_value.size(); i++) {
		cout << dp_value[i] << endl;
	}
	
	return dp_value;
}

vector<float> matrix_addition(vector<float> a, vector<float> b) {
	
	vector<float> vector_sum(a.size());
	
	cout << "//////////SHOWING NEW VALUE AFTER ADDING BIAS//////////" << endl;
	
	for (int i = 0; i < vector_sum.size(); i++) {
		vector_sum[i] = a[i] + b[i];
		cout << vector_sum[i] << endl;
	}
	
	return vector_sum;
}

///////////////////////////FUNCTIONS TO DISPLAY VALUES///////////////////////////

void show_weights(vector<vector<vector<float>>> weights) {
	
	cout << "//////////SHOWING WEIGHTS OF NN//////////" << endl;
	
	for (int i = 0; i < weights.size(); i++) {
		cout << "Layer " << i << endl;
		for (int j = 0; j < weights[i].size(); j++) {
			cout << ">> Neuron " << j << endl;
			for (int k = 0; k < weights[i][j].size(); k++) {
				cout << ">> >> " << weights[i][j][k] << endl;
			}
		}
	}
}

void show_bias(vector<vector<float>> bias) {
	
	cout << "//////////SHOWING BIAS OF NN//////////" << endl;
	
	for (int i = 0; i < bias.size(); i++) {
		cout << "Layer " << i + 1 << endl;
		
		for (int j = 0; j < bias[i].size(); j++) {
			cout << ">> Neuron " << j << ": " << bias[i][j] << endl;
		}
	}
}

void show_activation(vector<vector<float>> a) {
	
	cout << "//////////SHOWING ACTIVATION OF NN//////////" << endl;
	
	for (int i = 0; i < a.size(); i++) {
		cout << "Layer " << i << endl;
		
		for (int j = 0; j < a[i].size(); j++) {
			cout << ">> Neuron " << j << ": " << a[i][j] << endl;
		}
	}
}

