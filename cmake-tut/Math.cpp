#include "Math.hpp"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}

vector<double> sigmoid_of_vector(vector<double> x) {
	vector<double> sigmoid_vector(x.size());
	
	for (int i = 0; i < x.size(); i++) {
		sigmoid_vector[i] = sigmoid(x[i]);
	}
 
	return sigmoid_vector;
}

vector<double> sigmoid_prime_of_vector(vector<double> x) {
	
	vector<double> one_minus_sigmoid(x.size());
	vector<double> sigmoid_ = sigmoid_of_vector(x);
	
	for (int i = 0; i < x.size(); i++) {
		one_minus_sigmoid[i] = 1.0 - sigmoid_[i];
	}
	
	return matrix_multiplication(one_minus_sigmoid, sigmoid_);
}

///////////////////////////MATRIX MATH///////////////////////////

vector<double> matrix_addition(vector<double> a, vector<double> b) {
	
	vector<double> vector_sum(a.size());
	
	
	for (int i = 0; i < vector_sum.size(); i++) {
		vector_sum[i] = a[i] + b[i];
	}
	
	return vector_sum;
}

vector<double> matrix_substitution(vector<double> a, vector<double> b) {
	
	vector<double> vector_remainder(a.size());
	
	for (int i = 0; i < vector_remainder.size(); i++) {
		vector_remainder[i] = a[i] - b[i];
	}
	
	return vector_remainder;
}

vector<double> matrix_multiplication(vector<double> a, vector<double> b) {
	
	vector<double> vector_product(a.size());
	
	for (int i = 0; i < vector_product.size(); i++) {
		vector_product[i] = a[i] * b[i];
	}
	
	return vector_product;
}

///////////////////////////FUNCTIONS TO CALCULATE DOT PRODUCT///////////////////////////

vector<double> dot_product_for_ff(vector<vector<double>> weights, vector<double> input) {
	
	// Create vector of same length as number of neurons in NEXT layer.
	vector<double> dp_value(weights[0].size());
	
	// Getting weighted sum for each dp_value element
	for (int i = 0; i < dp_value.size(); i++) {
		double sum = 0;
		for (int j = 0; j < input.size(); j++) {
			sum += weights[j][i] * input[j];
		}
		dp_value[i] = sum;
	}
	
	return dp_value;
}

vector<double> dot_product_for_bp(vector<vector<double>> weights, vector<double> error) {
	
	// Create vector of same length as number of neurons in NEXT layer.
	vector<double> dp_value(weights.size());
	
	// Getting weighted sum for each dp_value element
	for (int i = 0; i < dp_value.size(); i++) {
		double sum = 0;
		for (int j = 0; j < error.size(); j++) {
			sum += weights[i][j] * error[j];
		}
		dp_value[i] = sum;
	}
	
	return dp_value;
}

vector<vector<double>> dot_product_for_delta_w(vector<double> activation, vector<double> error) {
	vector<vector<double>> dw;
	dw.resize(activation.size());
	
	for (int i = 0; i < activation.size(); i++) {	
		dw[i].resize(error.size());
		for (int j = 0; j < error.size(); j++) {
			dw[i][j] = activation[i] * error[j];
		}
	}
	
	return dw;
	
}

///////////////////////////FUNCTIONS TO DISPLAY VALUES///////////////////////////

void show_weights(vector<vector<vector<double>>> weights) {
	
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

void show_bias(vector<vector<double>> bias) {
	
	cout << "//////////SHOWING BIAS OF NN//////////" << endl;
	
	for (int i = 0; i < bias.size(); i++) {
		cout << "Layer " << i + 1 << endl;
		
		for (int j = 0; j < bias[i].size(); j++) {
			cout << ">> Neuron " << j << ": " << bias[i][j] << endl;
		}
	}
}

void show_activation(vector<vector<double>> a) {
	
	cout << "//////////SHOWING ACTIVATION OF NN//////////" << endl;
	
	for (int i = 0; i < a.size(); i++) {
		cout << "Layer " << i << endl;
		
		for (int j = 0; j < a[i].size(); j++) {
			cout << ">> Neuron " << j << ": " << a[i][j] << endl;
		}
	}
}

