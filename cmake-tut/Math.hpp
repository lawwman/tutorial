#pragma once
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

float sigmoid(float x);

vector<float> sigmoid_of_vector(vector<float> x);

vector<float> sigmoid_prime_of_vector(vector<float> x);

/* Used for adding bias to the neurons after dot product */
vector<float> matrix_addition(vector<float> a, vector<float> b);

vector<float> matrix_substitution(vector<float> a, vector<float> b);

vector<float> matrix_multiplication(vector<float> a, vector<float> b);
/*
 * @Params
 * Weights = Given a certain layer, weights represent all the weights between that certain layer and the
 *           next layer.
 * input   = All the input values for each of the neuron on the certain layer.
 * 
 * Function returns the dot product of the 2 matrices.
 */
vector<float> dot_product_for_ff(vector<vector<float>> weights, vector<float> input);

vector<vector<float>> dot_product_for_delta_w(vector<float> activation, vector<float> error);


///////////////////////////FUNCTIONS TO DISPLAY VALUES///////////////////////////
void show_weights(vector<vector<vector<float>>> weights);
void show_bias(vector<vector<float>> bias);
void show_activation(vector<vector<float>> a);
