#pragma once
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

float sigmoid(float x);

vector<float> sigmoid_of_vector(vector<float> x);

/*
 * @Params
 * Weights = Given a certain layer, weights represent all the weights between that certain layer and the
 *           next layer.
 * input   = All the input values for each of the neuron on the certain layer.
 * 
 * Function returns the dot product of the 2 matrices.
 */
vector<float> dot_product(vector<vector<float>> weights, vector<float> input);

/* Used for adding bias to the neurons after dot product */
vector<float> matrix_addition(vector<float> a, vector<float> b);


///////////////////////////FUNCTIONS TO DISPLAY VALUES///////////////////////////
void show_weights(vector<vector<vector<float>>> weights);
void show_bias(vector<vector<float>> bias);
void show_activation(vector<vector<float>> a);
