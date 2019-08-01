#include "util.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<vector<double>>> generate_train_test_data() {
	vector<vector<vector<double>>> data_set;
	
	data_set.resize(4); // Train_X, Train_Y, Test_X, Test_Y
	
	// Eqn: Y = X1
	// Given coordinate X and Y, if it is higher than the line, Y = {1, 0}, else Y = {0, 1}.
	
	data_set[0].resize(400);
	data_set[1].resize(400);
	data_set[2].resize(40);
	data_set[3].resize(40);
	
	srand(time(NULL));
	
	bool test = false;
	
	int count = 0;

	for (int i = 0; i < 440; i++) {  // 80 to train, 20 to test
	
		double train_x1 = rand()%70;
		double train_x2 = rand()%70;
		
		vector<double> train_x = {train_x1, train_x2};
		vector<double> train_y;
		
		if ((train_x1) < train_x2) {
			train_y = {0, 1};
		}
		else {
			train_y = {1, 0};
		}
		if (i > 399 && !test) {
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
