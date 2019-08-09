#include "util.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <Windows.h>

using namespace std;

vector<vector<vector<double>>> generate_train_test_data() {
	vector<vector<vector<double>>> data_set;
	
	data_set.resize(4); // Train_X, Train_Y, Test_X, Test_Y
	
	// Eqn: Y = X1
	// Given coordinate X and Y, if it is higher than the line, Y = {1, 0}, else Y = {0, 1}.
	
	int training_length = 500;
	int test_length = 40;
	
	data_set[0].resize(training_length);
	data_set[1].resize(training_length);
	data_set[2].resize(test_length);
	data_set[3].resize(test_length);
	
	srand(time(NULL));
	
	bool test = false;
	
	int count = 0;

	for (int i = 0; i < training_length + test_length; i++) {  // 80 to train, 20 to test
	
		double train_x1 = rand()%50;
		double train_x2 = rand()%50;
		
		vector<double> train_x = {train_x1, train_x2};
		vector<double> train_y;
		
		if ((train_x1) < train_x2) {
			train_y = {0, 1};
		}
		else {
			train_y = {1, 0};
		}
		if (i > (training_length - 1) && !test) {
			count = 0;
			test = true;
		}
		
		if (!test) {
			data_set[0][count] = train_x;
			data_set[1][count] = train_y;
		}
		else {
			data_set[2][count] = train_x;
			data_set[3][count] = train_y;
		}
		count++;
	}
	
	return data_set;
}

vector<vector<vector<double>>> generate_easy_train_test_data() {
	vector<vector<vector<double>>> data_set;
	
	data_set.resize(4); // Train_X, Train_Y, Test_X, Test_Y
	
	int training_length = 4;
	int test_length = 4;
	
	data_set[0].resize(training_length);
	data_set[1].resize(training_length);
	data_set[2].resize(test_length);
	data_set[3].resize(test_length);
	
	data_set[0][0] = {0, 1};
	data_set[1][0] = {1};
	
	data_set[0][1] = {1, 0};
	data_set[1][1] = {1};
	
	data_set[0][2] = {0, 0};
	data_set[1][2] = {0};

	data_set[0][3] = {1, 1};
	data_set[1][3] = {0};
	
	data_set[2][0] = {0, 1};
	data_set[3][0] = {1};
	
	data_set[2][1] = {1, 0};
	data_set[3][1] = {1};
	
	data_set[2][2] = {0, 0};
	data_set[3][2] = {0};

	data_set[2][3] = {1, 1};
	data_set[3][3] = {0};
	
	return data_set;
}

vector<vector<vector<double>>> randomize_train_data(vector<vector<vector<double>>> train_data) {
	
	int length_of_train_data = train_data[0].size();
	vector<vector<vector<double>>> train_data_to_rand(length_of_train_data);
	
	// Append the training input and expected output together for it to be later randomized
	for (int i = 0; i < length_of_train_data; i++) {
		train_data_to_rand[i].resize(2);
		train_data_to_rand[i][0] = train_data[0][i];
		train_data_to_rand[i][1] = train_data[1][i];
	}
	
	random_shuffle(train_data_to_rand.begin(), train_data_to_rand.end()); // Shuffles the vector
	
	// Return the randomized training data to the original dataset.
	for (int i = 0; i < length_of_train_data; i++) {
		train_data[0][i] = train_data_to_rand[i][0];
		train_data[1][i] = train_data_to_rand[i][1];
	}
	
	return train_data;
}

void display_data(vector<vector<double>> train_data) {
	// 52 because the 2 walls at the sides not included.
	for (int i = 0; i < 52; i++) {
		cout << "#";
	}
	cout << endl;
	
	int count = 0;
	
	for (int i = 0; i < 50; i++) {
		count = 0;
		for (int j = 0; j < 52; j++) {
			if (j == 0 || j == 51) {
				cout << "#";
			}
			else if (i == j) {
				cout << "*";
			}
			else {
				for (int k = 0; k < train_data.size(); k++) {
					if (train_data[k][0] == j && train_data[k][1] == i) {
						cout << train_data[k][2];
						count++;
						break;
						/*
						OK. this is how i choose to handle duplicate coordinates. Fucking ignore them
						they aint gonna be represented in the graph if there are dups. Fuck it.
						I could always make a function to ensure unique coordinates but hells no.
						BREAK OUT OF THE LOOP BITCH.
						
						And yes. '*' has a higher priority. so fuck the other shit.
						*/
					}
				}
				if (count == 0) {
					cout << " ";
				}
			}
			if (count > 0) {
				count--;
			}
			
		}
		cout << endl;
	}
	
	for (int i = 0; i < 52; i++) {
		cout << "#";
	}
	cout << endl;
}