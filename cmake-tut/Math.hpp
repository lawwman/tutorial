#pragma once
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

double sigmoid(double x);

vector<double> sigmoid_of_vector(vector<double> x);

vector<double> sigmoid_prime_of_vector(vector<double> x);

/* Used for adding bias to the neurons after dot product */
vector<double> matrix_addition(vector<double> a, vector<double> b);

vector<double> matrix_substitution(vector<double> a, vector<double> b);

vector<double> matrix_multiplication(vector<double> a, vector<double> b);
/*
 * @Params
 * Weights = Given a certain layer, weights represent all the weights between that certain layer and the
 *           next layer.
 * input   = All the input values for each of the neuron on the certain layer.
 * 
 * Function returns the dot product of the 2 matrices.
 */
vector<double> dot_product_for_ff(vector<vector<double>> weights, vector<double> input);

vector<double> dot_product_for_bp(vector<vector<double>> weights, vector<double> error);

vector<vector<double>> dot_product_for_delta_w(vector<double> activation, vector<double> error);


///////////////////////////FUNCTIONS TO DISPLAY VALUES///////////////////////////
void show_weights(vector<vector<vector<double>>> weights);
void show_bias(vector<vector<double>> bias);
void show_activation(vector<vector<double>> a);
